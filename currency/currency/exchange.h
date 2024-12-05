// exchange.h
#ifndef EXCHANGE_H_INCLUDED
#define EXCHANGE_H_INCLUDED

#include "date.h"

// ��������� ��� ������������� ������
typedef struct _exchange {
    Date date;         // ���� ������
    int exchange_id;   // ID ������
    int manager_id;    // ID ���������, �������������� �� �����
    char currency[20]; // ������ ������
    int price;         // ���� ������
} Exchange;

#endif // EXCHANGE_H_INCLUDED
