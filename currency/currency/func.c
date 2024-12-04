//func.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "func.h"
#include "sale.h"
#include "manager.h"

#define MONTH_NAMES_COUNT 12
const char *month_names[MONTH_NAMES_COUNT] = {
    "января", "февраля", "марта", "апреля", "мая", "июня",
    "июля", "августа", "сентября", "октября", "ноября", "декабря"
};

//Получение текущей даты в строковом формате
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names[tm.tm_mon], tm.tm_year + 1900);
}

//Преобразование продажи в строку
void sale_to_s(char s[100], Sale sale) {
    char format[] = "%d. %02d.%02d.%04d %d %s %d";
    sprintf(s, format, sale.sale_id, sale.date.day, sale.date.month, sale.date.year, sale.manager_id, sale.currency, sale.price);
}

//Преобразование менеджера в строку
void manager_to_s(char s[150], Manager manager) {
    snprintf(s, 150, "%d. %s %s %s", manager.manager_id, manager.manager_surname, manager.manager_name, manager.manager_patronymic);
}

//Меню
void show_menu() {
    printf(
        "0. Выход\n"
        "1. О программе\n"
        "2. Записать данные в файл продаж\n"
        "3. Загрузка из файла менеджеров\n"
        "4. Загрузка из файла продаж\n"
        "5. Печать списка менеджеров\n"
        "6. Печать списка продаж\n"
        "7. Выполнение запроса по продажам\n"
        "8. Редактировать продажу\n\n"); //Добавлено новое меню
}

//Проверка существования ID продажи в файле
int check_sale_id_exists(char *fname, int sale_id) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла для чтения");
        return 0;
    }

    Sale rec; //Запись продажи
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &rec.sale_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        if (rec.sale_id == sale_id) {
            fclose(in);
            return 1; //ID продажи существует
        }
    }
    fclose(in);
    return 0; //ID продажи не существует
}

//Ввод данных о продаже
void input_sale(Sale *sale, char *fname) {
    printf("Введите ID продажи: ");
    while (scanf("%d", &sale->sale_id) != 1 || check_sale_id_exists(fname, sale->sale_id)) {
        if (check_sale_id_exists(fname, sale->sale_id)) {
            printf("Ошибка: ID продажи %d уже существует. Пожалуйста, введите уникальный ID: ", sale->sale_id);
        } else {
            printf("Ошибка ввода. Пожалуйста, введите целое число для ID продажи: ");
        }
        while(getchar() != '\n');
    }

    printf("Введите дату продажи (дд.мм.гггг): ");
    while (scanf("%d.%d.%d", &sale->date.day, &sale->date.month, &sale->date.year) != 3 ||
           sale->date.day < 1 || sale->date.day > 31 ||
           sale->date.month < 1 || sale->date.month > 12 ||
           (sale->date.month == 2 && sale->date.day > 29) || //Проверка на февраль
           (sale->date.month == 4 && sale->date.day > 30) || //Проверка на апрель
           (sale->date.month == 6 && sale->date.day > 30) || //Проверка на июнь
           (sale->date.month == 9 && sale->date.day > 30) || //Проверка на сентябрь
           (sale->date.month == 11 && sale->date.day > 30)) { //Проверка на ноябрь
        printf("Ошибка ввода. Пожалуйста, введите дату в формате дд.мм.гггг: ");
        while(getchar() != '\n');
    }

    printf("Введите ID менеджера (1-2): ");
    while (scanf("%d", &sale->manager_id) != 1 || (sale->manager_id < 1 || sale->manager_id > 2)) {
        printf("Ошибка ввода. Пожалуйста, введите ID менеджера (1-2): ");
        while(getchar() != '\n');
    }

    printf("Введите валюту (USD, EURO): ");
    while (scanf("%s", sale->currency) != 1 || (strcmp(sale->currency, "USD") != 0 && strcmp(sale->currency, "EURO") != 0)) {
        printf("Ошибка ввода. Пожалуйста, введите валюту (USD, EURO): ");
        while(getchar() != '\n');
    }

    printf("Введите цену: ");
    while (scanf("%d", &sale->price) != 1 || sale->price < 0) {
        printf("Ошибка ввода. Пожалуйста, введите положительное целое число для цены: ");
        while(getchar() != '\n');
    }
}

