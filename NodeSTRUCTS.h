#ifndef INC_8_LAB_NODESTRUCTS_H
#define INC_8_LAB_NODESTRUCTS_H
#include "cstring"
#include "iostream"

struct NodeStudent;
struct NodeCourses;
struct NodeConnections;

struct Pointer {
    // можно ли дальше двигаться по регистрационным формам?
    virtual bool is_connectionNext() {};

    // виртуальные методы для получения имени и номера курса для NodeConnection
    virtual char* getName(){};
    virtual int getNum(){};
};

// СУПЕРКЛАСС, который может ссылаться на узел своего типа и на узел типа своего подкласса
struct NodeConnections: public Pointer {
    Pointer* student{};
    Pointer* course{};

    NodeConnections() {
        this->student = nullptr;
        this->course = nullptr;
    }

    NodeConnections(Pointer* student, Pointer* course)
    {
        this->student = student;
        this->course = course;
    }

    bool is_connectionNext() override {
        return this->course || this->student;
    }
};

struct NodeStudent: public Pointer {
    char* name{};
    NodeConnections* ringStudent{};

    explicit NodeStudent(const char *name)
    {
        this->name = new char[10];
        strcpy(this->name, name);
        this->ringStudent = nullptr;
    }

    // получить имя студента
    char * getName() override {
        return this->name;
    }
};

struct NodeCourses: public Pointer {
    int num{};
    NodeConnections *ringCourse{};

    explicit NodeCourses(int num) {
        this->num = num;
    }

    // получить номер курса
    int getNum() override {
        return this->num;
    }
};

#endif //INC_8_LAB_NODESTRUCTS_H
