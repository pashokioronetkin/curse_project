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
    int man_count = 0; // ���������� ����������
    int exchange_count = 0; // ���������� �������

    Exchange exchanges[AR_EXCHANGE_LEN]; // ������ ��� �������� �������
    Manager managers[AR_MAN_LEN]; // ������ ��� �������� ����������

    int item = -1; // ���������� ��� ������ ������ ����
    while (item != 0) {
        show_menu(); // ����� ����
        printf("�������� ��������: "); // ��������� ��������� ����� ������ ����
        scanf("%d", &item); // ���� ������ ������������
        system("cls"); // ������� ������� ����� ������
        switch (item) {
            case 0:
                printf("������� �� ������������� ����� ����������\n\n");
                break;
            case 1:
                printf("309��-22 ������� �. �.\n");
                printf("���� ��������� �������: �������� ����� �����\n\n");
                break;
            case 2:
                save_new_exchange("exchanges.txt"); // �������� ������ � ���� ������
                break;
            case 3:
                man_count = load_managers("managers.txt", managers, AR_MAN_LEN); // ��������� ����������
                printf("���� ���������� �������� � ������\n\n");
                break;
            case 4:
                exchange_count = load_exchanges("exchanges.txt", exchanges, AR_EXCHANGE_LEN); // ��������� ������
                printf("���� ������� �������� � ������\n\n");
                break;
            case 5:
                managers_print(managers, man_count); // ������ ������ ����������
                break;
            case 6:
                exchanges_print(exchanges, exchange_count); // ������ ������ ������
                break;
            case 7:
                do_query1(exchanges, exchange_count, "query1.txt"); // �����
                printf("��������� �������� � ����� %s\n\n", "query1.txt");
                break;
            case 8:
                edit_exchange("exchanges.txt"); // �������� �� edit_exchange
                break;
            case 9:
                manage_managers(managers, &man_count); // ���������� �����������
                break;
            default:
                printf("������. ������ �� 0 �� 9\n\n");
                break;
        }
    }

    return 0;
}
