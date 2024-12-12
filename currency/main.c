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

int main() {
    system("color F0"); // Цвет консоли - белый, цвет текста - черный
    setlocale(LC_ALL, "");
    int man_count = 0; // Количество менеджеров
    int exchange_count = 0; // Количество обменов

    Exchange exchanges[AR_EXCHANGE_LEN]; // Массив для хранения обменов
    Manager managers[AR_MAN_LEN]; // Массив для хранения менеджеров

    man_count = load_managers("managers.txt", managers, AR_MAN_LEN); // Загрузить менеджеров
    printf("Файл менеджеров загружен в память\n\n");

    int item = -1; // Переменная для выбора пункта меню
    while (item != 0) {
        printf("Главное меню:\n");
        printf("0. Выход\n");
        printf("1. О программе\n");
        printf("2. Я менеджер\n");
        printf("3. Я администратор\n");
        printf("Выберите действие: ");
        scanf("%d", &item); // Ввод выбора пользователя
        system("cls"); // Очистка консоли после выбора
        switch (item) {
            case 0:
                printf("Спасибо за использование нашей разработки\n\n");
                break;
            case 1:
                printf("309ИС-22 Донских П. Д.\n");
                printf("Генерация отчетов для обменного пункта валют\n\n");
                break;
            case 2:
                manager_login(managers, man_count, exchanges, &exchange_count); // Вход для менеджера
                break;
            case 3:
                admin_login(managers, &man_count); // Вход для администратора
                break;
            default:
                printf("Ошибка. Пункты от 0 до 3\n\n");
                break;
        }
    }

    return 0;
}
