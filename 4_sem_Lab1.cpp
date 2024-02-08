// 4_sem_Lab1.cpp: определяет точку входа для приложения.
//

#include "4_sem_Lab1.h"
#include <ctime>
#include <random>


using namespace std;

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}


int main()
{
    setlocale(LC_ALL, "ru");
    random_device rd;   
    mt19937 gen(rd());  
    uniform_int_distribution<> dist(0, 150000);


    std::cout << "Измеряем время для дерева поиска...\n";
    int size[] = {1000, 10000, 100000};
    double medium_insert[3];
    double medium_contains[3];
    double medium_add[3];
    double medium_delete[3];
    for (size_t s = 0; s < 3; ++s)
    {
        std::cout << "\n>>> Выполняем процедуры для дерева размером " << size[s] <<"\n\n";
        const int attempt = 100;
        const int attempt_contains_add_del = 1000;
        size_t time_insert[attempt];
        size_t time_contains[attempt];
        size_t time_add[attempt];
        size_t time_delete[attempt];


        std::cout << "Заполняем " << size[s] << " псевдо случайными числами...\n";
        size_t sum_insert = 0;
        for (size_t j = 0; j < attempt; ++j)
        {
            int start_insert = std::clock();
            My_set<int> _set(static_cast<int>(lcg()));
            for (size_t i = 1; i < size[s]; ++i) {
                _set.insert(static_cast<int>(lcg()));
            }
            //std::cout << j;
            int end_insert = std::clock();
            sum_insert += (end_insert - start_insert) / CLOCKS_PER_SEC;
        }
        medium_insert[s] = (double)sum_insert / attempt;
        std::cout << "Закончили заполнять. Сред. время - " << medium_insert[s] << "\n\n\n";


        My_set<int> _set(static_cast<int>(lcg()));
        for (size_t i = 1; i < size[s]; ++i) {
            _set.insert(static_cast<int>(lcg()));
        }
        
        std::cout << "Проверяем наличие значений...\n";
        size_t sum_contains = 0;
        for (size_t i = 0; i < attempt_contains_add_del; i++)
        {
            int start_contains = std::clock();

            bool res = _set.contains(dist(gen));

            int end_contains = std::clock();
            sum_contains += (end_contains - start_contains) / CLOCKS_PER_SEC;
        }
        medium_contains[s] = sum_contains / attempt_contains_add_del;
        std::cout << "Закончили проверять. Сред. время - " << medium_contains[s] << "\n\n\n";


        std::cout << "Добавляем значения...\n";
        size_t sum_add = 0;
        for (size_t i = 0; i < attempt_contains_add_del; i++)
        {
            int start_add = std::clock();

            _set.insert(dist(gen));

            int end_add = std::clock();
            sum_add += (end_add - start_add) / CLOCKS_PER_SEC;
        }
        medium_add[s] = sum_add / attempt_contains_add_del;
        std::cout << "Закончили добавлять. Сред. время - " << medium_add[s] << "\n\n\n";

        std::cout << "Удаляем значения...\n";
        size_t sum_delete = 0;
        for (size_t i = 0; i < attempt_contains_add_del; i++)
        {
            if (i == 100) {
                int b = 0;
            }
            if (i == 200) {
                int b = 0;
            }
            if (i == 300) {
                int b = 0;
            }
            if (i == 400) {
                int b = 0;
            }
            if (i == 500) {
                int b = 0;
            }
            int start_delete = std::clock();

            bool res = _set.erase(dist(gen));
            int end_delete = std::clock();
            sum_delete += (end_delete - start_delete) / CLOCKS_PER_SEC;
        }
        medium_delete[s] = sum_delete / attempt_contains_add_del;
        std::cout << "Закончили удалять. Время - " << medium_delete[s] << "\n\n\n";
    }
    
    return 0;
}

