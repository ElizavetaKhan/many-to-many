#include "courses.h"

courses::courses()
{
    for (int i = 0; i < amountOfArrayElements; ++i)
        arrayCourses[i] = nullptr;
}

void courses::destructor()
{
    for (int i = 0; i < amountOfArrayElements; ++i)
        delete arrayCourses[i];
}

void courses::insert(int course)
{
    int num = hash_function(course);
    // запомнили элемент, с которого стартовали
    int start = num;

    // счетчик для повторного хэширования
    int i = 0;

    // пока не дошли до ранее не тронутого элемента
    while (arrayCourses[num]) {

        // если прошли полный круг и не нашли пустых элементов
        if (start == num && (i != 0))
            std::cout << "!! МАССИВ ПЕРЕПОЛНЕН !!";

        // если он уже лежит там
        if (course == arrayCourses[num]->num)
            return;

        ++i;
        num = hash_function(course + i);
    }

    // если нашли пустой элемент – заполняем первый пустой
    if (!arrayCourses[num])
        arrayCourses[num] = new NodeCourses(course);
}

int courses::hash_function(int hash)
{
    return hash % amountOfArrayElements;
}

NodeCourses *courses::getCourse(int course)
{
    // номер элемента массива, где изначально должен находиться name
    int total = course % amountOfArrayElements;

    // если имя уже есть и находится в total
    if (arrayCourses[total] && course == arrayCourses[total]->num)
        return arrayCourses[total];

    // пока не встретим ранее не заполненный элемент
    // или же пока не сделаем полный круг
    int count = 1;
    int j = (total + count) % amountOfArrayElements;

    while (arrayCourses[j] && (j != total))
    {
        // если уже есть такое имя – возвращаем его
        if (course == arrayCourses[j]->num)
            return arrayCourses[j];

        ++count;
        j = (total + count) % amountOfArrayElements;
    }

    // если не нашли
    return nullptr;
}

void courses::print()
{
    std::cout << std::endl;
    for (int i = 0; i < amountOfArrayElements; ++i)
        if (arrayCourses[i])
            std::cout << arrayCourses[i]->num << ", ";

    std::cout << std::endl;
}