/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#include "EeRingQueue.h"
#include <EEvar.h>
  
class TempHistory {
public:
  constexpr static int size = 31*12;
  EEvar<uint32_t> baseTime;
  EeRingQueue<int8_t, size, uint16_t> samples;

  TempHistory(const uint32_t period) : baseTime(0), period(period) {
    baseTime.load();
    last = time(samples.size()-1);
  }

  //call once a day at midnight
  void update(const int8_t temp, const DateTime &now) {
    //reset log if we've lost more than an hour
    const DateTime newNotLaterThan = last + TimeDelta(period + 3600);
    if(last > now || newNotLaterThan < now) samples.reset();
    //update base timestamp
    if(!samples.size()) {
      *baseTime = now.unixtime();
      baseTime.save();
    }
    if(samples.size() == samples.capacity()) {
      *baseTime += period;
      baseTime.save();
    }
    samples.put(temp);
    last = now;
  }
  void reset() {
    samples.reset();
  }
  DateTime time(const uint16_t n) const {
    return DateTime(*baseTime) + TimeDelta(uint32_t(n)*period);
  }
  void dumpCSV(Stream &s, const char separator = ';') const {
    csvHeader(s, separator);
    s.println();
    for(int i = 0; i < samples.size(); ++i) {
      int8_t temp;
      samples.get(i, temp);
      char timeStr[] = "DD.MM.YY hh:mm";
      s.print(time(i).format(timeStr));
      s.print(separator);
      s.print(temp);
      s.println();
    }
  }
  static void csvHeader(Stream &s, const char separator) {
    s.print(F("date"));
    s.print(separator);
    s.print(F("temp"));
  }
  const DateTime& lastEntryTime() {
    return last;
  }
public:
  DateTime last;
  const uint32_t period;
};
