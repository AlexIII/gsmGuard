/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#include <TinyGsmClient.h>

class TinyGsmUTF : public TinyGsm {
public:
  template<typename ...Args>
  TinyGsmUTF(Args&&... args): TinyGsm(args...) {}
  
  void handsFree() {
    sendAT(GF("+CHF=0,2")); //hands free mode
    waitResponse();
    sendAT(GF("+CMIC=2,15")); //mic heighest gain
    waitResponse();
  }

  template <typename F>
  bool sendSMS_UTF8(const char* const number, const F& printer) {
    if(!sendSMS_UTF8_begin(number)) return false;
    printer(sendSMS_UTF8_stream());
    return sendSMS_UTF8_end();
  }
  
  bool callNumber(const char* const number) {
    sendAT(GF("D"), number, ";");
    int status = waitResponse(60000L,
                              GFP(GSM_OK),
                              GF("BUSY" GSM_NL),
                              GF("NO ANSWER" GSM_NL),
                              GF("NO CARRIER" GSM_NL));
    return status == 1;
  }
};
