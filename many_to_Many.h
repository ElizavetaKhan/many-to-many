#ifndef INC_8_LAB_MANY_TO_MANY_H
#define INC_8_LAB_MANY_TO_MANY_H
#include "students.h"
#include "courses.h"
#include <iostream>

// КЛАСС, КОТОРЫЙ ПРОКЛАДЫВАЕТ, УДАЛЯЕТ И НАХОДИТ СВЯЗИ СТУДЕНТОВ И КУРСОВ

class many_to_Many {
private:
    // получить предыдущий курс в кольце студента ДЛЯ УДАЛЕНИЯ (первый элемент проверяем до вхождения в метод)
    Pointer* getPrevCourseInRing(NodeCourses* course, NodeStudent* student);

    // получить предыдущего студента в кольце курса ДЛЯ УДАЛЕНИЯ (первый элемент проверяем до вхождения в метод)
    Pointer* getPrevStudentInRing(NodeStudent*, NodeCourses* course);

    // удаление конкретной связи, на вход приходит prev для курса и prev для студента (или же сам узел, если нужно удалить первую связь)
    void deleteConnect(Pointer* COURSE, Pointer* STUDENT);

    // ищем среди указателей элемент, содержащий именно информацию о курсе студента (номер)
    Pointer* getCourseForStudent(Pointer* course);

    // ищем среди указателей элемент, содержащий именно информацию о студенте на курсе (имя)
    Pointer* getStudentForCourse(Pointer* student);

    // для вставки проверяем наличие связи (предыдущий не нужен, так как вставляем сразу в начало кольца, после "головы")
    bool findConnect(NodeStudent* STUDENT, NodeCourses* COURSE);

public:
    many_to_Many();

    // деструктор
    ~many_to_Many();

    // конструктор сразу создает связь
    // добавление студента на курс
    void addStudentToCourse(const char STUDENT[10], int COURSE);

    // удаляет связь студент - курс
    void deleteStudentFromCourse(const char STUDENT[10], int COURSE);

    // удаляет всех студентов с курса
    void deleteAllStudentsFromCourse(int COURSE);

    // удаляет все курсы у студента
    void deleteAllStudentCourses(const char STUDENT[10]);

    // выводит всех студентов на курсе
    // Список студентов, посещающих конкретный курс
    void studentsInCourse(int COURSE);

    // выводит все курсы у студента
    // Список курсов, посещаемых конкретным студентом
    void studentCourses(const char STUDENT[10]);
};


#endif //INC_8_LAB_MANY_TO_MANY_H
