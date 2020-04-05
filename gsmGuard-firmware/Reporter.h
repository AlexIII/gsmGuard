/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#define TINY_GSM_MODEM_SIM800
#include "TinyGsmExtra.h"
#define BOOT_PIN 2
#define MODEM_POWER_PIN 5

class Reporter {
public:
  Reporter(Stream& stream, const char* const target) : modem(stream), target(target) {}
  enum Error : uint8_t{
    NO_ERROR,
    E_CANT_INIT,
    E_REG,
    E_SMS,
    E_CALL
  };
  template <typename F>
  Error send(const F& printer) {
    if(const Error e = initModem()) return e;
    if(!modem.sendSMS_UTF8(target, printer)) return E_SMS;
    DBG(F("Modem send sms ok."));
    return NO_ERROR;    
  }
  Error call() {
    if(const Error e = initModem()) return e;
    modem.sendAT(GF("+COLP=1"));
    modem.waitResponse();
    if(!modem.callNumber(target)) return E_CALL;
    DBG(F("Modem call ok."));
    delay(180000UL); //wait for 3 min
    modem.callHangup();
    return NO_ERROR; 
  }
  void pwrDwnModem() {
    inited = false;
    pinMode(BOOT_PIN, INPUT);
    modem.poweroff();
    digitalWrite(MODEM_POWER_PIN, LOW);
    pinMode(MODEM_POWER_PIN, INPUT);
  }
  
private:
  TinyGsmExtra modem;
  bool inited = false;
  const char* const target;

  Error initModem() {
    if(inited) return NO_ERROR;
    inited = true;
    digitalWrite(MODEM_POWER_PIN, LOW);
    pinMode(MODEM_POWER_PIN, OUTPUT);
    digitalWrite(BOOT_PIN, LOW);
    pinMode(BOOT_PIN, OUTPUT);
    delay(1000);
    if(!modem.init()) return E_CANT_INIT;
    DBG(F("Modem init ok."));
    modem.handsFree();
    if (!modem.waitForNetwork()) return E_REG;
    DBG(F("Modem reg ok."));
    return NO_ERROR;
  }
};
