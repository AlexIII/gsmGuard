/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _EVENT_H_
#define _EVENT_H_

#include <RTClib.h>
#include "Hardware.h"
#include "Local.h"

struct Event {
  enum EventNumber: uint8_t {
    DOOR_OPEN,
    MOVEMENT,
    LIGHT_CHANGED,
    TEMP_HIGH,
    TEMP_LOW,
    BAT_LOW,
    NO_EVENT = 0xFF
  };
  enum Action : uint8_t {
    NO_ACTION = 0,
    SMS       = 1<<0,
    CALL      = 1<<1,
    SIREN     = 1<<2,
    ANY = 0xFF
  }; 
  Event() : n(NO_EVENT) {}
  Event(const EventNumber n, const uint8_t val = 0, const Action action = NO_ACTION) : timestamp(Hardware::now().unixtime()), n(n), val(val), action(action) {}
  uint32_t timestamp;
  EventNumber n;
  uint8_t val;
  Action action;

  static void csvHeader(Stream &s, const char separator) {
    s.print(F("date"));
    s.print(separator);
    s.print(F("event"));
    s.print(separator);
    s.print(F("value"));
  }
  void print(Print& p, const char separator = '\n') {
    char timeStr[] = "DD.MM.YY hh:mm";
    p.print( time().format(timeStr) );
    const char sep[] = {separator, '\0'};
    p.print( sep );
    p.print( name() );
    valStr(p, separator);
  }
  
  bool isOk() const {return n < NO_EVENT;}
  DateTime time() const {
    return DateTime(timestamp);
  }
  operator bool() const {
    return n != NO_EVENT;
  }
  bool reportAs(const Action a) const {
    return action&a;
  }

private:
  const __FlashStringHelper* name() const {
    switch(n) {
      case DOOR_OPEN: return F(STR_EVENT_DOOR_OPEN);
      case LIGHT_CHANGED: return F(STR_EVENT_LIGHT_CHANGE);
      case TEMP_HIGH: return F(STR_EVENT_HIGH_TEMP);
      case TEMP_LOW: return F(STR_EVENT_LOW_TEMP);
      case MOVEMENT: return F(STR_EVENT_MOVEMENT);
      case BAT_LOW: return F(STR_EVENT_BAT_LOW);
    }
    return F("");
  }
  void valStr(Print& p, const char separator) const {
    const char sep[] = {separator, '\0'};
    switch(n) {
      case LIGHT_CHANGED: 
        p.print( sep );
        p.print( F(STR_EVENT_LIGHT ": ") );
        p.print( val );
        p.print( F("%") );
        break;
      case TEMP_HIGH:
      case TEMP_LOW: 
        p.print( sep );
        p.print( F(STR_EVENT_TEMP ": ") );
        p.print( *((int8_t*)&val) );
        p.print( F("*C") );
        break;
      case BAT_LOW: 
        p.print( sep );
        p.print( F(STR_EVENT_BAT ": ") );
        p.print( val/10 );
        p.print( F(".") );
        p.print( val%10 );
        p.print( F("v") );
        break;
      default: break;
    }
  }
};

#endif
