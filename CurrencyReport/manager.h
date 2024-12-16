// manager.h
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED

// Класс для представления менеджера
class Manager {
public:
    int manager_id;            // Уникальный идентификатор менеджера
    char manager_name[50];     // Имя менеджера
    char manager_surname[50];  // Фамилия менеджера
    char manager_patronymic[50]; // Отчество менеджера

    // Конструктор по умолчанию
    // Инициализирует manager_id нулем и устанавливает пустые строки для имени, фамилии и отчества
    Manager() : manager_id(0) {
        manager_name[0] = '\0';      // Инициализация имени пустой строкой
        manager_surname[0] = '\0';   // Инициализация фамилии пустой строкой
        manager_patronymic[0] = '\0'; // Инициализация отчества пустой строкой
    }
};

#endif // MANAGER_H_INCLUDED
