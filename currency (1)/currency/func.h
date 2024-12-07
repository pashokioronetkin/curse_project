// func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define N_MONTHS 12

#include "exchange.h"
#include "manager.h"

// ��������� �������
void get_current_date(char *date_str); // ��������� ������� ����
void exchange_to_s(char s[100], Exchange exchange); // �������������� ������ � ������
void manager_to_s(char s[150], Manager manager); // �������������� ��������� � ������
void show_menu(); // �������� ����
void save_new_exchange(char *fname); // ��������� ����� �����
int load_managers(char *fname, Manager managers[], int limit); // ��������� ����������
int load_exchanges(char *fname, Exchange exchanges[], int limit); // ��������� ������
void exchanges_print(Exchange exchanges[], int limit); // ������ ������ �������
void managers_print(Manager managers[], int limit); // ������ ������ ����������
void do_query1(Exchange exchanges[], int limit, const char *fname); // ���������� ������� �� �������
void edit_exchange(char *fname); // ������������� �����
void add_manager(Manager managers[], int *count); // �������� ���������
void remove_manager(Manager managers[], int *count); // ������� ���������
void manager_login(Manager managers[], int man_count, Exchange exchanges[], int *exchange_count); // ���� ��� ���������
void admin_login(Manager managers[], int *man_count); // ���� ��� ��������������
void admin_menu(Manager managers[], int *man_count); // ���� ��� ��������������
void manager_menu(Manager managers[], int man_count, Exchange exchanges[], int *exchange_count); // ���� ��� ���������
int check_exchange_id_exists(char *fname, int exchange_id);

#endif // FUNC_H_INCLUDED
