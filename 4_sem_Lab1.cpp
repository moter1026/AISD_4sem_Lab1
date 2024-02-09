// 4_sem_Lab1.cpp: определяет точку входа для приложения.
//

#include "4_sem_Lab1.h"
#include <ctime>
#include <random>
#include <algorithm>
#include <complex>

using namespace std;

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
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
        double set_medium_insert[3];
        double set_medium_contains[3];
        double set_medium_add[3];
        double set_medium_delete[3];

        double vector_medium_insert[3];
        double vector_medium_contains[3];
        double vector_medium_add[3];
        double vector_medium_delete[3];

        const int attempt = 100;
        const int attempt_contains_add_del = 1000;

        for (size_t s = 0; s < 3; ++s)
        {
            std::cout << "\n>>> Выполняем процедуры для дерева размером " << size[s] << "\n\n";

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
                sum_insert += (end_insert - start_insert);
            }
            set_medium_insert[s] = (double)sum_insert / attempt;
            std::cout << "Закончили заполнять. Сред. время - " << set_medium_insert[s] << "\n\n\n";


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
                sum_contains += (end_contains - start_contains);
            }
            set_medium_contains[s] = (double)sum_contains / attempt_contains_add_del;
            std::cout << "Закончили проверять. Сред. время - " << set_medium_contains[s] << "\n\n\n";


            std::cout << "Добавляем значения...\n";
            size_t sum_add = 0;
            for (size_t i = 0; i < attempt_contains_add_del; i++)
            {
                int start_add = std::clock();

                _set.insert(dist(gen));

int end_add = std::clock();
sum_add += (end_add - start_add);
            }
            set_medium_add[s] = (double)sum_add / attempt_contains_add_del;
            std::cout << "Закончили добавлять. Сред. время - " << set_medium_add[s] << "\n\n\n";

            std::cout << "Удаляем значения...\n";
            size_t sum_delete = 0;
            for (size_t i = 0; i < attempt_contains_add_del; i++)
            {
                int start_delete = std::clock();

                bool res = _set.erase(dist(gen));
                int end_delete = std::clock();
                sum_delete += (end_delete - start_delete);
            }
            set_medium_delete[s] = (double)sum_delete / attempt_contains_add_del;
            std::cout << "Закончили удалять. Время - " << set_medium_delete[s] << "\n\n\n";
        }





        for (size_t s = 0; s < 3; ++s)
        {
            std::cout << "\n>>> Выполняем процедуры для VECTOR размером " << size[s] << "\n\n";

            std::cout << "Заполняем " << size[s] << " псевдо случайными числами...\n";
            size_t sum_insert = 0;
            for (size_t j = 0; j < attempt; ++j)
            {
                int start_insert = std::clock();
                std::vector<int> _vector(static_cast<int>(lcg()));
                for (size_t i = 1; i < size[s]; ++i) {

                    int val = static_cast<int>(lcg());
                    for (size_t i = 0; i < _vector.size() - 1; i++)
                    {
                        if (val <= _vector[i])
                        {
                            _vector.insert(_vector.begin() + i, val);
                            break;
                        }
                        else if (i == _vector.size() - 1)
                        {
                            _vector.push_back(val);
                        }

                    }
                }
                //std::cout << j;
                int end_insert = std::clock();
                sum_insert += (end_insert - start_insert);
            }
            vector_medium_insert[s] = (double)sum_insert / attempt;
            std::cout << "Закончили заполнять. Сред. время - " << vector_medium_insert[s] << "\n\n\n";


            std::vector<int> _vector(static_cast<int>(lcg()));
            for (size_t i = 1; i < size[s]; ++i) {
                _vector.push_back(static_cast<int>(lcg()));
            }

            std::cout << "Проверяем наличие значений...\n";
            size_t sum_contains = 0;
            for (size_t i = 0; i < attempt_contains_add_del; i++)
            {
                int start_contains = std::clock();

                bool res = std::find(_vector.begin(), _vector.end(), dist(gen)) != _vector.end();

                int end_contains = std::clock();
                sum_contains += (end_contains - start_contains);
            }
            vector_medium_contains[s] = (double)sum_contains / attempt_contains_add_del;
            std::cout << "Закончили проверять. Сред. время - " << vector_medium_contains[s] << "\n\n\n";


            std::cout << "Добавляем значения...\n";
            size_t sum_add = 0;
            for (size_t i = 0; i < attempt_contains_add_del; i++)
            {
                int start_add = std::clock();

                _vector.push_back(dist(gen));

                int end_add = std::clock();
                sum_add += (end_add - start_add);
            }
            vector_medium_add[s] = (double)sum_add / attempt_contains_add_del;
            std::cout << "Закончили добавлять. Сред. время - " << vector_medium_add[s] << "\n\n\n";

            std::cout << "Удаляем значения...\n";
            size_t sum_delete = 0;
            for (size_t i = 0; i < attempt_contains_add_del; i++)
            {
                int start_delete = std::clock();

                auto res = std::find(_vector.begin(), _vector.end(), dist(gen));
                if (res == _vector.end()) { continue; }
                _vector.erase(res);

                int end_delete = std::clock();
                sum_delete += (end_delete - start_delete);
            }
            vector_medium_delete[s] = (double)sum_delete / attempt_contains_add_del;
            std::cout << "Закончили удалять. Время - " << vector_medium_delete[s] << "\n\n\n";
        }
    }



    

    
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 1000);

        std::complex<float> cpl_float(10.5, 2.5);
        My_set<std::complex<float>> _set(cpl_float);

        std::cout << _set.get_element()->get_key() << "\n";

        for (size_t i = 0; i < 1100; i++)
        {
            std::complex<float> cpl((float)dist(gen) / 100, (float)dist(gen) / 100);
            _set.insert(cpl);
        }
        std::complex<float> cpl(1.93, 0.6);
        _set.insert(cpl);

        (_set.contains(cpl) == 0) ? std::cout << "false" << "\n" : std::cout << "true" << "\n";

        std::cout << _set.erase(cpl_float) << "\n";
    }
    
    return 0;
}

