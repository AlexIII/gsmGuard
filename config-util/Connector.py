import struct
import base64
import serial.tools.list_ports
import serial
import time

class Connector:
    schedMaxSz = 15
    debug = True
    baudrate = 250000
    
    @staticmethod
    def getPorts():
        return [d.device for d in serial.tools.list_ports.comports()]

    @staticmethod
    def read(port, eventHist = False, tempHist = False):
        p = serial.Serial(port=port, baudrate=Connector.baudrate, timeout=3)
        if not p.isOpen():
            raise Exception('Cannot open port ' + port)
        p.setDTR(False)     #chip reset
        time.sleep(0.3)
        p.setDTR(True)
        ans = p.readline() #because of chip reset on port open
        if not ans:        #it should not be scilent after reset
            raise Exception('No answer')

        #request config
        p.write('\r\nCONFIG_REQ\r\n')
        p.timeout = 0.5
        ans = ""
        emptyStrCnt = 0
        for i in range(0, 30):
            ans = p.readline()
            if Connector.debug:
                print("RX: " + ans)
            if not ans:
                emptyStrCnt += 1
                if emptyStrCnt > 5:
                    break
            ans = ans.split('CONFIG_V1: ')
            if len(ans) >= 2 and not ans[0]:
                ans = ans[1]
                break
            ans = ""
        if not ans:
            p.close()
            raise Exception('No answer for config request')
        if Connector.debug:
            print("ANS: " + ans)
        conf = ans

        def getCsv():
            csv = ""
            started = False
            emptyStrCnt = 0
            for i in range(0, 800):
                ans = p.readline()
                if Connector.debug:
                    print("RX: " + ans)
                if not ans:
                    emptyStrCnt += 1
                    if emptyStrCnt > 5:
                        break
                if not started:
                    if ans.startswith("----CSV BEGIN----"):
                        started = True
                else:
                    if ans.startswith("----CSV END----"):
                        started = False
                        break
                    csv += ans
            if started:
                csv = ""
            return csv

        def getData(reqStr, name):
            p.write('\r\n'+reqStr+'\r\n')
            csv = getCsv()
            if not csv:
                p.close()
                raise Exception('No answer for '+name+' request')
            if Connector.debug:
                print(name + ' CSV: ' + csv)
            return csv

        #request event history
        eventHistCSV = getData('EVENTS_REQ', 'event') if eventHist else None
        tempHistCSV = getData('TEMP_REQ', 'temp') if tempHist else None

        p.close()
        ret = Connector.unpack(conf)
        ret['eventHist'] = eventHistCSV
        ret['tempHist'] = tempHistCSV
        return ret
        
    @staticmethod
    def write(port, conf):
        p = serial.Serial(port=port, baudrate=Connector.baudrate, timeout=3)
        if not p.isOpen():
            raise Exception('Cannot open port ' + port)
        p.setDTR(False)     #chip reset
        time.sleep(0.3)
        p.setDTR(True)
        ans = p.readline() #because of chip reset on port open
        if not ans:        #it should not be scilent after reset
            raise Exception('No answer')

        def strSplit(str, n):
            cnt = 0
            while cnt < len(str):
                inc = min(n, len(str)-cnt)
                yield str[cnt : cnt+inc]
                cnt += inc

        setStr = '\r\nCONFIG_V1: ' + Connector.pack(conf) + '\r\n'
        if Connector.debug:
            print(setStr)
        # p.write(setStr) #set config
        for prt in strSplit(setStr, 30):
            p.write(prt)
            time.sleep(0.1)

        p.timeout = 0.5
        ok = False
        for i in range(0, 30):
            ans = p.readline()
            if Connector.debug:
                print("RX: " + ans)
            if ans.startswith('SET_OK'):
                ok = True
                break
            if ans.startswith('SET_ERR'):
                raise Exception('Device rejected config')
        p.close()
        if not ok:
            raise Exception('No answer')
        return

    @staticmethod
    def unpack(buff):
        buff = base64.b64decode(buff)
        if Connector.debug:
            print("ANS SZ: " + str(len(buff)))
        buff = buff[:-21] #drop time
        crc = struct.unpack_from('B', buff)[0]
        buff = buff[1:] #drop crc
        if crc != Connector.crc(buff):
            raise Exception('Read CRC error')
        conf = {}
        conf['numb'] = struct.unpack_from('13s', buff)[0].rstrip('\0')
        buff = buff[13:]
        buff = buff[3:] #lang
        conf['dRep'] = struct.unpack_from('6s', buff)[0].rstrip('\0')
        buff = buff[6:]
        (conf['minT'], conf['maxT']) = struct.unpack_from('bb', buff)
        buff = buff[2:]
        conf['flags'] = int(struct.unpack_from('B', buff)[0])
        buff = buff[1:]
        sSz = int(struct.unpack_from('B', buff)[0])
        if sSz < 1:
            raise Exception('Broken config: schedule size is 0')
        if sSz > 15:
            raise Exception('Broken config: schedule size is more then 15')
        buff = buff[1:]
        conf['sched'] = []
        for i in range(0, sSz):
            s = {}
            (s['days'], s['events'], s['action']) = struct.unpack_from('BBB', buff)
            buff = buff[3:]
            (s['fromMin'], s['toMin']) = struct.unpack_from('HH', buff)
            buff = buff[4:]
            conf['sched'].append(s)
        if Connector.debug:
            print(conf)
        return conf

    @staticmethod
    def pack(conf):
        if Connector.debug:
            print(conf)
        buff = ''
        buff += struct.pack('15s', conf['numb'])
        buff += struct.pack('3s', 'ru') #not used
        buff += struct.pack('6s', conf['dRep'])
        buff += struct.pack('bb', conf['minT'], conf['maxT'])
        buff += struct.pack('B', conf['flags'])
        buff += struct.pack('B', len(conf['sched']))
        buff += Connector.schEntrys(conf['sched'])
        crc = Connector.crc(buff)
        buff = struct.pack('B', crc) + buff
        buff += struct.pack('21s', conf['time'])
        if Connector.debug:
            print("Packed config size: " + str(len(buff)))
        return base64.b64encode(buff)

    @staticmethod
    def schEntrys(sched):
        buff = ''
        for i in range(0, Connector.schedMaxSz):
            if i < len(sched):
                s = sched[i]
                buff += struct.pack('BBB', s['days'], s['events'], s['action']) + struct.pack('HH', s['fromMin'], s['toMin'])
            else:
                buff += struct.pack('BBB', 0, 0, 0) + struct.pack('HH', 0, 0)
        return buff
        
    @staticmethod
    def crc(buff):
        tmp = 0
        for c in buff:
            tmp = (tmp + ord(c))&0xFF
        return tmp

#test
#conf = {'numb' : '+799911111133', 'dRep' : '20:00', 'minT':-30, 'maxT':40, 'time':'01.01.19 12:32:11'}
#code = Connector.pack(conf)
#print(code)
#print(Connector.unpack(code))