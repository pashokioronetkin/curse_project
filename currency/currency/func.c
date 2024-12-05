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
    "������", "�������", "�����", "������", "���", "����",
    "����", "�������", "��������", "�������", "������", "�������"
};

// ��������� ������� ���� � ��������� �������
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names[tm.tm_mon], tm.tm_year + 1900);
}

// �������������� ������ � ������
void exchange_to_s(char s[100], Exchange exchange) {
    char format[] = "%d. %02d.%02d.%04d %d %s %d";
    sprintf(s, format, exchange.exchange_id, exchange.date.day, exchange.date.month, exchange.date.year, exchange.manager_id, exchange.currency, exchange.price);
}

// �������������� ��������� � ������
void manager_to_s(char s[150], Manager manager) {
    snprintf(s, 150, "%d. %s %s %s", manager.manager_id, manager.manager_surname, manager.manager_name, manager.manager_patronymic);
}

// ����
void show_menu() {
    printf(
        "0. �����\n"
        "1. � ���������\n"
        "2. �������� ������ � ���� �������\n"
        "3. �������� �� ����� ����������\n"
        "4. �������� �� ����� �������\n"
        "5. ������ ������ ����������\n"
        "6. ������ ������ �������\n"
        "7. ���������� ������� �� �������\n"
        "8. ������������� �����\n"
        "9. ���������� �����������\n\n");
}

// �������� ������������� ID ������ � �����
int check_exchange_id_exists(char *fname, int exchange_id) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� ����� ��� ������");
        return 0;
    }

    Exchange rec; // ������ ������
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &rec.exchange_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        if (rec.exchange_id == exchange_id) {
            fclose(in);
            return 1; // ID ������ ����������
        }
    }
    fclose(in);
    return 0; // ID ������ �� ����������
}

// ���� ������ � ������
void input_exchange(Exchange *exchange, char *fname) {
    printf("������� ID ������: ");
    while (scanf("%d", &exchange->exchange_id) != 1 || check_exchange_id_exists(fname, exchange->exchange_id)) {
        if (check_exchange_id_exists(fname, exchange->exchange_id)) {
            printf("������: ID ������ %d ��� ����������. ����������, ������� ���������� ID: ", exchange->exchange_id);
        } else {
            printf("������ �����. ����������, ������� ����� ����� ��� ID ������: ");
        }
        while(getchar() != '\n');
    }

    printf("������� ���� ������ (��.��.����): ");
    while (scanf("%d.%d.%d", &exchange->date.day, &exchange->date.month, &exchange->date.year) != 3 ||
           exchange->date.day < 1 || exchange->date.day > 31 ||
           exchange->date.month < 1 || exchange->date.month > 12 ||
           (exchange->date.month == 2 && exchange->date.day > 29) || // �������� �� �������
           (exchange->date.month == 4 && exchange->date.day > 30) || // �������� �� ������
           (exchange->date.month == 6 && exchange->date.day > 30) || // �������� �� ����
           (exchange->date.month == 9 && exchange->date.day > 30) || // �������� �� ��������
           (exchange->date.month == 11 && exchange->date.day > 30)) { // �������� �� ������
        printf("������ �����. ����������, ������� ���� � ������� ��.��.����: ");
        while(getchar() != '\n');
    }

    printf("������� ID ��������� (1-2): ");
    while (scanf("%d", &exchange->manager_id) != 1 || (exchange->manager_id < 1 || exchange->manager_id > 2)) {
        printf("������ �����. ����������, ������� ID ��������� (1-2): ");
        while(getchar() != '\n');
    }

    printf("������� ������ (USD, EURO): ");
    while (scanf("%s", exchange->currency) != 1 || (strcmp(exchange->currency, "USD") != 0 && strcmp(exchange->currency, "EURO") != 0)) {
        printf("������ �����. ����������, ������� ������ (USD, EURO): ");
        while(getchar() != '\n');
    }

    printf("������� ����: ");
    while (scanf("%d", &exchange->price) != 1 || exchange->price < 0) {
        printf("������ �����. ����������, ������� ������������� ����� ����� ��� ����: ");
        while(getchar() != '\n');
    }
}

// ���������� ������ ������ � ����
void save_new_exchange(char *fname) {
    Exchange exchange; // ������ ������
    input_exchange(&exchange, fname); // ���� ������ � ������

    FILE *out = fopen(fname, "a");
    if (out == NULL) {
        perror("������ �������� ����� ��� ������");
        return;
    }

    fprintf(out, "%d %02d.%02d.%04d %d %s %d\n", exchange.exchange_id, exchange.date.day, exchange.date.month, exchange.date.year, exchange.manager_id, exchange.currency, exchange.price);
    fclose(out);
    printf("����� ��������.\n\n");
}

