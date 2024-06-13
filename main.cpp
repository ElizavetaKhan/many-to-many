#include <iostream>
#include <fstream>
#include "courses.h"
#include "students.h"


namespace lab_8
{
    static courses COURSES;
    static students STUDENTS;
    static many_to_Many CONNECT;
}
using namespace lab_8;


void fillStudentsFromFile(std::ifstream& in)
{
    char str[10];
    while (in >> str)
        STUDENTS.insert(str);
}

void fillCoursesFromFile(std::ifstream& in)
{
    int num;
    while (in >> num)
        COURSES.insert(num);
}

int main() {
    std::ifstream in1("students.txt");
    std::ifstream in2("courses.txt");

    fillStudentsFromFile(in1);
    fillCoursesFromFile(in2);

    STUDENTS.print();
    COURSES.print();

    // добавляем
    CONNECT.addStudentToCourse("Mia",4);
    CONNECT.addStudentToCourse("Vanya",12);
    CONNECT.addStudentToCourse("Alex",9);
    CONNECT.addStudentToCourse("Alex",2);
    CONNECT.addStudentToCourse("David",9);
    CONNECT.addStudentToCourse("David",12);
    CONNECT.addStudentToCourse("David",4);
    CONNECT.addStudentToCourse("Ari",12);
    CONNECT.addStudentToCourse("Maya",12);
    CONNECT.addStudentToCourse("Maya",4);

    // получаем всех с 12 курса
    CONNECT.studentsInCourse(12);

    // удалим одного студента и проверим людей на курсе теперь
    CONNECT.studentCourses("David");
    CONNECT.deleteStudentFromCourse("David",12);
    CONNECT.studentCourses("David");
    CONNECT.studentsInCourse(12);

    // удалим курсы у студента
    CONNECT.studentCourses("Mia");
    CONNECT.studentsInCourse(4);

    //CONNECT.deleteAllStudentCourses("David");
    //CONNECT.deleteAllStudentsFromCourse(12);
    //CONNECT.studentCourses("David");

    CONNECT.deleteAllStudentCourses("Mia");
    CONNECT.studentCourses("Mia");

    return 0;
}
