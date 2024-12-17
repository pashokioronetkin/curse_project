// date.h
#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

// ����� ��� ������������� ����
class Date {
public:
    int year;  // ���
    int month; // �����
    int day;   // ����

    // ����������� � ����������� �� ���������
    // �������������� ���� 1 ������ 2024 ����, ���� �� ������� ������ ��������
    Date(int d = 1, int m = 1, int y = 2024) : year(y), month(m), day(d) {}
};

#endif // DATE_H_INCLUDED
