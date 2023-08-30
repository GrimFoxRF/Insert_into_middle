//вставка элементов в очередь с мелкогранулярной блокировкой
#include <iostream>
#include <mutex>
#include <Windows.h>
#include <sstream>
#include "Functions.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    FineGrainedQueue queue;
    //заполняем очередь первыми 3 элементами
    queue.insertIntoMiddle(0, 0);
    queue.insertIntoMiddle(7, 1);
    queue.insertIntoMiddle(1, 2);
    queue.showQueue();//выводим очередь на экран

    int value = 0;
    int npos = 0;

    while (true) //бесконечный цикл
    {
        std::cout << "\nВведите значение и номер позиции для вставки:" << std::endl;
        std::string input;
        std::getline(std::cin, input);

        std::stringstream stream(input);
        if (!(stream >> value >> npos))//если некорректный ввод
        {
            std::cout << "\nОШИБКА: Некорректный ввод." << std::endl;
            continue;
        }
        queue.insertIntoMiddle(value, npos);//вставка значения в указанную позицию
        queue.showQueue();//выводим очередь на экран
    }
    
    return 0;
}