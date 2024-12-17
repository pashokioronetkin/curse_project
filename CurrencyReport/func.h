// func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#define N_MONTHS 12 // ��������� ��� ���������� ������� � ����
#define AR_MAN_LEN 100    // ������������ ���������� ����������
#define AR_EXCHANGE_LEN 1000 // ������������ ���������� �������

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "exchange.h" // ��������� ������������� ����� � ������������ ������ Exchange
#include "manager.h"  // ��������� ������������� ����� � ������������ ������ Manager

// ���������� �������
void get_current_date(char* date_str); // ��������� ������� ���� � ��������� �������
void exchange_to_s(char s[100], const Exchange& exchange); // �������������� ������ � ������
void manager_to_s(char s[150], const Manager& manager); // �������������� ��������� � ������
void show_menu(); // ����������� ��������� ����
int get_current_year(); // ��������� �������� ����

// �������� � �������
void save_new_exchange(const char* fname, int current_manager_id); // ���������� ������ ������ � ����
int load_managers(const char* fname, Manager managers[], int limit); // �������� ���������� �� �����
int load_exchanges(const char* fname, Exchange exchanges[], int limit); // �������� ������� �� �����

// ����� ����������
void exchanges_print(const Exchange exchanges[], int limit); // ����� ������ �������
void managers_print(const Manager managers[], int limit); // ����� ������ ����������

// ������� � ������
void do_query(const Exchange exchanges[], int limit, const char* fname); // ������������ ������ �� ������� � txt
void do_query1(const Exchange exchanges[], int limit, const char* fname); // ������������ ������ �� ������� � html

// �������� ��������������
void edit_exchange(const char* fname, int current_manager_id); // �������������� ������
void add_manager(Manager managers[], int* count); // ���������� ������ ���������
void remove_manager(Manager managers[], int* count); // �������� ���������

// ������� ����� � ����
void manager_login(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count); // ���� ���������
void admin_login(Manager managers[], int* man_count); // ���� ��������������
void admin_menu(Manager managers[], int* man_count); // ���� ��������������
void manager_menu(Manager managers[], int man_count, Exchange exchanges[], int* exchange_count, int current_manager_id); // ���� ���������

// ��������
bool check_exchange_id_exists(const char* fname, int exchange_id); // �������� ������������� ID ������
bool validate_date(const Date& date); // �������� ������������ ����

#endif // FUNC_H_INCLUDED
