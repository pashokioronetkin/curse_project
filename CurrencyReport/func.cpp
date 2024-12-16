// func.cpp
#include "func.h"
#include <ctime>
#include <cstring>

// �������� �������
const char* ExchangeSystem::month_names[12] = {
    "������", "�������", "�����", "������", "���", "����",
    "����", "�������", "��������", "�������", "������", "�������"
};

const char* ExchangeSystem::month_names1[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};


int ExchangeSystem::get_current_year() {
    time_t t = time(NULL); // ��������� �������� �������
    struct tm tm = *localtime(&t); // �������������� ������� � ��������� �����
    return tm.tm_year + 1900; // ���������� ������� ���
}

// ��������� ������� ���� � ��������� �������
void ExchangeSystem::get_current_date(char* date_str) {
    time_t t = time(NULL); // ��������� �������� �������
    struct tm tm = *localtime(&t); // �������������� ������� � ��������� �����
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names[tm.tm_mon], tm.tm_year + 1900); // �������������� ����
}


void ExchangeSystem::get_current_date1(char* date_str) {
    time_t t = time(NULL); // ��������� �������� �������
    struct tm tm = *localtime(&t); // �������������� ������� � ��������� �����
    sprintf(date_str, "%d %s %d", tm.tm_mday, month_names1[tm.tm_mon], tm.tm_year + 1900); // �������������� ����
}

// �������������� ���������� � ��������� � ������
void ExchangeSystem::manager_to_s(char s[150], const Manager& manager) {
    snprintf(s, 150, "%d. %s %s %s",
             manager.manager_id,
             manager.manager_surname,
             manager.manager_name,
             manager.manager_patronymic);
}

// �������������� ���������� �� ������ � ������
void ExchangeSystem::exchange_to_s(char s[100], const Exchange& exchange) {
    sprintf(s, "%d. %02d.%02d.%04d %d %s %.2f", // ���������� %.2f ��� ������
            exchange.exchange_id,
            exchange.date.day,
            exchange.date.month,
            exchange.date.year,
            exchange.manager_id,
            exchange.currency,
            exchange.price);
}


// ���� ��������������
void ExchangeSystem::admin_menu(Manager managers[], int* man_count) {
    int choice = -1;
    while (choice != 0) {
        printf("���� ��������������:\n");
        printf("0. �����\n");
        printf("1. �������� ���������\n");
        printf("2. ������� ���������\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);
        system("cls"); // ������� ������

        switch (choice) {
            case 0:
                printf("����� �� ���� ��������������.\n");
                break;
            case 1:
                add_manager(managers, man_count); // ���������� ���������
                break;
            case 2:
                remove_manager(managers, man_count); // �������� ���������
                break;
            default:
                printf("������: �������� �����.\n");
                break;
        }
    }
}

// ���� ���������
void ExchangeSystem::manager_login(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count) {
    int manager_id;
    printf("������� ID ���������: ");

    if (scanf("%d", &manager_id) != 1) {
        printf("������ �����.\n");
        return;
    }

    bool found = false;
    for (int i = 0; i < man_count; i++) {
        if (managers[i].manager_id == manager_id) {
            found = true;
            printf("����� ����������, %s %s %s!\n",
                   managers[i].manager_surname,
                   managers[i].manager_name,
                   managers[i].manager_patronymic);
            system("pause"); // ����� ����� �������� ������
            system("cls");
            manager_menu(managers, man_count, exchanges, exchange_count, manager_id); // ������� � ���� ���������
            break;
        }
    }

    if (!found) {
        printf("����� � �������: �������� � ID %d �� ������.\n", manager_id);
    }
}

// ����������� ���� ���������
void ExchangeSystem::show_menu() {
    printf(
        "0. �����\n"
        "1. �������� ������ � ���� �������\n"
        "2. ������������� �����\n"
        "3. �������� �� ����� ����������\n"
        "4. �������� �� ����� �������\n"
        "5. ���������� ������ � .html\n"
        "6. ���������� ������ � .txt\n\n");
}

// ���� ���������
void ExchangeSystem::manager_menu(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count, int current_manager_id) {
    int choice = -1;
    while (choice != 0) {
        show_menu(); // �������� ���� ���������
        printf("�������� ��������: ");
        scanf("%d", &choice);
        system("cls"); // ������� ������

        switch (choice) {
            case 0:
                printf("����� �� ���� ���������.\n");
                break;
            case 1:
                save_new_exchange("exchanges.txt", current_manager_id); // ���������� ������ ������
                break;
            case 2:
                edit_exchange("exchanges.txt", current_manager_id); // �������������� ������
                break;
            case 3:
                *exchange_count = load_managers("managers.txt", managers, AR_MAN_LEN); // �������� ����������
                printf("��������� ����������: %d\n", *exchange_count);
                printf("������ ����������:\n");
                managers_print(managers, *exchange_count); // ������ ������ ����������
                break;
            case 4:
                *exchange_count = load_exchanges("exchanges.txt", exchanges, AR_EXCHANGE_LEN); // �������� �������
                printf("��������� �������: %d\n", *exchange_count);
                printf("���������� ����� exchanges.txt:\n");
                exchanges_print(exchanges, *exchange_count); // ������ ������ �������
                break;
            case 5:
                do_query1(exchanges, *exchange_count, "query1.html"); // ������������ ������ � html
                printf("����� ������� �����������.\n");
                break;
            case 6:
                do_query(exchanges, *exchange_count, "query1.txt"); // ������������ ������ � txt
                printf("����� ������� �����������.\n");
                break;
            default:
                printf("������. ����������, �������� ����� �� 0 �� 5.\n");
                break;
        }
    }
}


// ���� ��������������
void ExchangeSystem::admin_login(Manager managers[], int* man_count) {
    char password[50];
    printf("������� ������ ��������������: ");
    getchar(); // ������� ������ �����
    fgets(password, sizeof(password), stdin); // ���� ������
    password[strcspn(password, "\n")] = 0; // �������� ������� ����� ������

    if (strcmp(password, "123") == 0) {
        printf("����� ����������, �������������!\n");
        system("pause");
        system("cls");
        admin_menu(managers, man_count); // ������� � ���� ��������������
    } else {
        printf("�������� ������. ������ ��������.\n");
    }
}

// �������� ������������� ID ������
bool ExchangeSystem::check_exchange_id_exists(const char* fname, int exchange_id) {
    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� ����� ��� ������");
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
            return true; // ID ������
        }
    }
    fclose(in);
    return false; // ID �� ������
}

