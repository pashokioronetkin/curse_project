// main.cpp
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>
#include "func.h"

int main() {
    system("color F0"); // Устанавливает цвет консоли: белый фон и черный текст
    setlocale(LC_ALL, ""); // Устанавливает локаль для корректного отображения символов

    int man_count = 0;      // Количество менеджеров
    int exchange_count = 0; // Количество обменов

    Exchange exchanges[AR_EXCHANGE_LEN]; // Массив для хранения обменов
    Manager managers[AR_MAN_LEN];         // Массив для хранения менеджеров

    // Загрузка данных о менеджерах из файла
    man_count = load_managers("managers.txt", managers, AR_MAN_LEN);
    printf("Файл менеджеров загружен в память\n\n");

    int item = -1; // Переменная для выбора пункта меню
    while (item != 0) {
        // Отображение главного меню
        printf("Главное меню:\n");
        printf("0. Выход\n");
        printf("1. О программе\n");
        printf("2. Я менеджер\n");
        printf("3. Я администратор\n");
        printf("Выберите действие: ");
        scanf("%d", &item);
        system("cls"); // Очистка экрана

        switch (item) {
            case 0:
                // Завершение программы
                printf("Спасибо за использование нашей разработки\n\n");
                break;
            case 1:
                // Информация о программе
                printf("309ИС-22 Донских П. Д.\n");
                printf("Генерация отчетов для обменного пункта валют\n\n");
                break;
            case 2:
                // Вход для менеджера
                manager_login(managers, man_count, exchanges, &exchange_count);
                break;
            case 3:
                // Вход для администратора
                admin_login(managers, &man_count);
                break;
            default:
                // Обработка неверного выбора
                printf("Ошибка. Пункты от 0 до 3\n\n");
                break;
        }
    }

    return 0;
}
