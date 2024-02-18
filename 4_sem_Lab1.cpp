// 4_sem_Lab1.cpp: определяет точку входа для приложения.
//

#include "4_sem_Lab1.h"
#include <ctime>
#include <random>
#include <algorithm>
#include <complex>
#include <string>

#define ATTEMPT 100
#define ATTEMPT_CONTAINS_ADD_DEL 1000
#define COUNT_SIZE 3

using namespace std;

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

std::string generateRandomText(int length) {
    // Создаем генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    // Определяем символы, которые могут использоваться в случайной строке
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Создаем распределение для выбора случайных символов
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    // Генерируем случайную строку
    std::string randomText;
    for (int i = 0; i < length; ++i) {
        randomText += characters[distribution(gen)];
    }

    return randomText;
}


int main()
{
    setlocale(LC_ALL, "ru");
    {
        random_device rd;
        mt19937 gen(rd());  
        uniform_int_distribution<> dist(0, 300);
    
        std::vector<int> _vector;
        _vector.push_back(dist(gen));
        for (size_t i = 1; i < 500; ++i) {
            _vector.push_back(dist(gen));
        }

        std::vector<int> repeat = repeat_els(&_vector);
        bool do_sort;
        std::cout << "Отсортировать вектор из повторяющихся эл-тов?\nДа - любое число, Нет - 0\n";
        std::cin >> do_sort;
        if (do_sort)    std::sort(repeat.begin(), repeat.end());
        for (size_t i = 0; i < repeat.size(); i++)
        {
            std::cout << repeat[i] << " ";
        }
        std::cout << "\n\n";
    }

    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 150000);

        std::cout << "Измеряем время для дерева поиска...\n";
        int size[] = { 1000, 10000, 100000 };
        double* set_medium_insert = new double[COUNT_SIZE];
        double* set_medium_contains = new double[COUNT_SIZE];
        double* set_medium_add = new double[COUNT_SIZE];
        double* set_medium_delete = new double[COUNT_SIZE];

        double* vector_medium_insert = new double[COUNT_SIZE];
        double* vector_medium_contains = new double[COUNT_SIZE];
        double* vector_medium_add = new double[COUNT_SIZE];
        double* vector_medium_delete = new double[COUNT_SIZE];


        for (size_t s = 0; s < COUNT_SIZE; ++s)
        {
            std::cout << "\n>>> Выполняем процедуры для дерева размером " << size[s] << "\n\n";

            std::cout << "Заполняем " << size[s] << " псевдо случайными числами...\n";
            size_t sum_insert = 0;
            for (size_t j = 0; j < ATTEMPT; ++j)
            {
                int start_insert = std::clock();
                My_set<int> _set(static_cast<int>(lcg()));
                for (size_t i = 1; i < size[s]; ++i) {
                    _set.insert(static_cast<int>(lcg()));
                }
                //std::cout << j;
                int end_insert = std::clock();
                sum_insert += (end_insert - start_insert);
            }
            set_medium_insert[s] = (double)sum_insert / ATTEMPT;
            std::cout << "Закончили заполнять. Сред. время - " << set_medium_insert[s] << "\n\n\n";


            My_set<int> _set(static_cast<int>(lcg()));
            for (size_t i = 1; i < size[s]; ++i) {
                _set.insert(static_cast<int>(lcg()));
            }

            std::cout << "Проверяем наличие значений...\n";
            size_t sum_contains = 0;
            for (size_t i = 0; i < ATTEMPT_CONTAINS_ADD_DEL; i++)
            {
                int start_contains = std::clock();

                bool res = _set.contains(dist(gen));
                std::cout << res << " ";

                int end_contains = std::clock();
                sum_contains += (end_contains - start_contains);
            }
            set_medium_contains[s] = (double)sum_contains / ATTEMPT_CONTAINS_ADD_DEL;
            std::cout << "Закончили проверять. Сред. время - " << set_medium_contains[s] << "\n\n\n";


            std::cout << "Добавляем значения...\n";
            size_t sum_add = 0;
            for (size_t i = 0; i < ATTEMPT_CONTAINS_ADD_DEL; i++)
            {
                int start_add = std::clock();

                _set.insert(dist(gen));

int end_add = std::clock();
sum_add += (end_add - start_add);
            }
            set_medium_add[s] = (double)sum_add / ATTEMPT_CONTAINS_ADD_DEL;
            std::cout << "Закончили добавлять. Сред. время - " << set_medium_add[s] << "\n\n\n";

            std::cout << "Удаляем значения...\n";
            size_t sum_delete = 0;
            for (size_t i = 0; i < ATTEMPT_CONTAINS_ADD_DEL; i++)
            {
                int start_delete = std::clock();

                bool res = _set.erase(dist(gen));
                std::cout << res << " ";
                int end_delete = std::clock();
                sum_delete += (end_delete - start_delete);
            }
            set_medium_delete[s] = (double)sum_delete / ATTEMPT_CONTAINS_ADD_DEL;
            std::cout << "Закончили удалять. Время - " << set_medium_delete[s] << "\n\n\n";
        }





        for (size_t s = 0; s < COUNT_SIZE; ++s)
        {
            std::cout << "\n>>> Выполняем процедуры для VECTOR размером " << size[s] << "\n\n";

            std::cout << "Заполняем в случайном порядке" << size[s] << " псевдо случайными числами...\n";
            size_t sum_insert = 0;
            for (size_t j = 0; j < ATTEMPT; ++j)
            {
                int start_insert = std::clock();
                std::vector<int> _vector(static_cast<int>(lcg()));
                for (size_t i = 1; i < size[s]; ++i) {
                    int val = static_cast<int>(lcg());
                    _vector.push_back(val);
                }
                //std::cout << j;
                int end_insert = std::clock();
                sum_insert += (end_insert - start_insert);
            }
            vector_medium_insert[s] = (double)sum_insert / ATTEMPT;
            std::cout << "Закончили заполнять. Сред. время - " << vector_medium_insert[s] << "\n\n\n";


            std::vector<int> _vector(static_cast<int>(lcg()));      // Здесь создаём вектор, который дальше будем проверять
            for (size_t i = 1; i < size[s]; ++i) {
                _vector.push_back(static_cast<int>(lcg()));
            }

            std::cout << "Проверяем наличие значений...\n";
            size_t sum_contains = 0;
            for (size_t i = 0; i < ATTEMPT_CONTAINS_ADD_DEL; i++)
            {
                int start_contains = std::clock();

                bool res = std::find(_vector.begin(), _vector.end(), dist(gen)) != _vector.end();
                std::cout << res << " ";

                int end_contains = std::clock();
                sum_contains += (end_contains - start_contains);
            }
            vector_medium_contains[s] = (double)sum_contains / ATTEMPT_CONTAINS_ADD_DEL;
            std::cout << "Закончили проверять. Сред. время - " << vector_medium_contains[s] << "\n\n\n";


            std::cout << "Добавляем значения...\n";
            size_t sum_add = 0;
            for (size_t i = 0; i < ATTEMPT_CONTAINS_ADD_DEL; i++)
            {
                int start_add = std::clock();

                _vector.push_back(dist(gen));

                int end_add = std::clock();
                sum_add += (end_add - start_add);
            }
            vector_medium_add[s] = (double)sum_add / ATTEMPT_CONTAINS_ADD_DEL;
            std::cout << "Закончили добавлять. Сред. время - " << vector_medium_add[s] << "\n\n\n";

            std::cout << "Удаляем значения...\n";
            size_t sum_delete = 0;
            for (size_t i = 0; i < ATTEMPT_CONTAINS_ADD_DEL; i++)
            {
                int start_delete = std::clock();

                auto res = std::find(_vector.begin(), _vector.end(), dist(gen));
                if (res == _vector.end()) { continue; }
                _vector.erase(res);

                int end_delete = std::clock();
                sum_delete += (end_delete - start_delete);
            }
            vector_medium_delete[s] = (double)sum_delete / ATTEMPT_CONTAINS_ADD_DEL;
            std::cout << "Закончили удалять. Время - " << vector_medium_delete[s] << "\n\n\n";
        }



        delete set_medium_insert;
        delete set_medium_contains;
        delete set_medium_add;
        delete set_medium_delete;

        delete vector_medium_insert;
        delete vector_medium_contains;
        delete vector_medium_add;
        delete vector_medium_delete;
    }

    std::cout << "\n\n";
    std::cout << "\n\n";
    
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 1000);

        std::complex<float>* cpl_float = new std::complex<float>(6.5, 2.5);
        My_set<std::complex<float>>* _set = new My_set<std::complex<float>>(*cpl_float);

        std::cout << _set->get_element()->get_key() << "\n";

        for (size_t i = 0; i < 1100; i++)
        {
            std::complex<float> cpl((float)dist(gen) / 100, (float)dist(gen) / 100);
            _set->insert(cpl);
        }
        std::complex<float> cpl((float)1.93, (float)0.6);
        _set->insert(cpl);

        (_set->contains(cpl) == 0) ? std::cout << "false" << "\n" : std::cout << "true" << "\n";
        _set->print();
        std::cout << "\n" << _set->erase(*cpl_float) << "\n";
        _set->print();

        delete _set;
        delete cpl_float;
    }

    std::cout << "\n\n";
    std::cout << "\n\n";

    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 1000);

        std::complex<double>* cpl_float = new std::complex<double>(3.5, 2.5);
        My_set<std::complex<double>>* _set = new My_set<std::complex<double>>(*cpl_float);

        std::cout << _set->get_element()->get_key() << "\n";

        for (size_t i = 0; i < 1100; i++)
        {
            std::complex<double> cpl((double)dist(gen) / 100, (double)dist(gen) / 100);
            _set->insert(cpl);
        }
        std::complex<double> cpl(1.93, 0.6);
        _set->insert(cpl);

        (_set->contains(cpl) == 0) ? std::cout << "false" << "\n" : std::cout << "true" << "\n";
        _set->print();
        std::cout << "\n" << _set->erase(*cpl_float) << "\n";
        _set->print();

        delete _set;
        delete cpl_float;
    }

    std::cout << "\n\n";
    std::cout << "\n\n";
    
    {
        std::string* str = new std::string("Hello!");
        My_set<std::string>* _set = new My_set<std::string>(*str);

        for (size_t i = 0; i < 1100; i++)
        {
            std::string str1(generateRandomText(3));
            _set->insert(str1);
        }
        std::string str1("good");
        _set->insert(str1);

        (_set->contains(str1) == 0) ? std::cout << "false" << "\n" : std::cout << "true" << "\n";
        _set->print();
        std::cout << "\n" << _set->erase(*str) << "\n";
        _set->print();

        delete str;
        delete _set;
    }
    
    return 0;
}