//Сохранение новой продажи в файл
void save_new_sale(char *fname) {
    Sale sale; //Объект продажи
    input_sale(&sale, fname); //Ввод данных о продаже

    FILE *out = fopen(fname, "a");
    if (out == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    fprintf(out, "%d %02d.%02d.%04d %d %s %d\n", sale.sale_id, sale.date.day, sale.date.month, sale.date.year, sale.manager_id, sale.currency, sale.price);
    fclose(out);
    printf("Продажа добавлена.\n\n");
}

//Функция для редактирования существующей продажи
void edit_sale(char *fname) {
    Sale sale; //Объект продажи
    int sale_id;

    printf("Введите ID продажи для редактирования: ");
    scanf("%d", &sale_id);

    //Проверка существования ID продажи
    if (!check_sale_id_exists(fname, sale_id)) {
        printf("Ошибка: ID продажи %d не существует.\n", sale_id);
        return;
    }

    //Загрузка существующей продажи
    FILE *in = fopen(fname, "r");
    FILE *temp = fopen("temp.txt", "w"); //Временный файл для хранения обновленных данных
    if (in == NULL || temp == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    //Чтение данных из файла и редактирование нужной записи
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &sale.sale_id, &sale.date.day, &sale.date.month, &sale.date.year, &sale.manager_id, sale.currency, &sale.price) == 7) {
        if (sale.sale_id == sale_id) {
            printf("Редактирование продажи с ID %d:\n", sale_id);
            //Ввод новых данных, но ID остается прежним
            printf("Введите новую дату продажи (дд.мм.гггг): ");
            while (scanf("%d.%d.%d", &sale.date.day, &sale.date.month, &sale.date.year) != 3 ||
                   sale.date.day < 1 || sale.date.day > 31 ||
                   sale.date.month < 1 || sale.date.month > 12 ||
                   (sale.date.month == 2 && sale.date.day > 29) || //Проверка на февраль
                   (sale.date.month == 4 && sale.date.day > 30) || //Проверка на апрель
                   (sale.date.month == 6 && sale.date.day > 30) || //Проверка на июнь
                   (sale.date.month == 9 && sale.date.day > 30) || //Проверка на сентябрь
                   (sale.date.month == 11 && sale.date.day > 30)) { //Проверка на ноябрь
                printf("Ошибка ввода. Пожалуйста, введите дату в формате дд.мм.гггг: ");
                while(getchar() != '\n');
            }

            printf("Введите новый ID менеджера (1-2): ");
            while (scanf("%d", &sale.manager_id) != 1 || (sale.manager_id < 1 || sale.manager_id > 2)) {
                printf("Ошибка ввода. Пожалуйста, введите ID менеджера (1-2): ");
                while(getchar() != '\n');
            }

            printf("Введите новую валюту (USD, EURO): ");
            while (scanf("%s", sale.currency) != 1 || (strcmp(sale.currency, "USD") != 0 && strcmp(sale.currency, "EURO") != 0)) {
                printf("Ошибка ввода. Пожалуйста, введите валюту (USD, EURO): ");
                while(getchar() != '\n');
            }

            printf("Введите новую цену: ");
            while (scanf("%d", &sale.price) != 1 || sale.price < 0) {
                printf("Ошибка ввода. Пожалуйста, введите положительное целое число для цены: ");
                while(getchar() != '\n');
            }
        }
        //Запись данных в временный файл
        fprintf(temp, "%d %02d.%02d.%04d %d %s %d\n", sale.sale_id, sale.date.day, sale.date.month, sale.date.year, sale.manager_id, sale.currency, sale.price);
    }

    fclose(in);
    fclose(temp);
    remove(fname); //Удаление старого файла
    rename("temp.txt", fname); //Переименование временного файла в оригинальный
    printf("Продажа с ID %d успешно отредактирована.\n", sale_id);
}

//Загрузка менеджеров из файла
int load_managers(char *fname, Manager managers[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int count = 0; //Счетчик загруженных менеджеров
    Manager rec; //Запись менеджера
    while (count < limit && fscanf(in, "%d %s %s %s", &rec.manager_id, rec.manager_surname, rec.manager_name, rec.manager_patronymic) == 4) {
        managers[count] = rec; //Сохранение менеджера в массив
        count++;
    }
    fclose(in);
    return count; //Возврат количества загруженных менеджеров
}

//Загрузка продаж из файла
int load_sales(char *fname, Sale sales[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int count = 0; //Счетчик загруженных продаж
    Sale rec; //Запись продажи
    while (count < limit && fscanf(in, "%d %d.%d.%d %d %s %d", &rec.sale_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        sales[count] = rec; //Сохранение продажи в массив
        count++;
    }
    fclose(in);
    return count; //Возврат количества загруженных продаж
}

//Печать списка продаж
void sales_print(Sale sales[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        sale_to_s(s, sales[i]); //Преобразование продажи в строку
        puts(s); //Вывод строки
        puts("");
    }
}

//Печать списка менеджеров
void managers_print(Manager managers[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        manager_to_s(s, managers[i]); //Преобразование менеджера в строку
        puts(s); //Вывод строки
        puts("");
    }
}

//Выполнение запроса по продажам
void do_query1(Sale sales[], int limit, const char *fname) {
    if (limit == 0) { //Проверка на наличие продаж
        printf("Нет продаж для обработки запроса.\n");
        return;
    }

    int month_sales[N_MONTHS + 1] = {0}; //Массив для хранения количества продаж по месяцам
    int month_totals[N_MONTHS + 1] = {0}; //Массив для хранения сумм по месяцам

    //Получение текущего года
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900; //Текущий год

    //Перебор всех продаж и подсчет по месяцам и годам
    for (int i = 0; i < limit; i++) {
        int month = sales[i].date.month; //Месяц продажи
        int year = sales[i].date.year; //Год продажи

        //Считаем только продажи текущего года
        if (year == current_year) {
            month_sales[month]++; //Увеличиваем количество продаж за месяц
            month_totals[month] += sales[i].price; //Суммируем цену по месяцам
        }
    }

    FILE *out = fopen(fname, "w");
    if (out == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    //Шапка документа
    fprintf(out, "Отчет по продажам\n");
    fprintf(out, "Курс EURO: \n");
    fprintf(out, "Курс USD: \n");
    fprintf(out, "Дата: ");
    char current_date[100];
    get_current_date(current_date); //Получение текущей даты
    fprintf(out, "%s\n", current_date);
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Месяц/год Количество\n");

    //Вывод количества продаж по месяцам
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_sales[i] != 0) {
            fprintf(out, "%02d.%d %d\n", i, current_year, month_sales[i]); //Используем текущий год
        }
    }

    //Сумма обмененных денег по месяцам для текущего года
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Сумма обмененных денег по месяцам в %d году:\n", current_year);
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "%02d.%d: %d\n", i, current_year, month_totals[i]);
        }
    }

    //Подпись на последней странице
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Подпись: _______________________\n");

    fclose(out);
}
