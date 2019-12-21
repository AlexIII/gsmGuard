/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include <RTClib.h>
#include <Wire.h>
#include "TempHistory.h"

#define PIR_RELAX_TIME_MIN 20

#define LIGHT_PIN A0
#define TEMP_PIN 9
#define BAT_PIN A1
#define DOOR_PIN 7
#define PIR_PIN 6
#define EXT1_PIN 10
#define EXT2_PIN 11
#define BUZZER_PIN 8
#define POWER_PIN 13
#define USB_POWER_DETECT 12

TempHistory tempHistory(2UL*3600UL);
DS3231 rtc;

class Hardware {
  Hardware();
public:
  struct TempStat {
    int8_t min;
    int8_t max;
    int8_t avg;
  };

  struct Sensors {
    uint8_t light;  //%
    int8_t temp;    //deg. Celsius
    uint8_t bat;    // bat/10 = volts
    bool doorIsOpen;
    bool move;
    bool ext1;
    bool ext2;
  };

  static TempStat& tempStat() {
    static TempStat t{-127, -127, -127};
    return t;
  }
  static void init() {
    pinMode(USB_POWER_DETECT, INPUT);
    analogReference(INTERNAL);
    pinMode(DOOR_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(EXT1_PIN, INPUT);
    pinMode(EXT2_PIN, INPUT);
    pinMode(EXT2_PIN, INPUT);
    digitalWrite(EXT1_PIN, HIGH);
    digitalWrite(EXT2_PIN, HIGH);
    pinMode(BUZZER_PIN, OUTPUT);
    beep(false);
    pwrOn();
    if(!rtc.isrunning()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  static bool isExtPower() {
    return digitalRead(USB_POWER_DETECT);
  }
  static void pwrOn() {
    digitalWrite(POWER_PIN, HIGH);
    pinMode(POWER_PIN, OUTPUT);
    delay(1);
    rtc.begin();
  }
  static void pwrOff() {
    Wire.end();
    digitalWrite(POWER_PIN, LOW);
    pinMode(POWER_PIN, INPUT);
  }
  static Sensors sensors() {
    const DateTime cur = now();
    const int8_t t = temp(cur);
    updTempStat(t, cur);

    if((cur - tempHistory.lastEntryTime()).totalseconds() > 2UL*3600UL) //2 hr.
      tempHistory.update(t, cur);

    return {
      light(),
      t,
      bat(),
      digitalRead(DOOR_PIN),
      pir(cur),
      !digitalRead(EXT1_PIN),
      !digitalRead(EXT2_PIN)
    };
  }
  static DateTime now() {
    return rtc.now();
  }
  static void setTime(const char* date) { //"DD.MM.YYYY hh:mm:ss"
    rtc.adjust(DateTime(date, date+11));
  }
  static void beep(const bool on) {
    if(on) {
      //pinMode(BUZZER_PIN, OUTPUT);
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      //pinMode(BUZZER_PIN, INPUT);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  static void beep(const int sec) {
    const uint32_t end = millis() + sec*1000UL;
    while(end > millis()) {
      beep(true);
      delay(200);
      beep(false);
      delay(50);
    }
  }

  static void updButVoltage() {
    bat() = analogRead(BAT_PIN) / 21U;
  }
private:
  static int8_t temp(const DateTime &cur) {
    return round(rtc.getTemp());
  }
  static uint8_t light() {
    return (uint32_t(analogRead(LIGHT_PIN))*100)/1024UL;
  }
  static uint8_t& bat() {
    static uint8_t val = 0;
    return val;
  }
  static bool pir(const DateTime &curTime) {
#ifdef PIR_RELAX_TIME_MIN
    static DateTime lastOn;
    bool cur = digitalRead(PIR_PIN);
    if(cur) {
      if((curTime - lastOn).totalseconds() < PIR_RELAX_TIME_MIN*60)
        cur = false;
      lastOn = curTime;
    }
    return cur;
#else
    return digitalRead(PIR_PIN);
#endif
  }
  
  static void updTempStat(const int8_t t, const DateTime &cur) {
    //for avg
    static uint16_t cnt = 1; //5min intervals
    static DateTime last;
    
    //daily reset
    TempStat &ts = tempStat();
    static uint8_t statTempResetDay = 0;
    if(statTempResetDay != cur.day()) {
      statTempResetDay = cur.day();
      //if(cnt > 1) tempHistory.update(ts, cur);
      resetTempStat(t);
      cnt = 1;
      last = cur;
      return;
    }

    //update
    if(ts.min > t) ts.min = t;
    if(ts.max < t) ts.max = t;
    if((cur - last).totalseconds() > 300) {
      last = cur;
      ts.avg = (int32_t(ts.avg)*cnt + t) / (cnt+1);
      ++cnt;
    }
  }
  static void resetTempStat(const int8_t t) {
    tempStat().min = tempStat().max = tempStat().avg = t;
  }
};

#endif
