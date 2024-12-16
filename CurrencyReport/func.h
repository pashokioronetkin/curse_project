// func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define N_MONTHS 12 // ��������� ��� ���������� ������� � ����

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "exchange.h" // ��������� ������������� ����� � ������������ ������ Exchange
#include "manager.h"  // ��������� ������������� ����� � ������������ ������ Manager

// ����� ��� ���������� �������� �������
class ExchangeSystem {
public:
    static const int AR_MAN_LEN = 100;    // ������������ ���������� ����������
    static const int AR_EXCHANGE_LEN = 1000; // ������������ ���������� �������
    static const char* month_names[12];   // ����������� ������ � ���������� �������
    static const char* month_names1[12];   // ����������� ������ � ���������� �������

    // ��������������� ������
    static void get_current_date(char* date_str); // ��������� ������� ���� � ��������� �������
    static void get_current_date1(char* date_str); // ��������� ������� ���� � ��������� �������
    static void exchange_to_s(char s[100], const Exchange& exchange); // �������������� ������ � ������
    static void manager_to_s(char s[150], const Manager& manager); // �������������� ��������� � ������
    static void show_menu(); // ����������� ��������� ����
    static int get_current_year(); // ��������� �������� ����


    // �������� � �������
    static void save_new_exchange(const char* fname, int current_manager_id); // ���������� ������ ������ � ����
    static int load_managers(const char* fname, Manager managers[], int limit); // �������� ���������� �� �����
    static int load_exchanges(const char* fname, Exchange exchanges[], int limit); // �������� ������� �� �����

    // ����� ����������
    static void exchanges_print(const Exchange exchanges[], int limit); // ����� ������ �������
    static void managers_print(const Manager managers[], int limit); // ����� ������ ����������

    // ������� � ������
    static void do_query(const Exchange exchanges[], int limit, const char* fname); // ������������ ������ �� ������� � txt
    static void do_query1(const Exchange exchanges[], int limit, const char* fname); // ������������ ������ �� ������� � html

    // �������� ��������������
    static void edit_exchange(const char* fname, int current_manager_id); // �������������� ������
    static void add_manager(Manager managers[], int* count); // ���������� ������ ���������
    static void remove_manager(Manager managers[], int* count); // �������� ���������

    // ������� ����� � ����
    static void manager_login(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count); // ���� ���������
    static void admin_login(Manager managers[], int* man_count); // ���� ��������������
    static void admin_menu(Manager managers[], int* man_count); // ���� ��������������
    static void manager_menu(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count, int current_manager_id); // ���� ���������

    // ��������
    static bool check_exchange_id_exists(const char* fname, int exchange_id); // �������� ������������� ID ������
    static bool validate_date(const Date& date); // �������� ������������ ����
};

#endif // FUNC_H_INCLUDED
