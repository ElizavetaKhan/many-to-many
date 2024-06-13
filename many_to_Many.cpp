#include "many_to_Many.h"

many_to_Many::many_to_Many() = default;

many_to_Many::~many_to_Many()
{
    for (int i = 0; i < 20; ++i) {
        // получаем по очереди каждого студента для удаления всех его связей
        NodeStudent* student = students::getStudentForDeleting(i);

        // если такой элемент есть вообще
        if (student)
        {
            NodeConnections* connectSt = student->ringStudent;

            while (connectSt && connectSt->is_connectionNext()) {
                Pointer* nexT = connectSt->student;

                // удаляем связь
                deleteConnect(connectSt->course,student);
                connectSt = nexT;
            }
        }
    }

    // очищаем массивы курсов и студентов
    students::destructor();
    courses::destructor();
}

void many_to_Many::addStudentToCourse(const char STUDENT[10], int COURSE)
{
    // получаем студента
    NodeStudent* student = students::getStudent(STUDENT);
    // получаем курс
    NodeCourses* course = courses::getCourse(COURSE);


     // если это не nullptr – то есть такие студент и курс есть в списке
    // И если такой связи ЕЩЕ НЕТ
    if (student && course && !findConnect(*student,*course)) {
        // сразу создаем новую связь
        NodeConnections* NEW;
        NEW = new NodeConnections(student, course);

        // если еще нет курса у студента – создаем и добавляем
        if (!student->ringStudent) {
            student->ringStudent = NEW;
            // если при этом курс еще пустой – добавляем и выходим
            if (!course->ringCourse) {
                course->ringCourse = NEW;
                return;

                // иначе запоминаем последнюю добавленную связь в кольце курса, и добавляем новую после нее
            } else {
                Pointer* tailCourse = course->ringCourse;

                // новая связь ссылается на предыдущую на этом курсе
                course->ringCourse = NEW;
                NEW->course = tailCourse;
            }
            return;
        }

        // иначе если курс пустой – на нем еще нет студентов
        else if (!course->ringCourse) {
            course->ringCourse = NEW;
            Pointer* tailStudent = student->ringStudent;

            // новая связь ссылается на предыдущую у этого студента
            student->ringStudent = NEW;
            NEW->student = tailStudent;
            return;
        }


        // ЕСЛИ И У КУРСА, И СТУДЕНТА ЭТО УЖЕ НЕ ПЕРВАЯ СВЯЗЬ – просто добавляем в ringlist и ссылаемся на последнюю добавленную
        Pointer* tailStudent; Pointer* tailCourse;
        NodeConnections first = student->ringStudent;
        // если один курс, то prev у него нет – будем стартовать от элемента типа NodeStudent(элемента массива)
        !first.course ? tailStudent = student : tailStudent = student->ringStudent;
        first = course->ringCourse;
        !first.student ? tailCourse = course : tailCourse = course->ringCourse;

        // новая связь ссылается на ту, которая уже есть для этого курса
        NEW->course = tailCourse;
        course->ringCourse = NEW;

        NEW->student = tailStudent;
        student->ringStudent = NEW;
    }
}

void many_to_Many::deleteStudentFromCourse(const char STUDENT[10], int COURSE)
{
    // получаем студента
    NodeStudent* student = students::getStudent(STUDENT);
    // получаем курс
    NodeCourses* course = courses::getCourse(COURSE);


    // если они не nullptr – то есть такие студент и курс есть в списке
    if (student && course) {
        // если связи такой нет – выходим
        if (!student->ringStudent || !course->ringCourse)
            return;

        Pointer* prevST;
        Pointer* prevCour;
        // проверяем первые элементы отдельно
        getCourseForStudent(*student->ringStudent) == course ? prevST = student : prevST = getPrevStudentInRing(student,course);
        getStudentForCourse(*course->ringCourse) == student ? prevCour = course : prevCour = getPrevCourseInRing(course,student);

        // вызов приватного метода для удаления связи
        deleteConnect(prevCour,prevST);
    }
}

void many_to_Many::deleteAllStudentsFromCourse(int COURSE)
{
    // получаем курс
    NodeCourses* course = courses::getCourse(COURSE);

    // если он не nullptr – то есть такой курс есть в списке
    if (course) {
        NodeConnections* st = course->ringCourse;
        // пока не удалили все кольцо
        while (st->student && course->ringCourse)
        {
            deleteConnect(*course, st->student);
            st = st->course;
        }
    }
}

void many_to_Many::deleteAllStudentCourses(const char STUDENT[10])
{
    // получаем студента
    NodeStudent* student = students::getStudent(STUDENT);


    // если он не nullptr – то есть такой студент есть в списке
    if (student) {
        // пока не удалили все кольцо
        while (student->ringStudent) {
            Pointer course = getCourseForStudent(student->ringStudent);
            Pointer prevCourse = getPrevStudentInRing(student, course);

            // вызов приватного метода для удаления связи
            deleteConnect(prevCourse,student);
        }
    }
}

