// sale.h
#ifndef SALE_H_INCLUDED
#define SALE_H_INCLUDED

#include "date.h"

//��������� ��� ������������� �������
typedef struct _sale {
    Date date;         //���� �������
    int sale_id;       //ID �������
    int manager_id;    //ID ���������, �������������� �� �������
    char currency[20]; //������ ����������, ������� ��� ������
    int price;         //���� �������
} Sale;

#endif //SALE_H_INCLUDED
