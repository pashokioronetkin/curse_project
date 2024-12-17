// func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#define N_MONTHS 12 // Константа для количества месяцев в году
#define AR_MAN_LEN 100    // Максимальное количество менеджеров
#define AR_EXCHANGE_LEN 1000 // Максимальное количество обменов

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "exchange.h" // Включение заголовочного файла с определением класса Exchange
#include "manager.h"  // Включение заголовочного файла с определением класса Manager

// Объявление функций
void get_current_date(char* date_str); // Получение текущей даты в строковом формате
void exchange_to_s(char s[100], const Exchange& exchange); // Преобразование обмена в строку
void manager_to_s(char s[150], const Manager& manager); // Преобразование менеджера в строку
void show_menu(); // Отображение основного меню
int get_current_year(); // Получение текущего года

// Операции с файлами
void save_new_exchange(const char* fname, int current_manager_id); // Сохранение нового обмена в файл
int load_managers(const char* fname, Manager managers[], int limit); // Загрузка менеджеров из файла
int load_exchanges(const char* fname, Exchange exchanges[], int limit); // Загрузка обменов из файла

// Вывод информации
void exchanges_print(const Exchange exchanges[], int limit); // Вывод списка обменов
void managers_print(const Manager managers[], int limit); // Вывод списка менеджеров

// Запросы и отчеты
void do_query(const Exchange exchanges[], int limit, const char* fname); // Формирование отчета по обменам в txt
void do_query1(const Exchange exchanges[], int limit, const char* fname); // Формирование отчета по обменам в html

// Операции редактирования
void edit_exchange(const char* fname, int current_manager_id); // Редактирование обмена
void add_manager(Manager managers[], int* count); // Добавление нового менеджера
void remove_manager(Manager managers[], int* count); // Удаление менеджера

// Функции входа и меню
void manager_login(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count); // Вход менеджера
void admin_login(Manager managers[], int* man_count); // Вход администратора
void admin_menu(Manager managers[], int* man_count); // Меню администратора
void manager_menu(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count, int current_manager_id); // Меню менеджера

// Проверки
bool check_exchange_id_exists(const char* fname, int exchange_id); // Проверка существования ID обмена
bool validate_date(const Date& date); // Проверка корректности даты

#endif // FUNC_H_INCLUDED
