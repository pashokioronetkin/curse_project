//manager.h
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

//��������� ��� �������� ���������� � ���������
typedef struct _manager {
    int manager_id; //ID ���������
    char manager_name[50]; //��� ���������
    char manager_surname[50]; //������� ���������
    char manager_patronymic[50]; //�������� ���������
} Manager;

#endif //MANAGER_H_INCLUDED
