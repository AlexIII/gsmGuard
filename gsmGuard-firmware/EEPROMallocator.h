/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _EEPROMALLOCATOR_H_
#define _EEPROMALLOCATOR_H_

#include <EEPROM.h>

static uint16_t& __eeAddrCnt() {
  static uint16_t cur = 0;
  return cur;
}

uint16_t eeAlloc(const uint16_t sz) {
  uint16_t &cur = __eeAddrCnt();
  const uint16_t t = cur;
  cur += sz;
  return t;
}

uint16_t eeFree() {
  return __eeAddrCnt() >= EEPROM.length()? 0 : EEPROM.length() - __eeAddrCnt();
}

#endif
