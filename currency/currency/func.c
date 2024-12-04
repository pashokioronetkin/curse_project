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
    "������", "�������", "�����", "������", "���", "����",
    "����", "�������", "��������", "�������", "������", "�������"
};

//��������� ������� ���� � ��������� �������
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names[tm.tm_mon], tm.tm_year + 1900);
}

//�������������� ������� � ������
void sale_to_s(char s[100], Sale sale) {
    char format[] = "%d. %02d.%02d.%04d %d %s %d";
    sprintf(s, format, sale.sale_id, sale.date.day, sale.date.month, sale.date.year, sale.manager_id, sale.currency, sale.price);
}

//�������������� ��������� � ������
void manager_to_s(char s[150], Manager manager) {
    snprintf(s, 150, "%d. %s %s %s", manager.manager_id, manager.manager_surname, manager.manager_name, manager.manager_patronymic);
}

//����
void show_menu() {
    printf(
        "0. �����\n"
        "1. � ���������\n"
        "2. �������� ������ � ���� ������\n"
        "3. �������� �� ����� ����������\n"
        "4. �������� �� ����� ������\n"
        "5. ������ ������ ����������\n"
        "6. ������ ������ ������\n"
        "7. ���������� ������� �� ��������\n"
        "8. ������������� �������\n\n"); //��������� ����� ����
}

//�������� ������������� ID ������� � �����
int check_sale_id_exists(char *fname, int sale_id) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� ����� ��� ������");
        return 0;
    }

    Sale rec; //������ �������
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &rec.sale_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        if (rec.sale_id == sale_id) {
            fclose(in);
            return 1; //ID ������� ����������
        }
    }
    fclose(in);
    return 0; //ID ������� �� ����������
}

//���� ������ � �������
void input_sale(Sale *sale, char *fname) {
    printf("������� ID �������: ");
    while (scanf("%d", &sale->sale_id) != 1 || check_sale_id_exists(fname, sale->sale_id)) {
        if (check_sale_id_exists(fname, sale->sale_id)) {
            printf("������: ID ������� %d ��� ����������. ����������, ������� ���������� ID: ", sale->sale_id);
        } else {
            printf("������ �����. ����������, ������� ����� ����� ��� ID �������: ");
        }
        while(getchar() != '\n');
    }

    printf("������� ���� ������� (��.��.����): ");
    while (scanf("%d.%d.%d", &sale->date.day, &sale->date.month, &sale->date.year) != 3 ||
           sale->date.day < 1 || sale->date.day > 31 ||
           sale->date.month < 1 || sale->date.month > 12 ||
           (sale->date.month == 2 && sale->date.day > 29) || //�������� �� �������
           (sale->date.month == 4 && sale->date.day > 30) || //�������� �� ������
           (sale->date.month == 6 && sale->date.day > 30) || //�������� �� ����
           (sale->date.month == 9 && sale->date.day > 30) || //�������� �� ��������
           (sale->date.month == 11 && sale->date.day > 30)) { //�������� �� ������
        printf("������ �����. ����������, ������� ���� � ������� ��.��.����: ");
        while(getchar() != '\n');
    }

    printf("������� ID ��������� (1-2): ");
    while (scanf("%d", &sale->manager_id) != 1 || (sale->manager_id < 1 || sale->manager_id > 2)) {
        printf("������ �����. ����������, ������� ID ��������� (1-2): ");
        while(getchar() != '\n');
    }

    printf("������� ������ (USD, EURO): ");
    while (scanf("%s", sale->currency) != 1 || (strcmp(sale->currency, "USD") != 0 && strcmp(sale->currency, "EURO") != 0)) {
        printf("������ �����. ����������, ������� ������ (USD, EURO): ");
        while(getchar() != '\n');
    }

    printf("������� ����: ");
    while (scanf("%d", &sale->price) != 1 || sale->price < 0) {
        printf("������ �����. ����������, ������� ������������� ����� ����� ��� ����: ");
        while(getchar() != '\n');
    }
}

//���������� ����� ������� � ����
void save_new_sale(char *fname) {
    Sale sale; //������ �������
    input_sale(&sale, fname); //���� ������ � �������

    FILE *out = fopen(fname, "a");
    if (out == NULL) {
        perror("������ �������� ����� ��� ������");
        return;
    }

    fprintf(out, "%d %02d.%02d.%04d %d %s %d\n", sale.sale_id, sale.date.day, sale.date.month, sale.date.year, sale.manager_id, sale.currency, sale.price);
    fclose(out);
    printf("������� ���������.\n\n");
}