// ������� ��� �������������� ������������� ������
void edit_exchange(char *fname) {
    Exchange exchange; // ������ ������
    int exchange_id;

    printf("������� ID ������ ��� ��������������: ");
    scanf("%d", &exchange_id);

    // �������� ������������� ID ������
    if (!check_exchange_id_exists(fname, exchange_id)) {
        printf("������: ID ������ %d �� ����������.\n", exchange_id);
        return;
    }

    // �������� ������������� ������
    FILE *in = fopen(fname, "r");
    FILE *temp = fopen("temp.txt", "w"); // ��������� ���� ��� �������� ����������� ������
    if (in == NULL || temp == NULL) {
        perror("������ �������� �����");
        return;
    }

    // ������ ������ �� ����� � �������������� ������ ������
    while (fscanf(in, "%d %d.%d.%d %d %s %d", &exchange.exchange_id, &exchange.date.day, &exchange.date.month, &exchange.date.year, &exchange.manager_id, exchange.currency, &exchange.price) == 7) {
        if (exchange.exchange_id == exchange_id) {
            printf("�������������� ������ � ID %d:\n", exchange_id);
            // ���� ����� ������, �� ID �������� �������
            printf("������� ����� ���� ������ (��.��.����): ");
            while (scanf("%d.%d.%d", &exchange.date.day, &exchange.date.month, &exchange.date.year) != 3 ||
                   exchange.date.day < 1 || exchange.date.day > 31 ||
                   exchange.date.month < 1 || exchange.date.month > 12 ||
                   (exchange.date.month == 2 && exchange.date.day > 29) || // �������� �� �������
                   (exchange.date.month == 4 && exchange.date.day > 30) || // �������� �� ������
                   (exchange.date.month == 6 && exchange.date.day > 30) || // �������� �� ����
                   (exchange.date.month == 9 && exchange.date.day > 30) || // �������� �� ��������
                   (exchange.date.month == 11 && exchange.date.day > 30)) { // �������� �� ������
                printf("������ �����. ����������, ������� ���� � ������� ��.��.����: ");
                while(getchar() != '\n');
            }

            printf("������� ����� ������ (USD, EURO): ");
            while (scanf("%s", exchange.currency) != 1 || (strcmp(exchange.currency, "USD") != 0 && strcmp(exchange.currency, "EURO") != 0)) {
                printf("������ �����. ����������, ������� ������ (USD, EURO): ");
                while(getchar() != '\n');
            }

            printf("������� ����� ����: ");
            while (scanf("%d", &exchange.price) != 1 || exchange.price < 0) {
                printf("������ �����. ����������, ������� ������������� ����� ����� ��� ����: ");
                while(getchar() != '\n');
            }
        }
        fprintf(temp, "%d %02d.%02d.%04d %d %s %d\n", exchange.exchange_id, exchange.date.day, exchange.date.month, exchange.date.year, exchange.manager_id, exchange.currency, exchange.price);
    }

    fclose(in);
    fclose(temp);
    remove(fname); // ������� ������ ����
    rename("temp.txt", fname); // ��������������� ��������� ����
    printf("����� � ID %d ������� ��������������.\n\n", exchange_id);
}

// ������ ������ �������
void exchanges_print(Exchange exchanges[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        exchange_to_s(s, exchanges[i]);
        puts(s); // ����� ������
        puts("");
    }
}

// �������� ������� �� �����
int load_exchanges(char *fname, Exchange exchanges[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� �����");
        return 0;
    }

    int count = 0; // ������� ����������� �������
    Exchange rec; // ������ ������
    while (count < limit && fscanf(in, "%d %d.%d.%d %d %s %d", &rec.exchange_id, &rec.date.day, &rec.date.month, &rec.date.year, &rec.manager_id, rec.currency, &rec.price) == 7) {
        exchanges[count] = rec; // ���������� ������ � ������
        count++;
    }
    fclose(in);
    return count; // ������� ���������� ����������� �������
}

// �������� ���������� �� �����
int load_managers(char *fname, Manager managers[], int limit) {
    FILE *in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� �����");
        return 0;
    }

    int count = 0; // ������� ����������� ����������
    Manager rec; // ������ ���������
    while (count < limit && fscanf(in, "%d %s %s %s", &rec.manager_id, rec.manager_surname, rec.manager_name, rec.manager_patronymic) == 4) {
        managers[count] = rec; // ���������� ��������� � ������
        count++;
    }
    fclose(in);
    return count; // ������� ���������� ����������� ����������
}

