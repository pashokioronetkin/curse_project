// func.cpp
#include "func.h"
#include <ctime>
#include <cstring>

// Названия месяцев
const char* ExchangeSystem::month_names[12] = {
    "января", "февраля", "марта", "апреля", "мая", "июня",
    "июля", "августа", "сентября", "октября", "ноября", "декабря"
};

const char* ExchangeSystem::month_names1[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};


int ExchangeSystem::get_current_year() {
    time_t t = time(NULL); // Получение текущего времени
    struct tm tm = *localtime(&t); // Преобразование времени в локальное время
    return tm.tm_year + 1900; // Возвращаем текущий год
}

// Получение текущей даты в строковом формате
void ExchangeSystem::get_current_date(char* date_str) {
    time_t t = time(NULL); // Получение текущего времени
    struct tm tm = *localtime(&t); // Преобразование времени в локальное время
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names[tm.tm_mon], tm.tm_year + 1900); // Форматирование даты
}


void ExchangeSystem::get_current_date1(char* date_str) {
    time_t t = time(NULL); // Получение текущего времени
    struct tm tm = *localtime(&t); // Преобразование времени в локальное время
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names1[tm.tm_mon], tm.tm_year + 1900); // Форматирование даты
}

// Преобразование информации о менеджере в строку
void ExchangeSystem::manager_to_s(char s[150], const Manager& manager) {
    snprintf(s, 150, "%d. %s %s %s",
             manager.manager_id,
             manager.manager_surname,
             manager.manager_name,
             manager.manager_patronymic);
}

// Преобразование информации об обмене в строку
void ExchangeSystem::exchange_to_s(char s[100], const Exchange& exchange) {
    sprintf(s, "%d. %02d.%02d.%04d %d %s %.2f", // Используем %.2f для вывода
            exchange.exchange_id,
            exchange.date.day,
            exchange.date.month,
            exchange.date.year,
            exchange.manager_id,
            exchange.currency,
            exchange.price);
}


