//manager.h
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

//Структура для хранения информации о менеджере
typedef struct _manager {
    int manager_id; //ID менеджера
    char manager_name[50]; //Имя менеджера
    char manager_surname[50]; //Фамилия менеджера
    char manager_patronymic[50]; //Отчество менеджера
} Manager;

#endif //MANAGER_H_INCLUDED
