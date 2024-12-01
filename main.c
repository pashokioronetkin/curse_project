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

//��������� �������
void save_new_sale(char *fname);

int main() {
    setlocale(LC_ALL, "");
    int man_count = 0; //���������� ����������
    int sales_count = 0; //���������� ������

    Sale sales[AR_SALES_LEN]; //������ ��� �������� ������
    Manager managers[AR_MAN_LEN]; //������ ��� �������� ����������

    int item = -1; //���������� ��� ������ ������ ����
    while (item != 0) {
        show_menu(); //����� ����
        scanf("%d", &item); //���� ������ ������������
        switch (item) {
            case 0:
                printf("������� �� ������������� ����� ����������\n\n");
                break;
            case 1:
                printf("309��-22 ������� �. �.\n");
                printf("���� ��������� �������: �������� ����� �����\n\n");
                break;
            case 2:
                save_new_sale("sales.txt"); //��������� ����� �������
                break;
            case 3:
                man_count = load_managers("managers.txt", managers, AR_MAN_LEN); //��������� ����������
                printf("���� ���������� �������� � ������\n\n");
                break;
            case 4:
                sales_count = load_sales("sales.txt", sales, AR_SALES_LEN); //��������� �������
                printf("���� ������ �������� � ������\n\n");
                break;
            case 5:
                managers_print(managers, man_count); //������ ������ ����������
                break;
            case 6:
                sales_print(sales, sales_count); //������ ������ ������
                break;
            case 7:
                do_query1(sales, sales_count, "query1.txt"); //���������� ������� �� ��������
                printf("��������� �������� � ����� %s\n\n", "query1.txt");
                break;
            default:
                printf("������. ������ �� 0 �� 7\n\n");
                break;
        }
    }

    return 0;
}