//������� ��� �������������� ������������ �������
void edit_sale(char *fname) {
    Sale sale; //������ �������
    int sale_id;

    printf("������� ID ������� ��� ��������������: ");
    scanf("%d", &sale_id);

    //�������� ������������� ID �������
    if (!check_sale_id_exists(fname, sale_id)) {
        printf("������: ID ������� %d �� ����������.\n", sale_id);
        return;
    }

    //�������� ������������ �������
    FILE *in = fopen(fname, "r");
    FILE *temp = fopen("temp.txt", "w"); //��������� ���� ��� �������� ����������� ������
    if (in == NULL || temp == NULL) {
        perror("������ �������� �����");
        return;
    }

    //������ ������ �� ����� � �������������� ������ ������
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &sale.sale_id, &sale.date.day, &sale.date.month, &sale.date.year, &sale.manager_id, sale.currency, &sale.price) == 7) {
        if (sale.sale_id == sale_id) {
            printf("�������������� ������� � ID %d:\n", sale_id);
            //���� ����� ������, �� ID �������� �������
            printf("������� ����� ���� ������� (��.��.����): ");
            while (scanf("%d.%d.%d", &sale.date.day, &sale.date.month, &sale.date.year) != 3 ||
                   sale.date.day < 1 || sale.date.day > 31 ||
                   sale.date.month < 1 || sale.date.month > 12 ||
                   (sale.date.month == 2 && sale.date.day > 29) || //�������� �� �������
                   (sale.date.month == 4 && sale.date.day > 30) || //�������� �� ������
                   (sale.date.month == 6 && sale.date.day > 30) || //�������� �� ����
                   (sale.date.month == 9 && sale.date.day > 30) || //�������� �� ��������
                   (sale.date.month == 11 && sale.date.day > 30)) { //�������� �� ������
                printf("������ �����. ����������, ������� ���� � ������� ��.��.����: ");
                while(getchar() != '\n');
            }

            printf("������� ����� ID ��������� (1-2): ");
            while (scanf("%d", &sale.manager_id) != 1 || (sale.manager_id < 1 || sale.manager_id > 2)) {
                printf("������ �����. ����������, ������� ID ��������� (1-2): ");
                while(getchar() != '\n');
            }

            printf("������� ����� ������ (USD, EURO): ");
            while (scanf("%s", sale.currency) != 1 || (strcmp(sale.currency, "USD") != 0 && strcmp(sale.currency, "EURO") != 0)) {
                printf("������ �����. ����������, ������� ������ (USD, EURO): ");
                while(getchar() != '\n');
            }

            printf("������� ����� ����: ");
            while (scanf("%d", &sale.price) != 1 || sale.price < 0) {
                printf("������ �����. ����������, ������� ������������� ����� ����� ��� ����: ");
                while(getchar() != '\n');
            }
        }
        //������ ������ � ��������� ����
        fprintf(temp, "%d %02d.%02d.%04d %d %s %d\n", sale.sale_id, sale.date.day, sale.date.month, sale.date.year, sale.manager_id, sale.currency, sale.price);
    }

    fclose(in);
    fclose(temp);
    remove(fname); //�������� ������� �����
    rename("temp.txt", fname); //�������������� ���������� ����� � ������������
    printf("������� � ID %d ������� ���������������.\n", sale_id);
}

//�������� ���������� �� �����
int load_managers(char *fname, Manager managers[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� �����");
        return 0;
    }

    int count = 0; //������� ����������� ����������
    Manager rec; //������ ���������
    while (count < limit && fscanf(in, "%d %s %s %s", &rec.manager_id, rec.manager_surname, rec.manager_name, rec.manager_patronymic) == 4) {
        managers[count] = rec; //���������� ��������� � ������
        count++;
    }
    fclose(in);
    return count; //������� ���������� ����������� ����������
}

//�������� ������ �� �����
int load_sales(char *fname, Sale sales[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� �����");
        return 0;
    }

    int count = 0; //������� ����������� ������
    Sale rec; //������ �������
    while (count < limit && fscanf(in, "%d %d.%d.%d %d %s %d", &rec.sale_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        sales[count] = rec; //���������� ������� � ������
        count++;
    }
    fclose(in);
    return count; //������� ���������� ����������� ������
}

//������ ������ ������
void sales_print(Sale sales[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        sale_to_s(s, sales[i]); //�������������� ������� � ������
        puts(s); //����� ������
        puts("");
    }
}

//������ ������ ����������
void managers_print(Manager managers[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        manager_to_s(s, managers[i]); //�������������� ��������� � ������
        puts(s); //����� ������
        puts("");
    }
}

//���������� ������� �� ��������
void do_query1(Sale sales[], int limit, const char *fname) {
    if (limit == 0) { //�������� �� ������� ������
        printf("��� ������ ��� ��������� �������.\n");
        return;
    }

    int month_sales[N_MONTHS + 1] = {0}; //������ ��� �������� ���������� ������ �� �������
    int month_totals[N_MONTHS + 1] = {0}; //������ ��� �������� ���� �� �������

    //��������� �������� ����
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900; //������� ���

    //������� ���� ������ � ������� �� ������� � �����
    for (int i = 0; i < limit; i++) {
        int month = sales[i].date.month; //����� �������
        int year = sales[i].date.year; //��� �������

        //������� ������ ������� �������� ����
        if (year == current_year) {
            month_sales[month]++; //����������� ���������� ������ �� �����
            month_totals[month] += sales[i].price; //��������� ���� �� �������
        }
    }

    FILE *out = fopen(fname, "w");
    if (out == NULL) {
        perror("������ �������� �����");
        return;
    }

    //����� ���������
    fprintf(out, "����� �� ��������\n");
    fprintf(out, "���� EURO: \n");
    fprintf(out, "���� USD: \n");
    fprintf(out, "����: ");
    char current_date[100];
    get_current_date(current_date); //��������� ������� ����
    fprintf(out, "%s\n", current_date);
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "�����/��� ����������\n");

    //����� ���������� ������ �� �������
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_sales[i] != 0) {
            fprintf(out, "%02d.%d %d\n", i, current_year, month_sales[i]); //���������� ������� ���
        }
    }

    //����� ���������� ����� �� ������� ��� �������� ����
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "����� ���������� ����� �� ������� � %d ����:\n", current_year);
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "%02d.%d: %d\n", i, current_year, month_totals[i]);
        }
    }

    //������� �� ��������� ��������
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "�������: _______________________\n");

    fclose(out);
}
