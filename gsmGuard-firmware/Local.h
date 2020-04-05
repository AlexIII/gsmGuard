/*
 * GsmGuard v1.0
 * author: github.com/AlexIII
 * e-mail: endoftheworld@bk.ru
 * license: MIT
 */

#ifndef _LOCAL_H_
#define _LOCAL_H_

#ifdef LOCAL_RU

  //for Event.h
  #define STR_EVENT_DOOR_OPEN         "Открыта дверь"
  #define STR_EVENT_LIGHT_CHANGE      "Изменилось освещение"
  #define STR_EVENT_HIGH_TEMP         "Высокая температура"
  #define STR_EVENT_LOW_TEMP          "Низкая температура"
  #define STR_EVENT_MOVEMENT          "Обнаружено движение"
  #define STR_EVENT_BAT_LOW           "Батарея разряжена"
  #define STR_EVENT_LIGHT             "cвет"
  #define STR_EVENT_TEMP              "темп."
  #define STR_EVENT_BAT               "бат."
  
  //for Status.h
  #define STR_STATUS_DOOR             "дверь"
  #define STR_STATUS_OPENED           "Откр."
  #define STR_STATUS_CLOSED           "Закр."
  #define STR_STATUS_MOVEMENT         "движ."
  #define STR_STATUS_DETECTED         "Есть"
  #define STR_STATUS_NONE             "Нет "
  #define STR_STATUS_TEMP             "темп."
  #define STR_STATUS_MIN              "мин."
  #define STR_STATUS_MAX              "макс."
  #define STR_STATUS_MED              "сред."
  #define STR_STATUS_LIGHT            "cвет"
  #define STR_STATUS_BAT              "бат."
  #define STR_STATUS_EXT              "внеш."

#else //english

  //for Event.h
  #define STR_EVENT_DOOR_OPEN         "Door open"
  #define STR_EVENT_LIGHT_CHANGE      "Light change"
  #define STR_EVENT_HIGH_TEMP         "High temperature"
  #define STR_EVENT_LOW_TEMP          "Low temperature"
  #define STR_EVENT_MOVEMENT          "Movement detected"
  #define STR_EVENT_BAT_LOW           "Battery low"
  #define STR_EVENT_LIGHT             "light"
  #define STR_EVENT_TEMP              "temp."
  #define STR_EVENT_BAT               "bat."
  
  //for Status.h
  #define STR_STATUS_DOOR             "door "
  #define STR_STATUS_OPENED           "Closed"
  #define STR_STATUS_CLOSED           "Opened"
  #define STR_STATUS_MOVEMENT         "move "
  #define STR_STATUS_DETECTED         "Det."
  #define STR_STATUS_NONE             "None"
  #define STR_STATUS_TEMP             "temp."
  #define STR_STATUS_MIN              "min."
  #define STR_STATUS_MAX              "max."
  #define STR_STATUS_MED              "med."
  #define STR_STATUS_LIGHT            "light"
  #define STR_STATUS_BAT              "bat."
  #define STR_STATUS_EXT              "ext."
#endif

#endif
