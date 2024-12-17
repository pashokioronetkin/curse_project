// main.cpp
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>
#include "func.h"

int main() {
    system("color F0"); // ������������� ���� �������: ����� ��� � ������ �����
    setlocale(LC_ALL, ""); // ������������� ������ ��� ����������� ����������� ��������

    int man_count = 0;      // ���������� ����������
    int exchange_count = 0; // ���������� �������

    Exchange exchanges[AR_EXCHANGE_LEN]; // ������ ��� �������� �������
    Manager managers[AR_MAN_LEN];         // ������ ��� �������� ����������

    // �������� ������ � ���������� �� �����
    man_count = load_managers("managers.txt", managers, AR_MAN_LEN);
    printf("���� ���������� �������� � ������\n\n");

    int item = -1; // ���������� ��� ������ ������ ����
    while (item != 0) {
        // ����������� �������� ����
        printf("������� ����:\n");
        printf("0. �����\n");
        printf("1. � ���������\n");
        printf("2. � ��������\n");
        printf("3. � �������������\n");
        printf("�������� ��������: ");
        scanf("%d", &item);
        system("cls"); // ������� ������

        switch (item) {
            case 0:
                // ���������� ���������
                printf("������� �� ������������� ����� ����������\n\n");
                break;
            case 1:
                // ���������� � ���������
                printf("309��-22 ������� �. �.\n");
                printf("��������� ������� ��� ��������� ������ �����\n\n");
                break;
            case 2:
                // ���� ��� ���������
                manager_login(managers, man_count, exchanges, &exchange_count);
                break;
            case 3:
                // ���� ��� ��������������
                admin_login(managers, &man_count);
                break;
            default:
                // ��������� ��������� ������
                printf("������. ������ �� 0 �� 3\n\n");
                break;
        }
    }

    return 0;
}
