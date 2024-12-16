// date.h
#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

// Класс для представления даты
class Date {
public:
    int year;  // Год
    int month; // Месяц
    int day;   // День

    // Конструктор с параметрами по умолчанию
    // Инициализирует дату 1 января 2024 года, если не указаны другие значения
    Date(int d = 1, int m = 1, int y = 2024) : year(y), month(m), day(d) {}
};

#endif // DATE_H_INCLUDED
