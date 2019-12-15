/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _EEVAR_H_
#define _EEVAR_H_

#include "EEPROMallocator.h"

template<typename T>
class EEvar {
public:
  constexpr static int dataOffset = sizeof(EEvar<T>);
  void load() {
    eeprom_read_block(((uint8_t*)this)+dataOffset, (void*)myAddr, sizeof(T) - dataOffset);
  }
  void save() {
    eeprom_update_block(((uint8_t*)this)+dataOffset, (void*)myAddr, sizeof(T) - dataOffset);
  }
protected:
  EEvar() : myAddr(eeAlloc(sizeof(T) - dataOffset)) {load();}
private:
  const uint16_t myAddr;
};

template<typename T>
class EEvarCRC : public EEvar<T> {
public:
  void save() {
    crc = calcCRC();
    EEvar<T>::save();
  }
  bool chkCRC() {
    return crc == calcCRC();
  }
protected:
  EEvarCRC() {}
private:
  uint8_t crc;
  uint8_t calcCRC() const {
    uint8_t tmp = 0;
    const uint8_t* data = ((const uint8_t*)this) + sizeof(*this);
    for(uint16_t i = 0; i < sizeof(T) - sizeof(*this); ++i)
      tmp += *data++;
    return tmp;
  }
};


#endif
