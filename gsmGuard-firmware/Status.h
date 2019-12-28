/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#include <RTClib.h>

#include "Hardware.h"
#include "Events.h"
#include "Config.h"
#include "Local.h"

class SensorComparator {
  Hardware::Sensors prv;
  uint8_t critLightChange;
  int8_t critMinTemp;
  int8_t critMaxTemp;
  uint8_t minBat = 39; //3.9v
public:
  SensorComparator(const int8_t critMinTemp, const int8_t critMaxTemp, const uint8_t critLightChange = 35) :
    critLightChange(critLightChange), critMinTemp(critMinTemp), critMaxTemp(critMaxTemp) {}
  Event comp(const Hardware::Sensors &cur) {
    const auto e = yeildEvent(cur);
    prv = cur;
    return e;
  }
private:
  Event yeildEvent(const Hardware::Sensors &cur) const {
    if(!prv.doorIsOpen && cur.doorIsOpen) return Event::DOOR_OPEN;
    if(!prv.move && cur.move) return Event::MOVEMENT; 
    if(abs(int(prv.light) - int(cur.light)) > critLightChange) return {Event::LIGHT_CHANGED, cur.light};
    if(cur.temp >= critMaxTemp) return {Event::TEMP_HIGH, *((uint8_t*)&cur.temp)};
    if(cur.temp <= critMinTemp) return {Event::TEMP_LOW, *((uint8_t*)&cur.temp)};
    if(cur.bat <= minBat) return {Event::BAT_LOW, cur.bat};
    return Event::NO_EVENT;
  }
};

struct Status {
  Hardware::Sensors sens;
  Events events;
private:
  constexpr static const uint32_t eventReportTimeoutSec =   20*60UL;    //evry 20 min
  constexpr static const uint32_t tempReportTimeoutSec =    12*60*60UL; //evry 12hr
  constexpr static const uint32_t batReportTimeoutSec =     24*60*60UL; //evry 24hr
  SensorComparator sc;
  const Config &config;
  
public:  
  Status(const Config &config) : sc(config.minTemp, config.maxTemp), config(config) {}
  void init() {
    sens = Hardware::sensors();
    Hardware::updButVoltage();
    sc.comp(sens);
  }
  void upd() {
    sens = Hardware::sensors();
    Event e = sc.comp(sens);
    if(!e) return;

    DBG(F("New event:"));
    e.print(TINY_GSM_DEBUG);
    TINY_GSM_DEBUG.println();
      
    //repeat event report only after timeout
    bool addEvent = false;
    {
      Event prv;
      if(events.findLast(prv, e.n)) {
        uint32_t timeout = eventReportTimeoutSec;
        if(e.n == Event::TEMP_HIGH || e.n == Event::TEMP_LOW) timeout = tempReportTimeoutSec;
        else if(e.n == Event::BAT_LOW) timeout = batReportTimeoutSec;
        
        if((Hardware::now() - prv.time()).totalseconds() > timeout)
          addEvent = true; //timeout has elapsed
        else DBG(F("Event has already been reported."));
      } else addEvent = true; //we havn't reported it yet
    }
    
    if(addEvent) {
      e.action = config.getAction(e);
      events.put(e);
      DBG(F("Event added to the queue with action"), e.action);
    } else DBG(F("Event dropped."));
  }

  void print(Print& p) {
    auto &events = this->events;
    const auto eventDate = [&events](const Event::EventNumber n) -> const char* {
      Event e;
      if(events.findLast(e, n)) {
        static char timeStr[15];
        strcpy(timeStr, "DD.MM.YY hh:mm");
        return e.time().format(timeStr);
      }
      return "";
    };
    
    p.print( F(STR_STATUS_DOOR ": ") );
    p.print( sens.doorIsOpen? F(STR_STATUS_OPENED " [") : F(STR_STATUS_CLOSED " [") );
    p.print( eventDate(Event::DOOR_OPEN) );
    p.print( F("]\n" STR_STATUS_MOVEMENT ": ") );
    p.print( sens.move? F(STR_STATUS_DETECTED "  [") : F(STR_STATUS_NONE "  [") );
    p.print( eventDate(Event::MOVEMENT) );
    p.print( F("]\n" STR_STATUS_TEMP ": ") );
    p.print( sens.temp );
    p.print( F("*C  [" STR_STATUS_MIN " ") );
    p.print( Hardware::tempStat().min );
    p.print( F("*C, " STR_STATUS_MAX " ") );
    p.print( Hardware::tempStat().max );
    p.print( F("*C, " STR_STATUS_MED " ") );
    p.print( Hardware::tempStat().avg );
    p.print( F("*C]\n" STR_STATUS_LIGHT ":  ") );
    p.print( sens.light );
    p.print( F("%\n" STR_STATUS_BAT ":  ") );
    p.print( sens.bat/10 );
    p.print( F(".") );
    p.print( sens.bat%10 );
    p.print( F("v\n" STR_STATUS_EXT "1: ") );
    p.print( sens.ext1 );
    p.print( F("\n" STR_STATUS_EXT "2: ") );
    p.print( sens.ext2 );
  }
  
};
