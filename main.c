//main.c
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "func.h"
#include "sale.h"
#include "manager.h"

#define AR_MAN_LEN 100
#define AR_SALES_LEN 1000
#define TRUE 1

//Прототипы функций
void save_new_sale(char *fname);

int main() {
    setlocale(LC_ALL, "");
    int man_count = 0; //Количество менеджеров
    int sales_count = 0; //Количество продаж

    Sale sales[AR_SALES_LEN]; //Массив для хранения продаж
    Manager managers[AR_MAN_LEN]; //Массив для хранения менеджеров

    int item = -1; //Переменная для выбора пункта меню
    while (item != 0) {
        show_menu(); //Вывод меню
        scanf("%d", &item); //Ввод выбора пользователя
        switch (item) {
            case 0:
                printf("Спасибо за использование нашей разработки\n\n");
                break;
            case 1:
                printf("309ИС-22 Донских П. Д.\n");
                printf("Тема курсового проекта: Обменный пункт валют\n\n");
                break;
            case 2:
                save_new_sale("sales.txt"); //Сохранить новую продажу
                break;
            case 3:
                man_count = load_managers("managers.txt", managers, AR_MAN_LEN); //Загрузить менеджеров
                printf("Файл менеджеров загружен в память\n\n");
                break;
            case 4:
                sales_count = load_sales("sales.txt", sales, AR_SALES_LEN); //Загрузить продажи
                printf("Файл продаж загружен в память\n\n");
                break;
            case 5:
                managers_print(managers, man_count); //Печать списка менеджеров
                break;
            case 6:
                sales_print(sales, sales_count); //Печать списка продаж
                break;
            case 7:
                do_query1(sales, sales_count, "query1.txt"); //Выполнение запроса по продажам
                printf("Результат сохранен в файле %s\n\n", "query1.txt");
                break;
            default:
                printf("Ошибка. Пункты от 0 до 7\n\n");
                break;
        }
    }

    return 0;
}
