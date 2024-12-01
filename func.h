//func.h
#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#define N_MONTHS 12

#include "sale.h"
#include "manager.h"

//��������� �������
void get_current_date(char *date_str); //��������� ������� ����
void sale_to_s(char s[100], Sale sale); //�������������� ������� � ������
void manager_to_s(char s[150], Manager manager); //�������������� ��������� � ������
void show_menu(); //�������� ����
void save_new_sale(char *fname); //��������� ����� �������
int load_managers(char *fname, Manager managers[], int limit); //��������� ����������
int load_sales(char *fname, Sale sales[], int limit); //��������� �������
void sales_print(Sale sales[], int limit); //������ ������ ������
void managers_print(Manager managers[], int limit); //������ ������ ����������
void do_query1(Sale sales[], int limit, const char *fname); //���������� ������� �� ��������

#endif //FUNC_H_INCLUDED
