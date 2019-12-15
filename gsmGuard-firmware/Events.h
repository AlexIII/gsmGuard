/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#include "Event.h"
#include "EeRingQueue.h"

class Events : public EeRingQueue<Event, 70> {
public:
  bool findLast(Event &e, const Event::EventNumber n = Event::NO_EVENT) const {
    for(uint8_t i = 0; i < size(); ++i) {
      get(size()-1-i, e);
      if(n == Event::NO_EVENT || e.n == n) return true;
    }
    return false;
  }
  bool isUnreported(const Event::Action act = Event::Action(0xFF)) const {
    for(uint8_t i = 0; i < size(); ++i) {
      Event e;
      get(i, e);
      if(e.action & act) return true;
    }
    return false;
  }
  uint8_t unreportedCount(const Event::Action act) const {
    uint8_t cnt = 0;
    for(uint8_t i = 0; i < size(); ++i) {
      Event e;
      get(i, e);
      if(e.action & act) ++cnt;
    }
    return cnt;
  }
  void clearActions() {
    for(uint8_t i = 0; i < size(); ++i) {
      Event e;
      get(i, e);
      if(e.isOk() && e.action != Event::NO_ACTION) {
        e.action = Event::NO_ACTION;
        update(i, e);
      }
    }    
  }
  void dumpCSV(Stream &s, const char sepsrator = ';') const {
    Event::csvHeader(s, sepsrator);
    s.println();
    for(uint8_t i = 0; i < size(); ++i) {
      Event e;
      get(size()-i-1, e);
      e.print(s, sepsrator);
      s.println();
    }
  }
};
