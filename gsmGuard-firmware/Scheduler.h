/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#include "Config.h"

class Scheduler {
  DateTime nextTry; //init to now
  uint8_t attempt = 0;
  bool reportStatus = false;//true;
  struct {
    uint8_t hour = 20;
    uint8_t min = 0;
    bool reportedToday = false;
    bool isToReport(const DateTime &now) {
      if(!reportedToday && now.hour() >= hour && now.minute() >= min) {
        reportedToday = true;
        return true;
      }
      if(reportedToday && now.hour() < hour)
        reportedToday = false;
      return false;
    }
  } dailySatatus;
  Status &status;
  Reporter &reporter;
public:
  Scheduler(const Config &config, Status &status, Reporter &reporter) : status(status), reporter(reporter) {
    //parse and set daily report time
    const char* const sep = strchr(config.dailyReportTime, ':');
    if(sep) {
      dailySatatus.hour = atoi(config.dailyReportTime);
      dailySatatus.min = atoi(sep+1);
    } else dailySatatus.hour = 24;
  }
  
  void poll() {
    const DateTime now = Hardware::now();
    if(dailySatatus.isToReport(now)) { //check daily report time
      DBG(F("Daily report time"));
      reportStatus = true;
    }
    if(!isSomethingToReport()) { //nothing to report
      DBG(F("Nothing to report"));
      return;
    }
    if(nextTry > now) { //try later
      DBG(F("Next try in"), (nextTry-now).totalseconds()/60+1, F("min."));
      return;
    }
    if(sendAll()) { //success
      DBG(F("Send all: success"));
      clearNonSMS(); //temporary
      attempt = 0;
      return;
    }
    //failure
    DBG(F("Send all: fail"));
    nextTry = now + TimeDelta(nextAttemptDelaySec());
  }

  uint16_t nextAttemptDelaySec() {
    if(attempt < 0xFF) ++attempt;
    switch(attempt) {
      case 0: return 0;
      case 1: return 2*60;
      case 2: return 5*60;
      case 3: return 10*60;
      case 4: return 20*60;
      case 5:
      case 6: return 40*60;
    }
    return 720U*60U;
  }

  bool isSomethingToReport() const {
    return reportStatus || status.events.isUnreported();
  }

  bool sendAll() {
    if(reportStatus) {
      auto &status = this->status;
      if(!reporter.send([&status](Print &&p){status.print(p);}))
          reportStatus = false;
    }
    bool ok = false;
    if(!reportStatus) ok = sendEvents();
    if(ok) Hardware::updButVoltage();
    reporter.pwrDwnModem();
    return ok;
  }
  
  bool sendEvents() const {
    bool makeCall = false, siren = false;
    for(int i = 0; i < status.events.size(); ++i) {
      Event e;
      status.events.get(i, e);
      if(e.isOk()) {
        if(e.reportAs(Event::SMS) && reporter.send([&e](Print &&p){e.print(p);})) return false; //failed to send sms
        if(e.reportAs(Event::CALL))
          makeCall = true;
        if(e.reportAs(Event::SIREN))
          siren = true;
        //clear actions
        e.action = Event::NO_ACTION;
        status.events.update(i, e);
      }
    }
    if(makeCall) {
      DBG(F("Making a call..."));
      delay(3000);
      reporter.call();
    }
    if(siren) {
      DBG(F("Siren is on"));
      Hardware::beep(30);
    }
    return true;
  }

  void clearNonSMS() {
    for(int i = 0; i < status.events.size(); ++i) {
      Event e;
      status.events.get(i, e);
      if(e.isOk() && e.action != Event::NO_ACTION) {
        e.action = Event::NO_ACTION;
        status.events.update(i, e);
      }
    }  
  }
};
