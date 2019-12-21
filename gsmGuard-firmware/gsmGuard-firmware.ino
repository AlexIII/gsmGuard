/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

/*
Libraries:
https://github.com/AlexIII/TinyGSM (modified, pull request is pending)
https://github.com/Densaugeo/base64_arduino
https://github.com/AlexIII/RTCLib (modified, pull request is pending)
https://github.com/AlexIII/EEvar

Board: Arduino Nano / Pro / pro mini - 8MHz
*/ 

/* Select clock */
#define F_CPU_8MHZ
//#define F_CPU_16MHZ

/* Select locale */
//#define LOCAL_RU
#define LOCAL_EN

#define DEBUG_BAUDRATE 250000
#define AT_BAUDRATE 19200

#include <avr/sleep.h>
#define SerialMon Serial
#define TINY_GSM_DEBUG SerialMon
#include <SoftwareSerial.h>
#include "Reporter.h"
#include "Status.h"
#include "Scheduler.h"
#include "Config.h"

#if F_CPU != 8000000
  #error "F_CPU is not 8 MHz! Select board with 8MHz clock even if you actually use 16MHz. (in which case also #define F_CPU_16MHZ at the beginning of *.ino file)"
#endif

ConfigSerial config;
Status status(config);
SoftwareSerial SerialAT(4, 3); // RX, TX
Reporter reporter(SerialAT, config.phoneNumber);
Scheduler scheduler(config, status, reporter);

enum ConfigAction : uint8_t {
  NONE,
  CONFIG_SET,
  CONFIG_REQ,
  EVENTS_REQ,
  TEMP_REQ
};

ConfigAction getConfigStr(Stream &stream, char* confBuff, const size_t confBuffSz, const bool wait = true) {
  if(!wait && !stream.available()) return NONE;
  Stream::MultiTarget targets[] = {
    {"\nCONFIG_V1: ", 12, 0},
    {"\nCONFIG_REQ",  11, 0},
    {"\nEVENTS_REQ",  11, 0},
    {"\nTEMP_REQ",     9, 0}
  };
  const int res = stream.findMulti(targets, 4) + 1;
  if(!res) return NONE;
  if(res == CONFIG_SET) {
    const int r = stream.readBytesUntil('\n', confBuff, confBuffSz-1);
    if(!r) return NONE;
    if(r >= confBuffSz-1) {
      DBG(F("Error: Config buffer overflow."));
      return NONE;
    }
    confBuff[r] = 0; //add string terminator
  }
  while(stream.read() != -1); //flush buffer, we've got our answer
  return ConfigAction(res);
}

void csvBegin() {
  SerialMon.println(F("\r\n----CSV BEGIN----"));
}
void csvEnd() {
  SerialMon.println(F("----CSV END----"));
}

void dumpEventHistCSV() {
  csvBegin();
  status.events.dumpCSV(SerialMon);
  csvEnd();
}

void dumpTempCSV() {
  csvBegin();
  tempHistory.dumpCSV(SerialMon);
  csvEnd();
}

bool receiveCommand(const bool wait = true) {
    char confBuffer[(8*sizeof(config))/6 + 20];
    const ConfigAction act = getConfigStr(SerialMon, confBuffer, sizeof(confBuffer), wait);
    
    if(act) {
      DBG(F("REQ RECEIVED"));
      if(act == CONFIG_SET) {
        DBG(F("Config string received:"), confBuffer);
        if(config.formBASE64(confBuffer)) {
          DBG(F("New config successfully applyed!"));
          SerialMon.println(F("\r\nSET_OK"));
        } else {
          DBG(F("Error: wrong config."));
          SerialMon.println(F("\r\nSET_ERR"));
        }
        return true;
      } else if(act == CONFIG_REQ) {
        DBG(F("Config request"));
        SerialMon.print(F("\r\nCONFIG_V1: "));
        config.toBASE64(SerialMon);
        SerialMon.println();
        return true;
      } else if(act == EVENTS_REQ) {
        DBG(F("Event history request"));
        dumpEventHistCSV();
        return true;
      } else if(act == TEMP_REQ) {
        DBG(F("Temperature history request"));
        dumpTempCSV();
        return true;
      }
    }
    return false;
}

