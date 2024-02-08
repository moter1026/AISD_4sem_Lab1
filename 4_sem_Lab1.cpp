// 4_sem_Lab1.cpp: определяет точку входа для приложения.
//

#include "4_sem_Lab1.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    Node<int> mySet(1);
    Node<int> twoSet(2, nullptr, &mySet);
    Node<int> fourSet(4);

    Node<int> threeSet(3, &fourSet, &twoSet);

    Node<int> fiveSet(threeSet);

    My_set<int> set_one(threeSet);
    My_set<int> set_two(fiveSet);

    std::cout << "set_one: ";
    set_one.print();
    std::cout << "\n";
    std::cout << "set_two: ";
    set_two.print();
    std::cout << "\n";
    std::cout << "Вставляю доп значения в set_two\n";
    set_two.insert(10);
    set_two.insert(15);
    set_two.insert(12);
    set_two.insert(0);
    std::cout << "set_two: ";
    set_two.print();
    std::cout << "\n";
    std::cout << "копирую конструктором копирования set_two\n";
    My_set<int> set_three(set_two);
    std::cout << "set_two: ";
    set_two.print();
    std::cout << "set_three: ";
    set_three.print();
    return 0;
}

