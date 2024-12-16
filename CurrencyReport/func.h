// func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define N_MONTHS 12 // Константа для количества месяцев в году

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "exchange.h" // Включение заголовочного файла с определением класса Exchange
#include "manager.h"  // Включение заголовочного файла с определением класса Manager

// Класс для управления системой обменов
class ExchangeSystem {
public:
    static const int AR_MAN_LEN = 100;    // Максимальное количество менеджеров
    static const int AR_EXCHANGE_LEN = 1000; // Максимальное количество обменов
    static const char* month_names[12];   // Статический массив с названиями месяцев
    static const char* month_names1[12];   // Статический массив с названиями месяцев

    // Вспомогательные методы
    static void get_current_date(char* date_str); // Получение текущей даты в строковом формате
    static void get_current_date1(char* date_str); // Получение текущей даты в строковом формате
    static void exchange_to_s(char s[100], const Exchange& exchange); // Преобразование обмена в строку
    static void manager_to_s(char s[150], const Manager& manager); // Преобразование менеджера в строку
    static void show_menu(); // Отображение основного меню
    static int get_current_year(); // Получение текущего года


    // Операции с файлами
    static void save_new_exchange(const char* fname, int current_manager_id); // Сохранение нового обмена в файл
    static int load_managers(const char* fname, Manager managers[], int limit); // Загрузка менеджеров из файла
    static int load_exchanges(const char* fname, Exchange exchanges[], int limit); // Загрузка обменов из файла

    // Вывод информации
    static void exchanges_print(const Exchange exchanges[], int limit); // Вывод списка обменов
    static void managers_print(const Manager managers[], int limit); // Вывод списка менеджеров

    // Запросы и отчеты
    static void do_query(const Exchange exchanges[], int limit, const char* fname); // Формирование отчета по обменам в txt
    static void do_query1(const Exchange exchanges[], int limit, const char* fname); // Формирование отчета по обменам в html

    // Операции редактирования
    static void edit_exchange(const char* fname, int current_manager_id); // Редактирование обмена
    static void add_manager(Manager managers[], int* count); // Добавление нового менеджера
    static void remove_manager(Manager managers[], int* count); // Удаление менеджера

    // Функции входа и меню
    static void manager_login(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count); // Вход менеджера
    static void admin_login(Manager managers[], int* man_count); // Вход администратора
    static void admin_menu(Manager managers[], int* man_count); // Меню администратора
    static void manager_menu(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count, int current_manager_id); // Меню менеджера

    // Проверки
    static bool check_exchange_id_exists(const char* fname, int exchange_id); // Проверка существования ID обмена
    static bool validate_date(const Date& date); // Проверка корректности даты
};

#endif // FUNC_H_INCLUDED
