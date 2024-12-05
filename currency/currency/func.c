// func.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "func.h"
#include "exchange.h"
#include "manager.h"

#define MONTH_NAMES_COUNT 12
#define AR_MAN_LEN 100

const char *month_names[MONTH_NAMES_COUNT] = {
    "января", "февраля", "марта", "апреля", "мая", "июня",
    "июля", "августа", "сентября", "октября", "ноября", "декабря"
};

// Получение текущей даты в строковом формате
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names[tm.tm_mon], tm.tm_year + 1900);
}

// Преобразование обмена в строку
void exchange_to_s(char s[100], Exchange exchange) {
    char format[] = "%d. %02d.%02d.%04d %d %s %d";
    sprintf(s, format, exchange.exchange_id, exchange.date.day, exchange.date.month, exchange.date.year, exchange.manager_id, exchange.currency, exchange.price);
}

// Преобразование менеджера в строку
void manager_to_s(char s[150], Manager manager) {
    snprintf(s, 150, "%d. %s %s %s", manager.manager_id, manager.manager_surname, manager.manager_name, manager.manager_patronymic);
}

// Меню
void show_menu() {
    printf(
        "0. Выход\n"
        "1. О программе\n"
        "2. Записать данные в файл обменов\n"
        "3. Загрузка из файла менеджеров\n"
        "4. Загрузка из файла обменов\n"
        "5. Печать списка менеджеров\n"
        "6. Печать списка обменов\n"
        "7. Выполнение запроса по обменам\n"
        "8. Редактировать обмен\n"
        "9. Управление менеджерами\n\n");
}

// Проверка существования ID обмена в файле
int check_exchange_id_exists(char *fname, int exchange_id) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла для чтения");
        return 0;
    }

    Exchange rec; // Запись обмена
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &rec.exchange_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        if (rec.exchange_id == exchange_id) {
            fclose(in);
            return 1; // ID обмена существует
        }
    }
    fclose(in);
    return 0; // ID обмена не существует
}

// Ввод данных о обмене
void input_exchange(Exchange *exchange, char *fname) {
    printf("Введите ID обмена: ");
    while (scanf("%d", &exchange->exchange_id) != 1 || check_exchange_id_exists(fname, exchange->exchange_id)) {
        if (check_exchange_id_exists(fname, exchange->exchange_id)) {
            printf("Ошибка: ID обмена %d уже существует. Пожалуйста, введите уникальный ID: ", exchange->exchange_id);
        } else {
            printf("Ошибка ввода. Пожалуйста, введите целое число для ID обмена: ");
        }
        while(getchar() != '\n');
    }

    printf("Введите дату обмена (дд.мм.гггг): ");
    while (scanf("%d.%d.%d", &exchange->date.day, &exchange->date.month, &exchange->date.year) != 3 ||
           exchange->date.day < 1 || exchange->date.day > 31 ||
           exchange->date.month < 1 || exchange->date.month > 12 ||
           (exchange->date.month == 2 && exchange->date.day > 29) || // Проверка на февраль
           (exchange->date.month == 4 && exchange->date.day > 30) || // Проверка на апрель
           (exchange->date.month == 6 && exchange->date.day > 30) || // Проверка на июнь
           (exchange->date.month == 9 && exchange->date.day > 30) || // Проверка на сентябрь
           (exchange->date.month == 11 && exchange->date.day > 30)) { // Проверка на ноябрь
        printf("Ошибка ввода. Пожалуйста, введите дату в формате дд.мм.гггг: ");
        while(getchar() != '\n');
    }

    printf("Введите ID менеджера (1-2): ");
    while (scanf("%d", &exchange->manager_id) != 1 || (exchange->manager_id < 1 || exchange->manager_id > 2)) {
        printf("Ошибка ввода. Пожалуйста, введите ID менеджера (1-2): ");
        while(getchar() != '\n');
    }

    printf("Введите валюту (USD, EURO): ");
    while (scanf("%s", exchange->currency) != 1 || (strcmp(exchange->currency, "USD") != 0 && strcmp(exchange->currency, "EURO") != 0)) {
        printf("Ошибка ввода. Пожалуйста, введите валюту (USD, EURO): ");
        while(getchar() != '\n');
    }

    printf("Введите цену: ");
    while (scanf("%d", &exchange->price) != 1 || exchange->price < 0) {
        printf("Ошибка ввода. Пожалуйста, введите положительное целое число для цены: ");
        while(getchar() != '\n');
    }
}

