// 4_sem_Lab1.cpp: определяет точку входа для приложения.
//

#include "4_sem_Lab1.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    List<int> mySet(1);
    List<int> twoSet(2, nullptr, &mySet);
    List<int> fourSet(4);

    List<int> threeSet(3, &fourSet, &twoSet);

    List<int> fiveSet(threeSet);

    std::cout << "threeSet: ";
    threeSet.print();
    std::cout << "\n";
    std::cout << "fiveSet: ";
    fiveSet.print();
    std::cout << "\n";
    std::cout << "Вставляю доп значения в fiveSet\n";
    fiveSet.insert(10);
    fiveSet.insert(15);
    fiveSet.insert(12);
    fiveSet.insert(0);
    std::cout << "fiveSet: ";
    fiveSet.print();
    std::cout << "\n";
    std::cout << "копирую конструктором копирования fiveSet\n";
    List<int> sixSet(fiveSet);
    std::cout << "fiveSet: ";
    fiveSet.print();
    std::cout << "sixSet: ";
    sixSet.print();
    return 0;
}