void setup() {
  /* clock */
#ifndef F_CPU_8MHZ
  CLKPR = (1<<CLKPCE);
  CLKPR = (1<<CLKPS0); //clock prescale = 2
#endif
  /* power saving */
  ACSR = (1<<ACD); //disable ACOMP
  
  SerialMon.begin(DEBUG_BAUDRATE);
  SerialMon.setTimeout(2000);
  delay(50);
  SerialAT.begin(AT_BAUDRATE);
  
  Hardware::init();
  delay(300);
  status.init();
  DBG(F("System inited."));

  //reset history
  //tempHistory.reset();
  //status.events.reset();
  //tempHistory.baseTime.time = Hardware::now().unixtime();
  //tempHistory.baseTime.save();

  /*
  //PIR test
  while(1) {
      char t[] = "DD.MM.YY hh:mm:ss";
      const auto d = Hardware::now();
     DBG(F("Time:"), d.format(t));
    if(Hardware::pir(d)) {
      digitalWrite(LED_BUILTIN, 0);
      delay(1000);
    }
    digitalWrite(LED_BUILTIN, 1);
    delay(100);
  }
  */

  if(Hardware::isExtPower() || receiveCommand(true)) { //We're being configurated, so 
    char t[] = "DD.MM.YY hh:mm:ss";
    DBG(F("Time:"), Hardware::now().format(t));
    if(Hardware::isExtPower()) DBG(F("USB connection detected. Awaiting config."));
    status.events.clearActions(); //no need to report old events,
    while(1) {
      receiveCommand(); //no need to run the main program.
    }
  }
  
  DBG(F("Free EEPROM bytes:"), EEPROMallocator::free());
  if(!config.chkCRC()) { //broken config
    status.events.reset(); //reset memory
    tempHistory.reset();
    SerialMon.println(F("Broken config.\r\nSystem halted."));
    while(1); 
  }

/*
  tempHistory.update({-20, -10, -15}, Hardware::now());
  tempHistory.update({-21, -11, -16}, Hardware::now());
  tempHistory.update({-22, -12, -17}, Hardware::now());
  tempHistory.update({-23, -13, -18}, Hardware::now());
  tempHistory.update({-20, -10, -15}, Hardware::now());
  tempHistory.update({-17, -3, -10}, Hardware::now());
*/
  sleep_init();
}

ISR(WDT_vect) {}
void sleep_init() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  PCICR |= (1<<PCIE2);
  PCMSK2 |= (1<<PCINT23) | (1<<PCINT22);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void sleep() {
  digitalWrite(LED_BUILTIN, LOW);
  SerialMon.flush();
  SerialMon.end();
  SerialAT.flush();
  SerialAT.end();
  Hardware::pwrOff();

  const uint8_t DB = DDRB, DC = DDRC, DD = DDRD;
  DDRB = 0, DDRC = 0, DDRD = 0;
  const uint8_t PB = PORTB, PC = PORTC, PD = PORTD;
  PORTB = 0, PORTC = 0, PORTD = 0;
  
  asm volatile("wdr");
  WDTCSR |= (1<<WDCE)|(1<<WDE);
  WDTCSR = (1<<WDIE)|(1<<WDP2)|(1<<WDP3)|(1<<WDP0);
  sleep_cpu();
  WDTCSR |= (1<<WDCE)|(1<<WDE);
  WDTCSR = 0;

  PORTB = PB, PORTC = PC, PORTD = PD;
  DDRB = DB, DDRC = DC, DDRD = DD;

  digitalWrite(LED_BUILTIN, HIGH);
  Hardware::pwrOn();
  SerialMon.begin(DEBUG_BAUDRATE);
  SerialAT.begin(AT_BAUDRATE);
}

void loop() {
  /*
  if(SerialAT.available()) SerialMon.write(SerialAT.read());
  if(SerialMon.available()) SerialAT.write(SerialMon.read());
  delay(10);
  return;
  */
  const auto s = millis();
  status.upd();
  DBG(F("Unreported queue size:"), status.events.unreportedCount(Event::ANY));
  char t[] = "DD.MM.YY hh:mm:ss";
  DBG(F("Time:"), Hardware::now().format(t));
  DBG(F("Status:"));
  status.print(TINY_GSM_DEBUG);
  TINY_GSM_DEBUG.println();
  scheduler.poll();
  DBG(F("Cycle time, ms.:"), millis()-s);
  
  sleep();
}
