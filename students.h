#ifndef INC_8_LAB_STUDENTS_H
#define INC_8_LAB_STUDENTS_H
#include <iostream>
#include "many_to_Many.h"
#include "NodeSTRUCTS.h"

// КЛАСС, КОТОРЫЙ ЗАПОЛНЯЕТ ИЗНАЧАЛЬНЫЙ МАССИВ И ХРАНИТ БАЗУ СТУДЕНТОВ

class students {
private:
    static inline NodeStudent* arrayStudents[20]{};
    static inline int amountOfArrayElements = 20;

private:
    static int hash_function(int hash);

    // считаем сумму кодов символов – HASH
    static int calcHash(const char name[10]);

public:
    students();

    static void destructor();

    void insert(const char name[10]);

    static NodeStudent* getStudent(const char name[10]);

    void print();

    // для того, чтобы получить первого студента и в деструкторе начать удалять связи
    static NodeStudent* getStudentForDeleting(int num);
};


#endif //INC_8_LAB_STUDENTS_H