// ���������� ������ ������
void ExchangeSystem::save_new_exchange(const char* fname, int current_manager_id) {
    Exchange exchange;
    printf("������� ID ������: ");
    while (scanf("%d", &exchange.exchange_id) != 1 ||
           check_exchange_id_exists(fname, exchange.exchange_id)) {
        if (check_exchange_id_exists(fname, exchange.exchange_id)) {
            printf("������: ID ������ %d ��� ����������. ������� ���������� ID: ",
                   exchange.exchange_id);
        } else {
            printf("������ �����. ������� ����� ����� ��� ID ������: ");
        }
        while(getchar() != '\n'); // ������� ������ �����
    }

    printf("������� ���� ������ (��.��.����): ");
    while (scanf("%d.%d.%d",
           &exchange.date.day,
           &exchange.date.month,
           &exchange.date.year) != 3 ||
           !validate_date(exchange.date)) {
        printf("������ �����. ������� ���� � ������� ��.��.����: ");
        while(getchar() != '\n');
    }

    // ������������� ID ��������� �� ���������
    exchange.manager_id = current_manager_id;

    printf("������� ������ (USD, EURO): ");
    while (scanf("%s", exchange.currency) != 1 ||
           (strcmp(exchange.currency, "USD") != 0 &&
            strcmp(exchange.currency, "EURO") != 0)) {
        printf("������ �����. ������� ������ (USD, EURO): ");
        while(getchar() != '\n');
    }

    printf("������� ����: ");
    while (scanf("%lf", &exchange.price) != 1 || exchange.price < 0) { // ���������� %lf ��� double
        printf("������ �����. ������� ������������� ����� ��� ����: ");
        while(getchar() != '\n');
    }

    FILE* out = fopen(fname, "a");
    if (out == NULL) {
        perror("������ �������� ����� ��� ������");
        return;
    }

    fprintf(out, "%d %02d.%02d.%04d %d %s %.2f\n", // ���������� %.2f ��� ������
            exchange.exchange_id,
            exchange.date.day,
            exchange.date.month,
            exchange.date.year,
            exchange.manager_id,
            exchange.currency,
            exchange.price);
    fclose(out);
    printf("����� ��������.\n\n");
}

