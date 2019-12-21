/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _EERINGQUEUE_H_
#define _EERINGQUEUE_H_

#include <EEPROMallocator.h>

template <typename T, int SZ, typename index_t = uint8_t>
class EeRingQueue {
public:
  EeRingQueue() : addr((uint16_t)EEPROMallocator::alloc(sizeof(state) + sizeof(T)*SZ)) {
    EEPROM.get(addr, state);
    if(!state.isOk()) reset();
  }
  void reset() {
    state.tail = 0;
    state.size = 0;
    EEPROM.put(addr, state);
  }
  void put(const T& v) {
    EEPROM.put(dataAddr(state.tail), v);
    state.inc();
    EEPROM.put(addr, state);
  }
  index_t size() const {return state.size;}
  void get(index_t ind, T& v) const {
    const index_t head = state.size > state.tail? SZ-state.size+state.tail : state.tail-state.size;
    const index_t off = head < SZ-ind? head+ind : ind-(SZ-head);
    EEPROM.get(dataAddr(off), v);
  }
  void update(index_t ind, const T& v) const {
    const index_t head = state.size > state.tail? SZ-state.size+state.tail : state.tail-state.size;
    const index_t off = head < SZ-ind? head+ind : ind-(SZ-head);
    EEPROM.put(dataAddr(off), v);
  } 
  index_t capacity() {return SZ;}
private:
  struct {
    index_t tail; //where to put next value
    index_t size;
    void inc() {
      if(size < SZ) ++size;
      if(tail == SZ-1) tail = 0;
      else ++tail;
    }
    bool isOk() const {
      return size < SZ+1 && tail < SZ;
    }
  } state;
  uint16_t addr;
  uint16_t dataAddr(const index_t ind) const {return addr+sizeof(state)+ind*sizeof(T);}
};

#endif