// Меню администратора
void ExchangeSystem::admin_menu(Manager managers[], int* man_count) {
    int choice = -1;
    while (choice != 0) {
        printf("Меню администратора:\n");
        printf("0. Выход\n");
        printf("1. Добавить менеджера\n");
        printf("2. Удалить менеджера\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        system("cls"); // Очистка экрана

        switch (choice) {
            case 0:
                printf("Выход из меню администратора.\n");
                break;
            case 1:
                add_manager(managers, man_count); // Добавление менеджера
                break;
            case 2:
                remove_manager(managers, man_count); // Удаление менеджера
                break;
            default:
                printf("Ошибка: Неверный выбор.\n");
                break;
        }
    }
}

// Вход менеджера
void ExchangeSystem::manager_login(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count) {
    int manager_id;
    printf("Введите ID менеджера: ");

    if (scanf("%d", &manager_id) != 1) {
        printf("Ошибка ввода.\n");
        return;
    }

    bool found = false;
    for (int i = 0; i < man_count; i++) {
        if (managers[i].manager_id == manager_id) {
            found = true;
            printf("Добро пожаловать, %s %s %s!\n",
                   managers[i].manager_surname,
                   managers[i].manager_name,
                   managers[i].manager_patronymic);
            system("pause"); // Пауза перед очисткой экрана
            system("cls");
            manager_menu(managers, man_count, exchanges, exchange_count, manager_id); // Переход в меню менеджера
            break;
        }
    }

    if (!found) {
        printf("Отказ в доступе: менеджер с ID %d не найден.\n", manager_id);
    }
}

// Отображение меню менеджера
void ExchangeSystem::show_menu() {
    printf(
        "0. Выход\n"
        "1. Записать данные в файл обменов\n"
        "2. Редактировать обмен\n"
        "3. Загрузка из файла менеджеров\n"
        "4. Загрузка из файла обменов\n"
        "5. Сохранение отчета в .html\n"
        "6. Сохранение отчета в .txt\n\n");
}

// Меню менеджера
void ExchangeSystem::manager_menu(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count, int current_manager_id) {
    int choice = -1;
    while (choice != 0) {
        show_menu(); // Показать меню менеджера
        printf("Выберите действие: ");
        scanf("%d", &choice);
        system("cls"); // Очистка экрана

        switch (choice) {
            case 0:
                printf("Выход из меню менеджера.\n");
                break;
            case 1:
                save_new_exchange("exchanges.txt", current_manager_id); // Сохранение нового обмена
                break;
            case 2:
                edit_exchange("exchanges.txt", current_manager_id); // Редактирование обмена
                break;
            case 3:
                *exchange_count = load_managers("managers.txt", managers, AR_MAN_LEN); // Загрузка менеджеров
                printf("Загружено менеджеров: %d\n", *exchange_count);
                printf("Список менеджеров:\n");
                managers_print(managers, *exchange_count); // Печать списка менеджеров
                break;
            case 4:
                *exchange_count = load_exchanges("exchanges.txt", exchanges, AR_EXCHANGE_LEN); // Загрузка обменов
                printf("Загружено обменов: %d\n", *exchange_count);
                printf("Содержимое файла exchanges.txt:\n");
                exchanges_print(exchanges, *exchange_count); // Печать списка обменов
                break;
            case 5:
                do_query1(exchanges, *exchange_count, "query1.html"); // Формирование отчета в html
                printf("Отчет успешно сформирован.\n");
                break;
            case 6:
                do_query(exchanges, *exchange_count, "query1.txt"); // Формирование отчета в txt
                printf("Отчет успешно сформирован.\n");
                break;
            default:
                printf("Ошибка. Пожалуйста, выберите пункт от 0 до 5.\n");
                break;
        }
    }
}


// Вход администратора
void ExchangeSystem::admin_login(Manager managers[], int* man_count) {
    char password[50];
    printf("Введите пароль администратора: ");
    getchar(); // Очистка буфера ввода
    fgets(password, sizeof(password), stdin); // Ввод пароля
    password[strcspn(password, "\n")] = 0; // Удаление символа новой строки

    if (strcmp(password, "123") == 0) {
        printf("Добро пожаловать, администратор!\n");
        system("pause");
        system("cls");
        admin_menu(managers, man_count); // Переход в меню администратора
    } else {
        printf("Неверный пароль. Доступ запрещен.\n");
    }
}

// Проверка существования ID обмена
bool ExchangeSystem::check_exchange_id_exists(const char* fname, int exchange_id) {
    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла для чтения");
        return false;
    }

    Exchange rec;
    while (fscanf(in, "%d %d.%d.%d %d %s %lf",
           &rec.exchange_id,
           &rec.date.day,
           &rec.date.month,
           &rec.date.year,
           &rec.manager_id,
           rec.currency,
           &rec.price) == 7) {
        if (rec.exchange_id == exchange_id) {
            fclose(in);
            return true; // ID найден
        }
    }
    fclose(in);
    return false; // ID не найден
}

