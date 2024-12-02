// sale.h
#ifndef SALE_H_INCLUDED
#define SALE_H_INCLUDED

#include "date.h"

//Структура для представления продажи
typedef struct _sale {
    Date date;         //Дата продажи
    int sale_id;       //ID продажи
    int manager_id;    //ID менеджера, ответственного за продажу
    char currency[20]; //Модель автомобиля, который был продан
    int price;         //Цена продажи
} Sale;

#endif //SALE_H_INCLUDED
