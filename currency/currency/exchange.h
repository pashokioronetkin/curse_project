// exchange.h
#ifndef EXCHANGE_H_INCLUDED
#define EXCHANGE_H_INCLUDED

#include "date.h"

// Структура для представления обмена
typedef struct _exchange {
    Date date;         // Дата обмена
    int exchange_id;   // ID обмена
    int manager_id;    // ID менеджера, ответственного за обмен
    char currency[20]; // Валюта обмена
    int price;         // Цена обмена
} Exchange;

#endif // EXCHANGE_H_INCLUDED