// Сохранение нового обмена
void ExchangeSystem::save_new_exchange(const char* fname, int current_manager_id) {
    Exchange exchange;
    printf("Введите ID обмена: ");
    while (scanf("%d", &exchange.exchange_id) != 1 ||
           check_exchange_id_exists(fname, exchange.exchange_id)) {
        if (check_exchange_id_exists(fname, exchange.exchange_id)) {
            printf("Ошибка: ID обмена %d уже существует. Введите уникальный ID: ",
                   exchange.exchange_id);
        } else {
            printf("Ошибка ввода. Введите целое число для ID обмена: ");
        }
        while(getchar() != '\n'); // Очистка буфера ввода
    }

    printf("Введите дату обмена (дд.мм.гггг): ");
    while (scanf("%d.%d.%d",
           &exchange.date.day,
           &exchange.date.month,
           &exchange.date.year) != 3 ||
           !validate_date(exchange.date)) {
        printf("Ошибка ввода. Введите дату в формате дд.мм.гггг: ");
        while(getchar() != '\n');
    }

    // Устанавливаем ID менеджера по умолчанию
    exchange.manager_id = current_manager_id;

    printf("Введите валюту (USD, EURO): ");
    while (scanf("%s", exchange.currency) != 1 ||
           (strcmp(exchange.currency, "USD") != 0 &&
            strcmp(exchange.currency, "EURO") != 0)) {
        printf("Ошибка ввода. Введите валюту (USD, EURO): ");
        while(getchar() != '\n');
    }

    printf("Введите цену: ");
    while (scanf("%lf", &exchange.price) != 1 || exchange.price < 0) { // Используем %lf для double
        printf("Ошибка ввода. Введите положительное число для цены: ");
        while(getchar() != '\n');
    }

    FILE* out = fopen(fname, "a");
    if (out == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    fprintf(out, "%d %02d.%02d.%04d %d %s %.2f\n", // Используем %.2f для записи
            exchange.exchange_id,
            exchange.date.day,
            exchange.date.month,
            exchange.date.year,
            exchange.manager_id,
            exchange.currency,
            exchange.price);
    fclose(out);
    printf("Обмен добавлен.\n\n");
}

// Редактирование обмена
void ExchangeSystem::edit_exchange(const char* fname, int current_manager_id) {
    int exchange_id;
    printf("Введите ID обмена для редактирования: ");
    if (scanf("%d", &exchange_id) != 1) {
        printf("Ошибка ввода.\n");
        return;
    }

    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла для чтения");
        return;
    }

    Exchange exchanges[AR_EXCHANGE_LEN];
    int count = 0;
    while (fscanf(in, "%d %d.%d.%d %d %s %lf",
                  &exchanges[count].exchange_id,
                  &exchanges[count].date.day,
                  &exchanges[count].date.month,
                  &exchanges[count].date.year,
                  &exchanges[count].manager_id,
                  exchanges[count].currency,
                  &exchanges[count].price) == 7) {
        count++;
    }
    fclose(in);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (exchanges[i].exchange_id == exchange_id) {
            found = true;
            printf("Редактирование обмена с ID %d:\n", exchange_id);
            printf("Введите новую дату обмена (дд.мм.гггг): ");
            scanf("%d.%d.%d", &exchanges[i].date.day, &exchanges[i].date.month, &exchanges[i].date.year);
            // Устанавливаем ID менеджера по умолчанию
            exchanges[i].manager_id = current_manager_id;
            printf("Введите новую валюту (USD, EURO): ");
            scanf("%s", exchanges[i].currency);
            printf("Введите новую цену: ");
            scanf("%lf", &exchanges[i].price); // Используем %lf для double
            break;
        }
    }

    if (!found) {
        printf("Обмен с ID %d не найден.\n", exchange_id);
        return;
    }

    FILE* out = fopen(fname, "w");
    if (out == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(out, "%d %02d.%02d.%04d %d %s %.2f\n", // Используем %.2f для записи
                exchanges[i].exchange_id,
                exchanges[i].date.day,
                exchanges[i].date.month,
                exchanges[i].date.year,
                exchanges[i].manager_id,
                exchanges[i].currency,
                exchanges[i].price);
    }
    fclose(out);
    printf("Обмен с ID %d успешно отредактирован.\n", exchange_id);
}

// Проверка корректности даты
bool ExchangeSystem::validate_date(const Date& date) {
    if (date.month < 1 || date.month > 12) return false; // Проверка месяца
    if (date.day < 1) return false; // Проверка дня

    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31}; // Количество дней в каждом месяце
    if (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0))
        days_in_month[1] = 29; // Учет високосного года

    return date.day <= days_in_month[date.month - 1]; // Проверка корректности дня
}

// Загрузка обменов из файла
int ExchangeSystem::load_exchanges(const char* fname, Exchange exchanges[], int limit) {
    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int count = 0;
    Exchange rec;
    while (count < limit && fscanf(in, "%d %d.%d.%d %d %s %lf",
           &rec.exchange_id,
           &rec.date.day,
           &rec.date.month,
           &rec.date.year,
           &rec.manager_id,
           rec.currency,
           &rec.price) == 7) {
        exchanges[count] = rec;
        count++;
    }
    fclose(in);
    return count; // Возвращает количество загруженных обменов
}