// ������ ������ ����������
void managers_print(Manager managers[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        manager_to_s(s, managers[i]); // �������������� ��������� � ������
        puts(s); // ����� ������
        puts("");
    }
}

// ���������� ������� �� �������
void do_query1(Exchange exchanges[], int limit, const char *fname) {
    if (limit == 0) { // �������� �� ������� �������
        printf("��� ������� ��� ��������� �������.\n");
        return;
    }

    int month_exchanges[N_MONTHS + 1] = {0}; // ������ ��� �������� ���������� ������� �� �������
    int month_totals[N_MONTHS + 1] = {0}; // ������ ��� �������� ���� �� �������

    // ��������� �������� ����
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900; // ������� ���

    // ������� ���� ������� � ������� �� ������� � �����
    for (int i = 0; i < limit; i++) {
        int month = exchanges[i].date.month; // ����� ������
        int year = exchanges[i].date.year; // ��� ������

        // ������� ������ ������ �������� ����
        if (year == current_year) {
            month_exchanges[month]++; // ����������� ���������� ������� �� �����
            month_totals[month] += exchanges[i].price; // ��������� ���� �� �������
        }
    }

    FILE *out = fopen(fname, "w");
    if (out == NULL) {
        perror("������ �������� �����");
        return;
    }

    // ����� ���������
    fprintf(out, "����� �� �������\n");
    fprintf(out, "���� EURO: \n");
    fprintf(out, "���� USD: \n");
    fprintf(out, "����: ");
    char current_date[100];
    get_current_date(current_date); // ��������� ������� ����
    fprintf(out, "%s\n", current_date);
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "�����/��� ����������\n");

    // ����� ���������� ������� �� �������
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_exchanges[i] != 0) {
            fprintf(out, "%02d.%d %d\n", i, current_year, month_exchanges[i]); // ���������� ������� ���
        }
    }

    // ����� ���������� ����� �� ������� ��� �������� ����
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "����� ���������� ����� �� ������� � %d ����:\n", current_year);
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "%02d.%d: %d\n", i, current_year, month_totals[i]);
        }
    }

    // ������� �� ��������� ��������
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "�������: _______________________\n");

    fclose(out);
}

// ������� ��� ���������� �����������
void manage_managers(Manager managers[], int *count) {
    int action;
    printf("1. �������� ���������\n");
    printf("2. ������� ���������\n");
    printf("�������� ��������: ");
    scanf("%d", &action);

    switch (action) {
        case 1:
            add_manager(managers, count);
            break;
        case 2:
            remove_manager(managers, count);
            break;
        default:
            printf("������: �������� �����.\n");
            break;
    }
}

// ������� ��� ���������� ���������
void add_manager(Manager managers[], int *count) {
    if (*count >= AR_MAN_LEN) {
        printf("������: ���������� ������������ ���������� ����������.\n");
        return;
    }

    Manager new_manager;
    printf("������� ID ���������: ");
    scanf("%d", &new_manager.manager_id);

    // �������� �� ������������ ID
    for (int i = 0; i < *count; i++) {
        if (managers[i].manager_id == new_manager.manager_id) {
            printf("������: �������� � ID %d ��� ����������.\n", new_manager.manager_id);
            return;
        }
    }

    printf("������� ��� ���������: ");
    scanf("%s", new_manager.manager_name);
    printf("������� ������� ���������: ");
    scanf("%s", new_manager.manager_surname);
    printf("������� �������� ���������: ");
    scanf("%s", new_manager.manager_patronymic);

    managers[*count] = new_manager; // ���������� ������ ��������� � ������
    (*count)++; // ���������� �������� ����������
    printf("�������� ��������.\n\n");
}

// ������� ��� �������� ���������
void remove_manager(Manager managers[], int *count) {
    int id;
    printf("������� ID ��������� ��� ��������: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (managers[i].manager_id == id) {
            found = 1;
            // �������� ���� ���������� ����� ���������� �� ���� ������� �����
            for (int j = i; j < *count - 1; j++) {
                managers[j] = managers[j + 1];
            }
            (*count)--; // ��������� ������� ����������
            printf("�������� � ID %d ������.\n\n", id);
            break;
        }
    }

    if (!found) {
        printf("������: �������� � ID %d �� ������.\n\n", id);
    }
}