// �������������� ������
void ExchangeSystem::edit_exchange(const char* fname, int current_manager_id) {
    int exchange_id;
    printf("������� ID ������ ��� ��������������: ");
    if (scanf("%d", &exchange_id) != 1) {
        printf("������ �����.\n");
        return;
    }

    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� ����� ��� ������");
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
            printf("�������������� ������ � ID %d:\n", exchange_id);
            printf("������� ����� ���� ������ (��.��.����): ");
            scanf("%d.%d.%d", &exchanges[i].date.day, &exchanges[i].date.month, &exchanges[i].date.year);
            // ������������� ID ��������� �� ���������
            exchanges[i].manager_id = current_manager_id;
            printf("������� ����� ������ (USD, EURO): ");
            scanf("%s", exchanges[i].currency);
            printf("������� ����� ����: ");
            scanf("%lf", &exchanges[i].price); // ���������� %lf ��� double
            break;
        }
    }

    if (!found) {
        printf("����� � ID %d �� ������.\n", exchange_id);
        return;
    }

    FILE* out = fopen(fname, "w");
    if (out == NULL) {
        perror("������ �������� ����� ��� ������");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(out, "%d %02d.%02d.%04d %d %s %.2f\n", // ���������� %.2f ��� ������
                exchanges[i].exchange_id,
                exchanges[i].date.day,
                exchanges[i].date.month,
                exchanges[i].date.year,
                exchanges[i].manager_id,
                exchanges[i].currency,
                exchanges[i].price);
    }
    fclose(out);
    printf("����� � ID %d ������� ��������������.\n", exchange_id);
}

// �������� ������������ ����
bool ExchangeSystem::validate_date(const Date& date) {
    if (date.month < 1 || date.month > 12) return false; // �������� ������
    if (date.day < 1) return false; // �������� ���

    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31}; // ���������� ���� � ������ ������
    if (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0))
        days_in_month[1] = 29; // ���� ����������� ����

    return date.day <= days_in_month[date.month - 1]; // �������� ������������ ���
}

// �������� ������� �� �����
int ExchangeSystem::load_exchanges(const char* fname, Exchange exchanges[], int limit) {
    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� �����");
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
    return count; // ���������� ���������� ����������� �������
}

// �������� ���������� �� �����
int ExchangeSystem::load_managers(const char* fname, Manager managers[], int limit) {
    FILE* in = fopen(fname, "r");
    if (in == NULL) {
        perror("������ �������� �����");
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
    return count; // ���������� ���������� ����������� ����������
}

// ���������� ������ ���������
void ExchangeSystem::add_manager(Manager managers[], int* count) {
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

    // ���� ������� ��������� � ��������� �� ������� ����
    printf("������� ������� ���������: ");
    while (1) {
        scanf("%s", new_manager.manager_surname);
        if (strspn(new_manager.manager_surname, "0123456789") == 0) {
            break; // ������� ���������, ������� �� �����
        }
        printf("������: ������� �� ������ ��������� �����. ����������, ������� ������� �����: ");
    }

    // ���� ����� ��������� � ��������� �� ������� ����
    printf("������� ��� ���������: ");
    while (1) {
        scanf("%s", new_manager.manager_name);
        if (strspn(new_manager.manager_name, "0123456789") == 0) {
            break; // ��� ���������, ������� �� �����
        }
        printf("������: ��� �� ������ ��������� �����. ����������, ������� ��� �����: ");
    }

    // ���� �������� ��������� � ��������� �� ������� ����
    printf("������� �������� ���������: ");
    while (1) {
        scanf("%s", new_manager.manager_patronymic);
        if (strspn(new_manager.manager_patronymic, "0123456789") == 0) {
            break; // �������� ���������, ������� �� �����
        }
        printf("������: �������� �� ������ ��������� �����. ����������, ������� �������� �����: ");
    }

    managers[*count] = new_manager; // ���������� ������ ��������� � ������
    (*count)++; // ���������� �������� ����������
    printf("�������� ��������.\n\n");

    // ���������� ��������� � ����
    FILE* out = fopen("managers.txt", "a");
    if (out == NULL) {
        perror("������ �������� ����� ��� ������");
        return;
    }
    fprintf(out, "%d %s %s %s\n", new_manager.manager_id, new_manager.manager_surname, new_manager.manager_name, new_manager.manager_patronymic);
    fclose(out);
}

// �������� ���������
void ExchangeSystem::remove_manager(Manager managers[], int* count) {
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

    // ���������� ����� ����� ��������
    FILE* out = fopen("managers.txt", "w");
    if (out == NULL) {
        perror("������ �������� ����� ��� ������");
        return;
    }

    // ������ ���������� ���������� � ����
    for (int i = 0; i < *count; i++) {
        fprintf(out, "%d %s %s %s\n", managers[i].manager_id, managers[i].manager_surname, managers[i].manager_name, managers[i].manager_patronymic);
    }

    fclose(out);
}

// ������������ ������ txt
void ExchangeSystem::do_query(const Exchange exchanges[], int limit, const char* fname) {
    if (limit == 0) {
        printf("��� ������� ��� ��������� �������.\n");
        return;
    }

    int month_exchanges[N_MONTHS + 1] = {0}; // ������������� ������� ��� �������� ���������� �������
    double month_totals[N_MONTHS + 1] = {0.0};   // ������������� ������� ��� �������� ���� �������

    // �������� ������� ���
    int report_year = get_current_year(); // ������� ���������� ������� ���

    // ������� ���������� �� �������
    for (int i = 0; i < limit; i++) {
        if (exchanges[i].date.year == report_year) {
            int month = exchanges[i].date.month;
            month_exchanges[month]++;
            month_totals[month] += exchanges[i].price;
        }
    }

    FILE* out = fopen(fname, "w");
    if (out == NULL) {
        perror("������ �������� �����");
        return;
    }

    // ������������ ������
    fprintf(out, "����� �� �������\n");
    fprintf(out, "���� EURO: \n");
    fprintf(out, "���� USD: \n");

    // ������� ����
    char current_date[100];
    get_current_date(current_date);
    fprintf(out, "����: %s\n", current_date);

    fprintf(out, "-----------------------------------\n");
    fprintf(out, "�����/��� ����������\n");

    // ����� ���������� ������� �� �������
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_exchanges[i] != 0) {
            fprintf(out, "%02d.%d %d\n", i, report_year, month_exchanges[i]);
        }
    }

    // ����� ���� �� �������
    fprintf(out, "-----------------------------------\n");
    fprintf(out, "����� ���������� ����� � ������ �� ������� � %d ����:\n", report_year);
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "%02d.%d: %.2f\n", i, report_year, month_totals[i]);
        }
    }

    fprintf(out, "-----------------------------------\n");
    fprintf(out, "�������: _______________________\n");

    fclose(out);
}


