// main.c
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>

#include "func.h"
#include "exchange.h"
#include "manager.h"

#define AR_MAN_LEN 100
#define AR_EXCHANGE_LEN 1000
#define TRUE 1


int main() {
    setlocale(LC_ALL, "");
    int man_count = 0; // Количество менеджеров
    int exchange_count = 0; // Количество обменов

    Exchange exchanges[AR_EXCHANGE_LEN]; // Массив для хранения обменов
    Manager managers[AR_MAN_LEN]; // Массив для хранения менеджеров

    int item = -1; // Переменная для выбора пункта меню
    while (item != 0) {
        show_menu(); // Вывод меню
        printf("Выберите действие: "); // Добавлено сообщение после вывода меню
        scanf("%d", &item); // Ввод выбора пользователя
        system("cls"); // Очистка консоли после выбора
        switch (item) {
            case 0:
                printf("Спасибо за использование нашей разработки\n\n");
                break;
            case 1:
                printf("309ИС-22 Донских П. Д.\n");
                printf("Тема курсового проекта: Обменный пункт валют\n\n");
                break;
            case 2:
                save_new_exchange("exchanges.txt"); // Записать данные в файл обмены
                break;
            case 3:
                man_count = load_managers("managers.txt", managers, AR_MAN_LEN); // Загрузить менеджеров
                printf("Файл менеджеров загружен в память\n\n");
                break;
            case 4:
                exchange_count = load_exchanges("exchanges.txt", exchanges, AR_EXCHANGE_LEN); // Загрузить обмены
                printf("Файл обменов загружен в память\n\n");
                break;
            case 5:
                managers_print(managers, man_count); // Печать списка менеджеров
                break;
            case 6:
                exchanges_print(exchanges, exchange_count); // Печать списка обмена
                break;
            case 7:
                do_query1(exchanges, exchange_count, "query1.txt"); // Отчет
                printf("Результат сохранен в файле %s\n\n", "query1.txt");
                break;
            case 8:
                edit_exchange("exchanges.txt"); // Изменено на edit_exchange
                break;
            case 9:
                manage_managers(managers, &man_count); // Управление менеджерами
                break;
            default:
                printf("Ошибка. Пункты от 0 до 9\n\n");
                break;
        }
    }

    return 0;
}
