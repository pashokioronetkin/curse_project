// exchange.h
#ifndef EXCHANGE_H_INCLUDED
#define EXCHANGE_H_INCLUDED

#include "date.h" // ��������� ������������� ����� � ������������ ������ Date

// ����� ��� ������������� ������ �����
class Exchange {
public:
    Date date;         // ���� ������
    int exchange_id;   // ���������� ������������� ������
    int manager_id;    // ������������� ���������, ������� ������ �����
    char currency[20]; // ������ ������ (��������, USD ��� EURO)
    double price;      // ����� ������

    // ����������� �� ���������
    // �������������� ���� exchange_id, manager_id � price ������
    // ������������� ������ ������ ��� currency
    Exchange() : exchange_id(0), manager_id(0), price(0.0) {
        currency[0] = '\0'; // ������������� ������ ������ ������ ���������
    }
};

#endif // EXCHANGE_H_INCLUDED
