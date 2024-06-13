#ifndef INC_8_LAB_COURSES_H
#define INC_8_LAB_COURSES_H
#include "NodeSTRUCTS.h"
#include <iostream>
#include "many_to_Many.h"

// КЛАСС, КОТОРЫЙ ЗАПОЛНЯЕТ ИЗНАЧАЛЬНЫЙ МАССИВ И ХРАНИТ БАЗУ ИМЕЮЩИХСЯ КУРСОВ

class courses {
private:
    static inline NodeCourses* arrayCourses[20]{};
    static inline int amountOfArrayElements = 20;

private:
    int hash_function(int num);

public:
    courses();

    static void destructor();

    void insert(int course);

    static NodeCourses* getCourse(int course);

    void print();
};


#endif //INC_8_LAB_COURSES_H
