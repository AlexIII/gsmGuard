/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <base64.hpp>
#include "Hardware.h"
#include "Event.h"
#include "EEvar.h"

class Config : public EEvarCRC<Config> {
public:
  constexpr static uint8_t scheduleMaxSize = 15;
  char phoneNumber[13];
  char lang[3];
  char dailyReportTime[6];
  int8_t minTemp;
  int8_t maxTemp;

  struct SchEntry {
    uint8_t days;
    enum EventSource : uint8_t {
      DOOR_OPEN     = 1<<Event::DOOR_OPEN,
      MOVEMENT      = 1<<Event::MOVEMENT,
      LIGHT_CHANGE  = 1<<Event::LIGHT_CHANGED
    };
    EventSource src;
    Event::Action act;
    uint16_t fromMin;
    uint16_t toMin;

    bool isActive() const {
      const DateTime now = Hardware::now();
      const uint8_t dw = (now.dayOfTheWeek()+6)%7;
      const uint16_t nowMins = now.hour()*60UL + now.minute();
      if(days&(1<<dw)) //if day of the week is right
        if(fromMin == toMin || (nowMins >= fromMin && nowMins < toMin)) //and time is right
          return true;
      return false;
    }
    Event::Action getAction(const SchEntry::EventSource e) const {
      return src & e? act : Event::NO_ACTION;
    }
  };
  uint8_t scheduleSize;
  SchEntry schedule[scheduleMaxSize];

  Config() {}
  Event::Action getAction(const SchEntry::EventSource e) const {
    for(uint8_t i = 0; i < scheduleSize; ++i) {
      const SchEntry &cur = schedule[scheduleSize-i-1];
      DBG(F("SE"), i, cur.src, cur.act);
      if(cur.isActive()) {
        DBG(F("MATCH!"));
        return cur.getAction(e);
      }
      DBG(F("NO FIT"));
    }
    return Event::NO_ACTION;
  }
  Event::Action getAction(const Event &e) const {
    if(e.n > Event::LIGHT_CHANGED) return Event::SMS;
    return getAction(SchEntry::EventSource(1<<e.n));
  }
  bool test() {
    strcpy(phoneNumber, "+79122433841");
    strcpy(lang, "ru");
    strcpy(dailyReportTime, "21:00");
    minTemp = -30;
    maxTemp = 40;
    scheduleSize = 1;
    schedule[0].days = 0xFF;
    schedule[0].src = SchEntry::DOOR_OPEN;
    schedule[0].act = (Event::Action)0xFF;
    schedule[0].fromMin = schedule[0].toMin = 10;
    for(uint8_t i = 1; i < scheduleMaxSize; ++i) {
      schedule[0].days = 0;
      schedule[0].src = (SchEntry::EventSource)0;
      schedule[0].act = (Event::Action)0;
      schedule[0].fromMin = schedule[0].toMin = 0;
    }
    save();
    load();
    return chkCRC();
  }
};

class ConfigSerial : public Config {
  constexpr static int mySz() {
    return sizeof(ConfigSerial) - dataOffset;
  }
public:
  ConfigSerial() {}
  bool formBASE64(const char* str) {
    if(decode_base64_length((uint8_t*)str) != mySz()) {
      DBG(F("Received config: wrong size. Abort."));
      return false;
    }
    decode_base64((uint8_t*)str, (uint8_t*)this + dataOffset);
    if(!chkCRC()) {
      load();
      DBG(F("Received config: wrong crc. Abort."));
      return false;
    }
    save();
    Hardware::setTime(time);
    return true;
  }
  void toBASE64(Stream &s) {
    const uint16_t len = encode_base64_length(mySz())+1;
    char buff[len];
    strcpy(time, "DD.MM.YY hh:mm:ss");
    Hardware::now().format(time);
    encode_base64((uint8_t*)this + dataOffset, mySz(), (uint8_t*)buff);
    s.write(buff);
  }  
private:
  char time[21];  
};

#endif
