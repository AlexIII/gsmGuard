#! /usr/bin/env python
# -*- coding: utf-8 -*-

curLocal = [None, 'EN']

def Local(strVal):
    return curLocal[0][strVal] if curLocal[0] is not None and strVal in curLocal[0] else strVal

Locals = {
'EN': None,
'RU': {
        'Save as': 'Сохранить как',
        'Date': 'Дата',
        'Event': 'Событие',
        'Value': 'Значение',
        'Incorrect time in the schedule': 'Неверно введено время в расписании',
        'Select at least one day of the week': 'Не выбран ни один день недели',
        'Select at least one event': 'Не выбрано ни одно событие',
        'Max one report in 20min': 'Не более одного сообщения в 20 мин.',

        'Day of the week': 'День недели',
        'from': 'c',
        'to': 'до',
        'event': 'событие',
        'action': 'действие',
        'mo': 'пн',
        'tu': 'вт',
        'we': 'ср',
        'th': 'чт',
        'fr': 'пт',
        'sa': 'сб',
        'su': 'вс',
        'hh : mm': 'чч : мм',
        'door': 'дверь',
        'move.': 'движ.',
        'light': 'свет',
        'call': 'звонок',
        'siren': 'сирена',
        'Error': 'Ошибка',
        'Serial port not found': 'Последовательный порт не найден',
        'Schedule': 'Расписание',

        'Connection': 'Подключение',
        'Port': 'Порт',
        'Read': 'Считать',
        'Write': 'Записать',
        'Read event history': 'Запрос истории событий',
        'Read temperature statistics': 'Запрос статистики температуры',
        'Alarms': 'Оповещение',
        'Tel.': 'Тел.',
        'Daily report': 'Ежедн. отчет',
        'Temperature alarm': 'Предупр. по температуре',
        'min.': 'мин.',
        'max.': 'макс.',
        'Please wait...': 'Пожалуйста, ждите...',
        'Success!': 'Успешно!',
        'Incorrect phone number': 'Неверный номер телефона',
        'Incorrect report time': 'Неверное время отчета',
        'Incorrect temperature range': 'Неверный диапазон температур',

        'Language:': 'Язык',
        'Localization': 'Локализация'
    }
}

def getLocales():
    return Locals.keys()
def getCurrentLocale():
    return curLocal[1]

def setLocale(locale):
    curLocal[0] = Locals[locale]
    curLocal[1] = locale
