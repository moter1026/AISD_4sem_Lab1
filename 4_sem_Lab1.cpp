// 4_sem_Lab1.cpp: определяет точку входа для приложения.
//

#include "4_sem_Lab1.h"

using namespace std;

int main()
{
    Set_analog<int> mySet(1);
    Set_analog<int> twoSet(2, nullptr, &mySet);
    Set_analog<int> fourSet(4);

    Set_analog<int> threeSet(3, &fourSet, &twoSet);

    threeSet.print();
    return 0;
}