// ������������ ������ html
void ExchangeSystem::do_query1(const Exchange exchanges[], int limit, const char* fname) {
    if (limit == 0) {
        printf("No exchanges to process.\n");
        return;
    }

    int month_exchanges[N_MONTHS + 1] = {0}; // ������������� ������� ��� �������� ����
    double month_totals[N_MONTHS + 1] = {0.0};   // ������������� ������� ��� ������������ ���� �������� ��������

    // ���������� ���, ��� �������� �� ������ ������� �����
    int report_year = get_current_year(); // ������� ���������� ������� ���

    // ������� ���������� �� �������
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

    // ������ BOM ��� ��������� UTF-8
    fprintf(out, "\xEF\xBB\xBF");

    // ������ HTML-���������
    fprintf(out, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n");
    fprintf(out, "<title>Exchange Report</title>\n</head>\n<body>\n");
    fprintf(out, "<h1>Exchange Report</h1>\n");

    // ������� ����
    char current_date[100];
    get_current_date1(current_date);
    fprintf(out, "<p>Date: %s</p>\n", current_date);

    fprintf(out, "<h2>Number of Exchanges by Month</h2>\n");
    fprintf(out, "<table border=\"1\">\n<tr><th>Month/Year</th><th>Count</th></tr>\n");

    // ����� ���������� ���� �� �������
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_exchanges[i] != 0) {
            fprintf(out, "<tr><td>%02d.%d</td><td>%d</td></tr>\n", i, report_year, month_exchanges[i]);
        }
    }
    fprintf(out, "</table>\n");

    fprintf(out, "<h2>Total Amount Exchanged in Rubles by Month in %d</h2>\n", report_year);
    fprintf(out, "<table border=\"1\">\n<tr><th>Month/Year</th><th>Amount</th></tr>\n");

    // ����� ����� ���� �� �������
    for (int i = 1; i <= N_MONTHS; i++) {
        if (month_totals[i] != 0) {
            fprintf(out, "<tr><td>%02d.%d</td><td>%.2f</td></tr>\n", i, report_year, month_totals[i]);
        }
    }
    fprintf(out, "</table>\n");

    fprintf(out, "<p>Signature: _______________________</p>\n");

    // ����� HTML-���������
    fprintf(out, "</body>\n</html>\n");

    fclose(out);
}


// ����� ������ �������
void ExchangeSystem::exchanges_print(const Exchange exchanges[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        exchange_to_s(s, exchanges[i]); // �������������� ������ � ������
        puts(s); // ����� ������
        puts("");
    }
}

// ����� ������ ����������
void ExchangeSystem::managers_print(const Manager managers[], int limit) {
    for (int i = 0; i < limit; i++) {
        char s[150] = "";
        manager_to_s(s, managers[i]); // �������������� ��������� � ������
        puts(s); // ����� ������
        puts("");
    }
}
