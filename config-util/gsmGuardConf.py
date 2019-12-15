#! /usr/bin/env python
# -*- coding: utf-8 -*-

# pip install pyserial
# pip install matplotlib

import Tkinter
from Tkinter import StringVar, IntVar
import ttk
import tkMessageBox
import os
from datetime import datetime
import re
import traceback
from Connector import Connector
from eventHist import EventHistory
from tempPlot import TempPlot
import sys
from Local import Local, setLocale, getLocales, getCurrentLocale
from resource_path import resource_path

#setLocale('RU')
appVersion = "1.0"

class ScheduleEntry:
    def __init__(self, root, row, deleteButton = None):
        self.vars = {}
        widgets = []
        
        pady = 10
        padx = 3
        #day of the week
        for i in range(0, 7):
            w = 'w'+str(i)
            self.vars[w] = IntVar()
            t = ttk.Checkbutton(root, variable = self.vars[w])
            t.grid(column = i+1, row = row, pady = (pady, 0), sticky = 'ew')
            widgets.append(t)
            if not deleteButton:
                self.vars[w].set(1)
                t.config(state = 'disable')

        #time from
        self.vars['fromHr'] = StringVar()
        t = ttk.Entry(root, width=2, textvariable = self.vars['fromHr'])
        t.grid(column = 8, row = row, padx = (padx, 0), pady = (pady, 0))
        widgets.append(t)

        t = ttk.Label(root, text = ":")
        t.grid(column = 9, row = row, pady = (pady, 0))
        widgets.append(t)

        self.vars['fromMin'] = StringVar()
        t = ttk.Entry(root, width=2, textvariable = self.vars['fromMin'])
        t.grid(column = 10, row = row, padx = (0, padx), pady = (pady, 0))
        widgets.append(t)

        #time to
        self.vars['toHr'] = StringVar()
        t = ttk.Entry(root, width=2, textvariable = self.vars['toHr'])
        t.grid(column = 11, row = row, padx = (padx, 0), pady = (pady, 0))
        widgets.append(t)

        t = ttk.Label(root, text = ":")
        t.grid(column = 12, row = row, pady = (pady, 0))
        widgets.append(t)

        self.vars['toMin'] = StringVar()
        t = ttk.Entry(root, width=2, textvariable = self.vars['toMin'])
        t.grid(column = 13, row = row, padx = (0, padx), pady = (pady, 0))
        widgets.append(t)

        if not deleteButton:
            self.vars['fromHr'].set('00')
            self.vars['fromMin'].set('00')
            self.vars['toHr'].set('00')
            self.vars['toMin'].set('00')
            widgets[-1].config(state = 'disable')
            widgets[-3].config(state = 'disable')
            widgets[-4].config(state = 'disable')
            widgets[-6].config(state = 'disable')

        #events
        self.vars['door'] = IntVar(value = 0 if deleteButton else 1)
        t = ttk.Checkbutton(root, variable = self.vars['door'])
        t.grid(column = 14, row = row, padx = (padx, 0), pady = (pady, 0))
        widgets.append(t)

        self.vars['move'] = IntVar(value = 0 if deleteButton else 1)
        t = ttk.Checkbutton(root, variable = self.vars['move'])
        t.grid(column = 15, row = row, pady = (pady, 0))
        widgets.append(t)

        self.vars['light'] = IntVar(value = 0 if deleteButton else 1)
        t = ttk.Checkbutton(root, variable = self.vars['light'])
        t.grid(column = 16, row = row, padx = (0, padx), pady = (pady, 0))
        widgets.append(t)

        #actions
        self.vars['sms'] = IntVar(value = 0 if deleteButton else 1)
        t = ttk.Checkbutton(root, variable = self.vars['sms'])
        t.grid(column = 17, row = row, padx = (padx, 0), pady = (pady, 0))
        widgets.append(t)

        self.vars['call'] = IntVar(value = 0 if deleteButton else 1)
        t = ttk.Checkbutton(root, variable = self.vars['call'])
        t.grid(column = 18, row = row, pady = (pady, 0))
        widgets.append(t)

        self.vars['buzz'] = IntVar(value = 0 if deleteButton else 1)
        t = ttk.Checkbutton(root, variable = self.vars['buzz'])
        t.grid(column = 19, row = row, padx = (0, padx), pady = (pady, 0))
        widgets.append(t)

        #delete entry
        if deleteButton:
            self.deleteButton = deleteButton
            t = ttk.Button(root, text = "X", width = 3, command = lambda: self.delete())
            t.grid(column = 20, row = row, padx = padx, pady = (pady, 0))
            widgets.append(t)

        self.widgets = widgets

    def delete(self):
        for w in self.widgets:
            w.destroy()
        if self.deleteButton:
            self.deleteButton(self)

    def validate(self):
        validTime = lambda h, m: (
            h.isdigit() and m.isdigit()
            and int(h) >= 0 and int(h) <= 23
            and int(m) >= 0 and int(m) <= 59)
        if (not validTime(self.vars['fromHr'].get(), self.vars['fromMin'].get())
            or not validTime(self.vars['toHr'].get(), self.vars['toMin'].get())):
                raise Exception(Local('Incorrect time in the schedule'))
        fromMin = int(self.vars['fromHr'].get())*60 + int(self.vars['fromMin'].get())
        toMin = int(self.vars['toHr'].get())*60 + int(self.vars['toMin'].get())
        
        days = 0
        for i in range(0, 7):
            w = 'w'+str(i)
            if self.vars[w].get():
                days |= (1<<i)
        if not days:
            raise Exception(Local('Select at least one day of the week'))
            
        events = 0
        i = 0
        for e in ['door', 'move', 'light']:
            if self.vars[e].get():
                events |= (1<<i)
            i += 1
        if not events:
            raise Exception(Local('Select at least one event'))
            
        action = 0
        i = 0
        for a in ['sms', 'call', 'buzz']:
            if self.vars[a].get():
                action |= (1<<i)
            i += 1
        
        return (days, fromMin, toMin, events, action)
        
    def set(self, vals):
        for i in range(0, 7):
            w = 'w'+str(i)
            self.vars[w].set(bool( vals['days'] & (1<<i) ))
            
        setTime = lambda mins, h, m : (h.set(mins/60), m.set(mins%60))
        setTime(vals['fromMin'], self.vars['fromHr'], self.vars['fromMin'])
        setTime(vals['toMin'], self.vars['toHr'], self.vars['toMin'])
        
        i = 0
        for e in ['door', 'move', 'light']:
            self.vars[e].set(bool(  vals['events'] & (1<<i) ))
            i += 1

        i = 0
        for e in ['sms', 'call', 'buzz']:
            self.vars[e].set(bool(  vals['action'] & (1<<i) ))
            i += 1
            
        return None
        
    def get(self):
        v = self.validate()
        return {'days': v[0], 'fromMin': v[1], 'toMin': v[2], 'events': v[3], 'action': v[4]}

    @staticmethod
    def labels(root, addFun):
        ttk.Label(root, text = Local('Day of the week')).grid(padx = 3,   column = 1,     columnspan = 7, row = 1)
        ttk.Label(root, text = Local('from')).grid(padx = 3,             column = 8,     columnspan = 3, row = 1)
        ttk.Label(root, text = Local('to')).grid(padx = 3,            column = 11,    columnspan = 3, row = 1)
        ttk.Label(root, text = Local('event')).grid(padx = 3,       column = 14,    columnspan = 3, row = 1)
        ttk.Label(root, text = Local('action')).grid(padx = 3,      column = 17,    columnspan = 3, row = 1)

        ttk.Label(root,  text=Local('mo')).grid(column=1, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('tu')).grid(column=2, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('we')).grid(column=3, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('th')).grid(column=4, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('fr')).grid(column=5, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('sa')).grid(column=6, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('su')).grid(column=7, row=2, sticky = 'news')

        ttk.Label(root,  text=Local('hh : mm')).grid(column=8, row=2, columnspan = 3)
        ttk.Label(root,  text=Local('hh : mm')).grid(column=11, row=2, columnspan = 3)

        ttk.Label(root,  text=Local('door')).grid(column=14, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('move.')).grid(column=15, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('light')).grid(column=16, row=2, sticky = 'news')

        ttk.Label(root,  text="SMS").grid(column=17, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('call')).grid(column=18, row=2, sticky = 'news')
        ttk.Label(root,  text=Local('siren')).grid(column=19, row=2, sticky = 'news')
		
        ttk.Button(root, text = "+", width = 3, command = addFun).grid(column=20, row=1, rowspan = 2, padx = 3, pady = 3)


