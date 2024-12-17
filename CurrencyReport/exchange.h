// exchange.h
#ifndef EXCHANGE_H_INCLUDED
#define EXCHANGE_H_INCLUDED

#include "date.h" // Включение заголовочного файла с определением класса Date

// Класс для представления обмена валют
class Exchange {
public:
    Date date;         // Дата обмена
    int exchange_id;   // Уникальный идентификатор обмена
    int manager_id;    // Идентификатор менеджера, который провел обмен
    char currency[20]; // Валюта обмена (например, USD или EURO)
    double price;      // Сумма обмена

    // Конструктор по умолчанию
    // Инициализирует поля exchange_id, manager_id и price нулями
    // Устанавливает пустую строку для currency
    Exchange() : exchange_id(0), manager_id(0), price(0.0) {
        currency[0] = '\0'; // Инициализация строки валюты пустым значением
    }
};

#endif // EXCHANGE_H_INCLUDED
