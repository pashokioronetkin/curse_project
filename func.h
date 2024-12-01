//func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define N_MONTHS 12

#include "sale.h"
#include "manager.h"

//Прототипы функций
void get_current_date(char *date_str); //Получение текущей даты
void sale_to_s(char s[100], Sale sale); //Преобразование продажи в строку
void manager_to_s(char s[150], Manager manager); //Преобразование менеджера в строку
void show_menu(); //Показать меню
void save_new_sale(char *fname); //Сохранить новую продажу
int load_managers(char *fname, Manager managers[], int limit); //Загрузить менеджеров
int load_sales(char *fname, Sale sales[], int limit); //Загрузить продажи
void sales_print(Sale sales[], int limit); //Печать списка продаж
void managers_print(Manager managers[], int limit); //Печать списка менеджеров
void do_query1(Sale sales[], int limit, const char *fname); //Выполнение запроса по продажам

#endif //FUNC_H_INCLUDED