class GUI:
    def run(self):
        self.maxSentries = 15
        if len(Connector.getPorts()) == 0:
            tkMessageBox.showerror(Local('Error'), Local('Serial port not found'))
            os._exit(0)
        self.reload = False
        self.protScanTask = None
        self.tempWindow = None
        self.histWindow = None
        
        #window
        root = self.root = Tkinter.Tk()
        root.resizable(False, False)
        root.title('GSMguard Configuration v.' + appVersion)
        root.iconbitmap(resource_path('./gg-icon.ico'))

        fleft = ttk.Frame(root)
        fleft.pack(side = 'left', anchor = 'n')
        fright = ttk.LabelFrame(root, text = Local('Schedule'))
        fright.pack(side = 'right', anchor = 'n', padx = 3, pady = 3, fill = 'y')
        
        self.makeLocaleSettings(fleft)
        self.makePortSettings(fleft)
        self.makeMainSettings(fleft)
        self.makeScheduleSettings(fright)

        self.updPortList()
        root.mainloop()
        return self.reload

    #------------------ GUI CONSTRUCTION -----------------------
    def makeLocaleSettings(self, root):
        localeFrame = ttk.LabelFrame(root, text = Local('Localization'))
        localeFrame.pack(side = 'top', fill = 'x', padx = 3, pady = 3)
        langFrame = ttk.Frame(localeFrame)
        langFrame.pack(side = 'top', fill = 'x')
        ttk.Label(langFrame, text = Local('Language:')).pack(side = 'left', padx = 3, pady = 3)
        def changeLang(x):
            setLocale(x)
            self.reload = True
            if self.protScanTask is not None:
                self.root.after_cancel(self.protScanTask)
            self.root.destroy()
        ttk.OptionMenu(langFrame, StringVar(), getCurrentLocale(), *getLocales(), command = changeLang).pack(side = 'left', padx = 3, pady = 3)

    def makePortSettings(self, root):
        connFrame = ttk.LabelFrame(root, text = Local('Connection'))
        connFrame.pack(side = 'top', fill = 'x', padx = 3, pady = 3)
        portFrame = ttk.Frame(connFrame)
        portFrame.pack(side = 'top')
        ttk.Label(portFrame, text = Local('Port')).pack(side = 'left', padx = 3, pady = 3)
        self.port = StringVar()
        self.portOpt = ttk.OptionMenu(portFrame, self.port)
        self.portOpt.pack(side = 'left', padx = 3, pady = 3)
        ttk.Button(portFrame, text = Local('Read'), command = lambda: self.readButton()).pack(side = 'left', padx = 3, pady = 3)
        ttk.Button(portFrame, text = Local('Write'), command = lambda: self.writeButton()).pack(side = 'left', padx = 3, pady = 3)
        self.readEventHist = IntVar(value = 1)
        ttk.Checkbutton(connFrame, text = Local('Read event history'), variable=self.readEventHist).pack(side = 'top', anchor = 'w', padx = 3, pady = 3)
        self.readTempStat = IntVar(value = 1)
        ttk.Checkbutton(connFrame, text = Local('Read temperature statistics'), variable=self.readTempStat).pack(side = 'top', anchor = 'w', padx = 3, pady = 3)
        self.infoLbl = StringVar()
        ttk.Label(connFrame, textvariable=self.infoLbl, foreground = 'red').pack(side = 'top')

    def makeMainSettings(self, root):
        mainConfFrame = ttk.LabelFrame(root, text = Local('Alarms'))
        mainConfFrame.pack(side = 'top', fill = 'x', padx = 3, pady = 3)

        #phone number
        phoneFrame = ttk.Frame(mainConfFrame)
        phoneFrame.pack(side = 'top', padx = 3, pady = 3, anchor="w")
        ttk.Label(phoneFrame, text = Local('Tel.')).pack(side = 'left', padx = 3, pady = 3)
        self.phone = StringVar(value = '+12225566123')
        ttk.Entry(phoneFrame, width=20, textvariable=self.phone).pack(side = 'left', padx = 3, pady = 3)

        #daily report time
        dRepFrame = ttk.Frame(mainConfFrame)
        dRepFrame.pack(side = 'top', padx = 3, pady = 3, anchor="w")
        self.repOn = IntVar(value = 1)
        ttk.Checkbutton(dRepFrame, text = Local('Daily report'), variable=self.repOn, command = lambda: drepEn(self.repOn.get())).pack(side = 'left', padx = 3, pady = 3)
        self.repHr = StringVar(value = '20')
        rm = ttk.Entry(dRepFrame, width=2, textvariable=self.repHr)
        rm.pack(side = 'left')
        ttk.Label(dRepFrame, text = ":").pack(side = 'left')
        self.repMin = StringVar(value = '00')
        rh = ttk.Entry(dRepFrame, width=2, textvariable=self.repMin)
        rh.pack(side = 'left')
        def drepEn(v):
            if v:
                rm.config(state='enabled')
                rh.config(state='enabled')
            else:
                rm.config(state='disabled')
                rh.config(state='disabled')

        #temperature report
        tempFrame = ttk.Frame(mainConfFrame)
        tempFrame.pack(side = 'top', padx = 3, pady = 3, anchor="w")
        ttk.Label(tempFrame, text = Local('Temperature alarm')).pack(side = 'top', padx = 3, pady = 3)
        ttk.Label(tempFrame, text = Local('min.')).pack(side = 'left')
        self.tempMin = StringVar(value = '-30')
        ttk.Entry(tempFrame, width=4, textvariable=self.tempMin).pack(side = 'left')
        ttk.Label(tempFrame, text = "°С    " + Local('max.')).pack(side = 'left')
        self.tempMax = StringVar(value = '40')
        ttk.Entry(tempFrame, width=4, textvariable=self.tempMax).pack(side = 'left')
        ttk.Label(tempFrame, text = "°С").pack(side = 'left')

    def makeScheduleSettings(self, root):
        self.sEntries = []
        self.sEntryCnt = 4
        self.addSEntry = lambda: self.addScheduleEntry(root)
        ScheduleEntry.labels(root, self.addSEntry)
        self.sEntries.append(ScheduleEntry(root, 3))

    def addScheduleEntry(self, root):
        if len(self.sEntries) >= self.maxSentries:
            return
        self.sEntries.append(ScheduleEntry(root, self.sEntryCnt, lambda v: self.sEntries.remove(v)))
        self.sEntryCnt += 1

    #------------------ LOGIC -----------------------
    def updPortList(self):
        ports = Connector.getPorts()
        tmp = self.port.get()
        self.portOpt.set_menu(tmp if tmp else ports[0] if len(ports) else '', *ports)
        self.protScanTask = self.root.after(2000, lambda: self.updPortList())

    def readButton(self):
        self.infoLbl.set(Local('Please wait...'))
        self.root.update()
        try:
            conf = Connector.read(self.port.get(), self.readEventHist.get(), self.readTempStat.get())
            self.spreadData(conf)
            
            if self.histWindow:
                self.histWindow.destroy()
                self.histWindow = None
            if self.tempWindow:
                self.tempWindow.destroy() 
                self.tempWindow = None
                
            if self.readEventHist.get():
                self.histWindow = Tkinter.Toplevel()
                x = self.root.winfo_x()
                y = self.root.winfo_y() + self.root.winfo_height() + 40
                self.histWindow.geometry('+%d+%d' % (x,y))
                EventHistory(self.histWindow, conf['eventHist'])
            if self.readTempStat.get():
                self.tempWindow = Tkinter.Toplevel()
                x = self.root.winfo_x() + self.root.winfo_width() + 10
                y = self.root.winfo_y()
                self.tempWindow.geometry('+%d+%d' % (x,y))
                TempPlot(self.tempWindow, conf['tempHist'])
                
        except Exception as e:
            tkMessageBox.showerror(Local('Error'), str(e))
            traceback.print_exc()
        finally:
            self.infoLbl.set('')

    def writeButton(self):
        self.infoLbl.set(Local('Please wait...'))
        self.root.update()
        try:
            self.validate()
            conf = self.gatherData()
            Connector.write(self.port.get(), conf)
            tkMessageBox.showinfo('Info', Local('Success!'))
        except Exception as e:
            tkMessageBox.showerror(Local('Error'), str(e))
            traceback.print_exc()
        finally:
            self.infoLbl.set('')
        #print(self.gatherData())

    def gatherData(self):
        data = {}
        data['numb'] = self.phone.get()
        if self.repOn.get():
            data['dRep'] = self.repHr.get()+':'+self.repMin.get()
        else:
            data['dRep'] = 'none'
        data['minT'] = int(self.tempMin.get())
        data['maxT'] = int(self.tempMax.get())
        data['time'] = datetime.now().strftime("%d-%m-%Y %H:%M:%S")
        data['sched'] = []
        for e in self.sEntries:
            data['sched'].append(e.get())
        return data

    def spreadData(self, data):
        self.phone.set(data['numb'])
        if data['dRep'] == 'none':
            self.repOn.set(False)
        else:
            self.repOn.set(True)
            t = data['dRep'].split(':')
            self.repHr.set(t[0])
            self.repMin.set(t[1])
        self.tempMin.set(data['minT'])
        self.tempMax.set(data['maxT'])
        
        #make enties
        while len(self.sEntries) < len(data['sched']):
            self.addSEntry()
        while len(self.sEntries) > len(data['sched']):
            self.sEntries[len(self.sEntries)-1].delete()
        for i in range(0, len(self.sEntries)):
            self.sEntries[i].set(data['sched'][i])
            
    def validate(self):
        if not re.match(r'^\+?\d{11}$', self.phone.get()):
            raise Exception(Local('Success!'))
        if self.repOn.get() and (
            not self.repHr.get().isdigit()
            or not self.repMin.get().isdigit()
            or int(self.repHr.get()) > 23 
            or int(self.repMin.get()) > 59 ):
            raise Exception(Local('Incorrect phone number'))
        try:
            min = int(self.tempMin.get())
            max = int(self.tempMax.get())
        except:
            raise Exception(Local('Incorrect report time'))
        if (min < -80 or min > 80
            or max < -80  or max > 80
            or not min < max ):
            raise Exception(Local('Incorrect temperature range'))
        for e in self.sEntries:
            e.validate()

if __name__ == "__main__":
    reload(sys)
    sys.setdefaultencoding('utf-8')
    while GUI().run() is True:
        pass