// Сохранение нового обмена в файл
void save_new_exchange(char *fname) {
    Exchange exchange; // Объект обмена
    input_exchange(&exchange, fname); // Ввод данных о обмене

    FILE *out = fopen(fname, "a");
    if (out == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    fprintf(out, "%d %02d.%02d.%04d %d %s %d\n", exchange.exchange_id, exchange.date.day, exchange.date.month, exchange.date.year, exchange.manager_id, exchange.currency, exchange.price);
    fclose(out);
    printf("Обмен добавлен.\n\n");
}

// Функция для редактирования существующего обмена
void edit_exchange(char *fname) {
    Exchange exchange; // Объект обмена
    int exchange_id;

    printf("Введите ID обмена для редактирования: ");
    scanf("%d", &exchange_id);

    // Проверка существования ID обмена
    if (!check_exchange_id_exists(fname, exchange_id)) {
        printf("Ошибка: ID обмена %d не существует.\n", exchange_id);
        return;
    }

    // Загрузка существующего обмена
    FILE *in = fopen(fname, "r");
    FILE *temp = fopen("temp.txt", "w"); // Временный файл для хранения обновленных данных
    if (in == NULL || temp == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    // Чтение данных из файла и редактирование нужной записи
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &exchange.exchange_id, &exchange.date.day, &exchange.date.month, &exchange.date.year, &exchange.manager_id, exchange.currency, &exchange.price) == 7) {
        if (exchange.exchange_id == exchange_id) {
            printf("Редактирование обмена с ID %d:\n", exchange_id);
            // Ввод новых данных, но ID остается прежним
            printf("Введите новую дату обмена (дд.мм.гггг): ");
            while (scanf("%d.%d.%d", &exchange.date.day, &exchange.date.month, &exchange.date.year) != 3 ||
                   exchange.date.day < 1 || exchange.date.day > 31 ||
                   exchange.date.month < 1 || exchange.date.month > 12 ||
                   (exchange.date.month == 2 && exchange.date.day > 29) || // Проверка на февраль
                   (exchange.date.month == 4 && exchange.date.day > 30) || // Проверка на апрель
                   (exchange.date.month == 6 && exchange.date.day > 30) || // Проверка на июнь
                   (exchange.date.month == 9 && exchange.date.day > 30) || // Проверка на сентябрь
                   (exchange.date.month == 11 && exchange.date.day > 30)) { // Проверка на ноябрь
                printf("Ошибка ввода. Пожалуйста, введите дату в формате дд.мм.гггг: ");
                while(getchar() != '\n');
            }

            printf("Введите новую валюту (USD, EURO): ");
            while (scanf("%s", exchange.currency) != 1 || (strcmp(exchange.currency, "USD") != 0 && strcmp(exchange.currency, "EURO") != 0)) {
                printf("Ошибка ввода. Пожалуйста, введите валюту (USD, EURO): ");
                while(getchar() != '\n');
            }

            printf("Введите новую цену: ");
            while (scanf("%d", &exchange.price) != 1 || exchange.price < 0) {
                printf("Ошибка ввода. Пожалуйста, введите положительное целое число для цены: ");
                while(getchar() != '\n');
            }
        }
        fprintf(temp, "%d %02d.%02d.%04d %d %s %d\n", exchange.exchange_id, exchange.date.day, exchange.date.month, exchange.date.year, exchange.manager_id, exchange.currency, exchange.price);
    }

    fclose(in);
    fclose(temp);
    remove(fname); // Удаляем старый файл
    rename("temp.txt", fname); // Переименовываем временный файл
    printf("Обмен с ID %d успешно отредактирован.\n\n", exchange_id);
}

// Печать списка обменов
void exchanges_print(Exchange exchanges[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        exchange_to_s(s, exchanges[i]);
        puts(s); // Вывод строки
        puts("");
    }
}

