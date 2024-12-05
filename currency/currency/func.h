// func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define N_MONTHS 12

#include "exchange.h"
#include "manager.h"

// Прототипы функций
void get_current_date(char *date_str); // Получение текущей даты
void exchange_to_s(char s[100], Exchange exchange); // Преобразование обмена в строку
void manager_to_s(char s[150], Manager manager); // Преобразование менеджера в строку
void show_menu(); // Показать меню
void save_new_exchange(char *fname); // Сохранить новый обмен
int load_managers(char *fname, Manager managers[], int limit); // Загрузить менеджеров
int load_exchanges(char *fname, Exchange exchanges[], int limit); // Загрузить обмены
void exchanges_print(Exchange exchanges[], int limit); // Печать списка обменов
void managers_print(Manager managers[], int limit); // Печать списка менеджеров
void do_query1(Exchange exchanges[], int limit, const char *fname); // Выполнение запроса по обменам
void edit_exchange(char *fname); // Редактировать обмен
void manage_managers(Manager managers[], int *count); // Управление менеджерами
void add_manager(Manager managers[], int *count); // Добавить менеджера
void remove_manager(Manager managers[], int *count); // Удалить менеджера

#endif // FUNC_H_INCLUDED
