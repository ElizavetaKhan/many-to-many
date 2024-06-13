#include "students.h"

students::students()
{
    for (int i = 0; i < amountOfArrayElements; ++i)
        arrayStudents[i] = nullptr;
}

void students::destructor()
{
    for (int i = 0; i < amountOfArrayElements; ++i)
        delete arrayStudents[i];
}

int students::calcHash(const char *name)
{
    int total = 0;

    for (int i = 0; name[i] != '\0'; ++i)
        total += name[i];
    return total;
}

void students::insert(const char *name)
{
    // высчитываем хэш, далее в хэш-функции ищем первый свободный элемент, чтобы вставить туда
    int hash = calcHash(name);

    int num = hash_function(hash);
    // запомнили элемент, с которого стартовали
    int start = num;

    // счетчик для повторного хэширования
    int i = 0;

    // пока не дошли до ранее не тронутого элемента
    while (arrayStudents[num]) {

        // если прошли полный круг и не нашли пустых элементов
        if (start == num && (i != 0))
            std::cout << "!! МАССИВ ПЕРЕПОЛНЕН !!";

        // если оно уже лежит там – ничего не делаем
        if (strcmp(name, arrayStudents[num]->name) == 0)
            return;

        ++i;
        num = hash_function(hash + i);
    }

    // если нашли пустой элемент – заполняем первый пустой
    if (!arrayStudents[num])
        arrayStudents[num] = new NodeStudent(name);
}

int students::hash_function(int hash)
{
    return (hash) % amountOfArrayElements;
}

NodeStudent *students::getStudent(const char *name)
{
    int hash = calcHash(name);
    int i = 1;

    // проверяем отдельно элемент array[hash]
    if (arrayStudents[hash % amountOfArrayElements] && strcmp(name,arrayStudents[hash % amountOfArrayElements]->name) == 0)
        return arrayStudents[hash % amountOfArrayElements];

    int num = (hash+i) % amountOfArrayElements;

    // пока не сделали круг или не встретили пустой элемент
    while (((hash % amountOfArrayElements) != num) && arrayStudents[num]) {
        // если нашли имя
        if (strcmp(name,arrayStudents[num]->name) == 0)
            return arrayStudents[num];
        ++i;
        num = (hash + i) % amountOfArrayElements;
    }

    // если не нашли такое имя
    return nullptr;
}

void students::print()
{
    std::cout << std::endl;
    for (int i = 0; i < amountOfArrayElements; ++i)
        if (arrayStudents[i])
            std::cout << arrayStudents[i]->name << ", ";

    std::cout << std::endl;
}

NodeStudent *students::getStudentForDeleting(int num)
{
    return arrayStudents[num];
}