bool many_to_Many::findConnect(NodeStudent* STUDENT, NodeCourses* COURSE)
{
    NodeConnections* start = STUDENT.ringStudent;
    Pointer* startPointer = STUDENT.ringStudent;

    // пока не прошли круг
    while (startPointer->is_connectionNext()) {
        if (startPointer->getNum() == COURSE)
            return true;

        startPointer = start->course;
    }
    return false;
}

Pointer* many_to_Many::getPrevCourseInRing(NodeCourses* course, NodeStudent* student)
{
    Pointer* prevCourse = course;
    Pointer* current = course->ringCourse;

    // пока не прошли круг
    while (current->is_connectionNext()) {
        auto* connect = dynamic_cast<NodeConnections *>(current);
        Pointer* studentRing = connect->student;

        if (getStudentForCourse(studentRing) == student)
            return prevCourse;

        prevCourse = current;
        current = connect->course;
    }

    return nullptr;
}

Pointer* many_to_Many::getPrevStudentInRing(NodeStudent* student, NodeCourses* course) {
    Pointer *prevCourse = student;
    Pointer *current = student->ringStudent;

    // пока не прошли круг
    while (current->is_connectionNext()) {
        auto *connect = dynamic_cast<NodeConnections *>(current);
        Pointer *courseRing = connect->course;

        if (getCourseForStudent(courseRing) == course)
            return prevCourse;

        prevCourse = current;
        current = connect->student;
    }

    return nullptr;
}

void many_to_Many::deleteConnect(Pointer* COURSE, Pointer* STUDENT)
{
    // запоминаем элемент, который надо удалить, если он не первый
    Pointer* cur = nullptr;

    // если удаление первой связи для курса
    if (!COURSE.is_connectionNext())
    {
        cur = COURSE.ringCourse;
        // и она единственная у курса
        if (cur->course == COURSE) {
            // зануляем само кольцо
            COURSE.ringCourse = nullptr;

            // И ПРИ ЭТОМ единственная у студента – зануляем кольцо студента
            NodeStudent* tempCur = STUDENT.ringStudent;
            if (tempCur->student == STUDENT) {
                STUDENT.ringStudent = nullptr;
                delete cur;
                return;
            }
        }

    // первая связь для студента
    } else if (!STUDENT.is_connectionNext()) {
        cur = STUDENT.ringStudent;

        // и единственная у студента
        if (cur->student == STUDENT) {
            // зануляем кольцо студента
            STUDENT.ringStudent = nullptr;
        }
    }

    if (!cur)
        cur = COURSE.student;

    // если до этого не занулили кольцо и нужно переопределить его
    // просто "вырезаем" связь из кольца
    if (STUDENT.ringStudent) {
        // находим следующего студента в кольце курса и присваиваем
        Pointer* nextST = cur->course;
        !STUDENT.is_connectionNext() ? STUDENT.redefenitionOfRingCour(nextST)
                                      : STUDENT.RedefenitionCourseInConnection(nextST);

    } if (COURSE.ringCourse) {
        // находим следующий курс в кольце студента и присваиваем
        Pointer* nextCOU = cur->student;
        !COURSE.is_connectionNext() ? COURSE.redefenitionOfRingSt(nextCOU)
                                     : COURSE.RedefenitionStudentInConnection(nextCOU);
    }
    // чистим память с удаленной связи
    delete cur;
}


void many_to_Many::studentsInCourse(int COURSE)
{
    // получаем курс
    NodeCourses* course = courses::getCourse(COURSE);


    // если он не nullptr – то есть такой курс есть в списке
    if (course) {
        std::cout << std::endl;
        Pointer* i = course->ringCourse;
        NodeConnections* cur = course->ringCourse;

        std::cout << course->num << "-> ";
        while (i && i->is_connectionNext()) {
            // получаем имя из виртуального метода СУПЕРкласса
            std::cout << getStudentForCourse(*cur)->getName() << ", ";
            i = cur->course;
        }
        std::cout << std::endl;
    }
}

void many_to_Many::studentCourses(const char STUDENT[10])
{
    // получаем студента
    NodeStudent* student = students::getStudent(STUDENT);


    // если он не nullptr – то есть такой студент есть в списке
    if (student)
    {
        std::cout << std::endl;
        Pointer* i = student->ringStudent;
        NodeConnections* cur = student->ringStudent;

        std::cout << student->name << "-> ";
        while (i && i->is_connectionNext()) {
            // получаем номер из виртуального метода суперкласса
            std::cout << getCourseForStudent(*cur)->getNum() << ", ";
            i = cur->student;
        }
        std::cout << std::endl;
    }
}

Pointer* many_to_Many::getCourseForStudent(Pointer* course)
{
    Pointer* POINTER = course;

    while (POINTER->is_connectionNext())
        POINTER = course->course;
    return POINTER;
}

Pointer* many_to_Many::getStudentForCourse(Pointer* student)
{
    Pointer* POINTER = student;

    while (student->is_connectionNext())
        POINTER = student->student;
    return POINTER;
}