// Загрузка менеджеров из файла
int ExchangeSystem::load_managers(const char* fname, Manager managers[], int limit) {
    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("Ошибка открытия файла");
        return 0;
    }

    int count = 0;
    Manager rec;
    while (count < limit && fscanf(in, "%d %s %s %s",
           &rec.manager_id,
           rec.manager_surname,
           rec.manager_name,
           rec.manager_patronymic) == 4) {
        managers[count] = rec;
        count++;
    }
    fclose(in);
    return count; // Возвращает количество загруженных менеджеров
}

// Добавление нового менеджера
void ExchangeSystem::add_manager(Manager managers[], int* count) {
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

    // Ввод фамилии менеджера с проверкой на наличие цифр
    printf("Введите фамилию менеджера: ");
    while (1) {
        scanf("%s", new_manager.manager_surname);
        if (strspn(new_manager.manager_surname, "0123456789") == 0) {
            break; // Фамилия корректна, выходим из цикла
        }
        printf("Ошибка: Фамилия не должна содержать цифры. Пожалуйста, введите фамилию снова: ");
    }

    // Ввод имени менеджера с проверкой на наличие цифр
    printf("Введите имя менеджера: ");
    while (1) {
        scanf("%s", new_manager.manager_name);
        if (strspn(new_manager.manager_name, "0123456789") == 0) {
            break; // Имя корректно, выходим из цикла
        }
        printf("Ошибка: Имя не должно содержать цифры. Пожалуйста, введите имя снова: ");
    }

    // Ввод отчества менеджера с проверкой на наличие цифр
    printf("Введите отчество менеджера: ");
    while (1) {
        scanf("%s", new_manager.manager_patronymic);
        if (strspn(new_manager.manager_patronymic, "0123456789") == 0) {
            break; // Отчество корректно, выходим из цикла
        }
        printf("Ошибка: Отчество не должно содержать цифры. Пожалуйста, введите отчество снова: ");
    }

    managers[*count] = new_manager; // Сохранение нового менеджера в массив
    (*count)++; // Увеличение счетчика менеджеров
    printf("Менеджер добавлен.\n\n");

    // Сохранение менеджера в файл
    FILE* out = fopen("managers.txt", "a");
    if (out == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }
    fprintf(out, "%d %s %s %s\n", new_manager.manager_id, new_manager.manager_surname, new_manager.manager_name, new_manager.manager_patronymic);
    fclose(out);
}

// Удаление менеджера
void ExchangeSystem::remove_manager(Manager managers[], int* count) {
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

    // Обновление файла после удаления
    FILE* out = fopen("managers.txt", "w");
    if (out == NULL) {
        perror("Ошибка открытия файла для записи");
        return;
    }

    // Запись оставшихся менеджеров в файл
    for (int i = 0; i < *count; i++) {
        fprintf(out, "%d %s %s %s\n", managers[i].manager_id, managers[i].manager_surname, managers[i].manager_name, managers[i].manager_patronymic);
    }

    fclose(out);
}