// Загрузка обменов из файла
int load_exchanges(char *fname, Exchange exchanges[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int count = 0; // Счетчик загруженных обменов
    Exchange rec; // Запись обмена
    while (count < limit && fscanf(in, "%d %d.%d.%d %d %s %d", &rec.exchange_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        exchanges[count] = rec; // Сохранение обмена в массив
        count++;
    }
    fclose(in);
    return count; // Возврат количества загруженных обменов
}

// Загрузка менеджеров из файла
int load_managers(char *fname, Manager managers[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int count = 0; // Счетчик загруженных менеджеров
    Manager rec; // Запись менеджера
    while (count < limit && fscanf(in, "%d %s %s %s", &rec.manager_id, rec.manager_surname, rec.manager_name, rec.manager_patronymic) == 4) {
        managers[count] = rec; // Сохранение менеджера в массив
        count++;
    }
    fclose(in);
    return count; // Возврат количества загруженных менеджеров
}

// Печать списка менеджеров
void managers_print(Manager managers[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        manager_to_s(s, managers[i]); // Преобразование менеджера в строку
        puts(s); // Вывод строки
        puts("");
    }
}

// Выполнение запроса по обменам
void do_query1(Exchange exchanges[], int limit, const char *fname) {
    if (limit == 0) { // Проверка на наличие обменов
        printf("Нет обменов для обработки запроса.\n");
        return;
    }

    int month_exchanges[N_MONTHS + 1] = {0}; // Массив для хранения количества обменов по месяцам
    int month_totals[N_MONTHS + 1] = {0}; // Массив для хранения сумм по месяцам

    // Получение текущего года
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900; // Текущий год

    // Перебор всех обменов и подсчет по месяцам и годам
    for (int i = 0; i < limit; i++) {
        int month = exchanges[i].date.month; // Месяц обмена
        int year = exchanges[i].date.year; // Год обмена

        // Считаем только обмены текущего года
        if (year == current_year) {
            month_exchanges[month]++; // Увеличиваем количество обменов за месяц
            month_totals[month] += exchanges[i].price; // Суммируем цену по месяцам
        }
    }

    FILE *out = fopen(fname, "w");
    if (out == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    // Шапка документа
    fprintf(out, "Отчет по обменам\n");
    fprintf(out, "Курс EURO: \n");
    fprintf(out, "Курс USD: \n");
    fprintf(out, "Дата: ");
    char current_date[100];
    get_current_date(current_date); // Получение текущей даты
    fprintf(out, "%s\n", current_date);
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Месяц/год Количество\n");

    // Вывод количества обменов по месяцам
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_exchanges[i] != 0) {
            fprintf(out, "%02d.%d %d\n", i, current_year, month_exchanges[i]); // Используем текущий год
        }
    }

    // Сумма обмененных денег по месяцам для текущего года
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Сумма обмененных денег по месяцам в %d году:\n", current_year);
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "%02d.%d: %d\n", i, current_year, month_totals[i]);
        }
    }

    // Подпись на последней странице
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Подпись: _______________________\n");

    fclose(out);
}

// Функция для управления менеджерами
void manage_managers(Manager managers[], int *count) {
    int action;
    printf("1. Добавить менеджера\n");
    printf("2. Удалить менеджера\n");
    printf("Выберите действие: ");
    scanf("%d", &action);

    switch (action) {
        case 1:
            add_manager(managers, count);
            break;
        case 2:
            remove_manager(managers, count);
            break;
        default:
            printf("Ошибка: Неверный выбор.\n");
            break;
    }
}

// Функция для добавления менеджера
void add_manager(Manager managers[], int *count) {
    if (*count >= AR_MAN_LEN) {
        printf("Ошибка: Достигнуто максимальное количество менеджеров.\n");
        return;
    }

    Manager new_manager;
    printf("Введите ID менеджера: ");
    scanf("%d", &new_manager.manager_id);

    // Проверка на уникальность ID
    for (int i = 0; i < *count; i++) {
        if (managers[i].manager_id == new_manager.manager_id) {
            printf("Ошибка: Менеджер с ID %d уже существует.\n", new_manager.manager_id);
            return;
        }
    }

    printf("Введите имя менеджера: ");
    scanf("%s", new_manager.manager_name);
    printf("Введите фамилию менеджера: ");
    scanf("%s", new_manager.manager_surname);
    printf("Введите отчество менеджера: ");
    scanf("%s", new_manager.manager_patronymic);

    managers[*count] = new_manager; // Сохранение нового менеджера в массив
    (*count)++; // Увеличение счетчика менеджеров
    printf("Менеджер добавлен.\n\n");
}

// Функция для удаления менеджера
void remove_manager(Manager managers[], int *count) {
    int id;
    printf("Введите ID менеджера для удаления: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (managers[i].manager_id == id) {
            found = 1;
            // Сдвигаем всех менеджеров после удаляемого на одну позицию влево
            for (int j = i; j < *count - 1; j++) {
                managers[j] = managers[j + 1];
            }
            (*count)--; // Уменьшаем счетчик менеджеров
            printf("Менеджер с ID %d удален.\n\n", id);
            break;
        }
    }

    if (!found) {
        printf("Ошибка: Менеджер с ID %d не найден.\n\n", id);
    }
}
