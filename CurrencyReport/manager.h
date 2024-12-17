// manager.h
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

// ����� ��� ������������� ���������
class Manager {
public:
    int manager_id;            // ���������� ������������� ���������
    char manager_name[50];     // ��� ���������
    char manager_surname[50];  // ������� ���������
    char manager_patronymic[50]; // �������� ���������

    // ����������� �� ���������
    // �������������� manager_id ����� � ������������� ������ ������ ��� �����, ������� � ��������
    Manager() : manager_id(0) {
        manager_name[0] = '\0';      // ������������� ����� ������ �������
        manager_surname[0] = '\0';   // ������������� ������� ������ �������
        manager_patronymic[0] = '\0'; // ������������� �������� ������ �������
    }
};

#endif // MANAGER_H_INCLUDED