// Формирование отчета txt
void ExchangeSystem::do_query(const Exchange exchanges[], int limit, const char* fname) {
    if (limit == 0) {
        printf("Нет обменов для обработки запроса.\n");
        return;
    }

    int month_exchanges[N_MONTHS + 1] = {0}; // Инициализация массива для подсчета количества обменов
    double month_totals[N_MONTHS + 1] = {0.0};   // Инициализация массива для подсчета сумм обменов

    // Получите текущий год
    int report_year = get_current_year(); // Функция возвращает текущий год

    // Подсчет статистики по месяцам
    for (int i = 0; i < limit; i++) {
        if (exchanges[i].date.year == report_year) {
            int month = exchanges[i].date.month;
            month_exchanges[month]++;
            month_totals[month] += exchanges[i].price;
        }
    }

    FILE* out = fopen(fname, "w");
    if (out == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    // Формирование отчета
    fprintf(out, "Отчет по обменам\n");
    fprintf(out, "Курс EURO: \n");
    fprintf(out, "Курс USD: \n");

    // Текущая дата
    char current_date[100];
    get_current_date(current_date);
    fprintf(out, "Дата: %s\n", current_date);

    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Месяц/год Количество\n");

    // Вывод количества обменов по месяцам
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_exchanges[i] != 0) {
            fprintf(out, "%02d.%d %d\n", i, report_year, month_exchanges[i]);
        }
    }

    // Вывод сумм по месяцам
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Сумма обмененных денег в рублях по месяцам в %d году:\n", report_year);
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "%02d.%d: %.2f\n", i, report_year, month_totals[i]);
        }
    }

    fprintf(out, "-----------------------------------\n");
    fprintf(out, "Подпись: _______________________\n");

    fclose(out);
}


// Формирование отчета html
void ExchangeSystem::do_query1(const Exchange exchanges[], int limit, const char* fname) {
    if (limit == 0) {
        printf("No exchanges to process.\n");
        return;
    }

    int month_exchanges[N_MONTHS + 1] = {0}; // Инициализация массива для подсчета бирж
    double month_totals[N_MONTHS + 1] = {0.0};   // Инициализация массива для суммирования сумм биржевых операций

    // Установите год, для которого вы хотите создать отчет
    int report_year = get_current_year(); // Функция возвращает текущий год

    // Подсчет статистики по месяцам
    for (int i = 0; i < limit; i++) {
        if (exchanges[i].date.year == report_year) {
            int month = exchanges[i].date.month;
            month_exchanges[month]++;
            month_totals[month] += exchanges[i].price;
        }
    }

    FILE* out = fopen(fname, "w");
    if (out == NULL) {
        perror("Error opening file");
        return;
    }

    // Запись BOM для кодировки UTF-8
    fprintf(out, "\xEF\xBB\xBF");

    // Начало HTML-документа
    fprintf(out, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n");
    fprintf(out, "<title>Exchange Report</title>\n</head>\n<body>\n");
    fprintf(out, "<h1>Exchange Report</h1>\n");

    // Текущая дата
    char current_date[100];
    get_current_date1(current_date);
    fprintf(out, "<p>Date: %s</p>\n", current_date);

    fprintf(out, "<h2>Number of Exchanges by Month</h2>\n");
    fprintf(out, "<table border=\"1\">\n<tr><th>Month/Year</th><th>Count</th></tr>\n");

    // Вывод количества бирж по месяцам
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_exchanges[i] != 0) {
            fprintf(out, "<tr><td>%02d.%d</td><td>%d</td></tr>\n", i, report_year, month_exchanges[i]);
        }
    }
    fprintf(out, "</table>\n");

    fprintf(out, "<h2>Total Amount Exchanged in Rubles by Month in %d</h2>\n", report_year);
    fprintf(out, "<table border=\"1\">\n<tr><th>Month/Year</th><th>Amount</th></tr>\n");

    // Вывод общих сумм по месяцам
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "<tr><td>%02d.%d</td><td>%.2f</td></tr>\n", i, report_year, month_totals[i]);
        }
    }
    fprintf(out, "</table>\n");

    fprintf(out, "<p>Signature: _______________________</p>\n");

    // Конец HTML-документа
    fprintf(out, "</body>\n</html>\n");

    fclose(out);
}


// Вывод списка обменов
void ExchangeSystem::exchanges_print(const Exchange exchanges[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        exchange_to_s(s, exchanges[i]); // Преобразование обмена в строку
        puts(s); // Вывод строки
        puts("");
    }
}

// Вывод списка менеджеров
void ExchangeSystem::managers_print(const Manager managers[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        manager_to_s(s, managers[i]); // Преобразование менеджера в строку
        puts(s); // Вывод строки
        puts("");
    }
}
