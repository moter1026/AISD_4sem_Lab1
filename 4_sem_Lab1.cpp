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

    threeSet.print();
    fiveSet.print();
    return 0;
}

