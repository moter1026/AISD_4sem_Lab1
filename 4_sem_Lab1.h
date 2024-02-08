// 4_sem_Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>


// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.


template<typename T>
class List {
private:
	T _key;
	List* _right_ptr;
	List* _left_ptr;
	//List* _root_ptr;
public:
	List() = default;
	List(List& const obj) {
		if (!&obj) { throw std::runtime_error("Передан пустой объект");	}

		List* el = &obj;
		this->_key = obj.get_key();
		this->_left_ptr = nullptr;
		this->_right_ptr = nullptr;
		std::stack<List*> stk;
		while (el != nullptr || !stk.empty())
		{
			if (!stk.empty())
			{
				el = stk.top();
				stk.pop();
				if (el->get_right() != nullptr)
				{
					el = el->get_right();
				}
				else
				{
					el = nullptr;
				}
			}
			while (el != nullptr)
			{
				stk.push(el);
				this->insert(el->get_key());
				el = el->get_left();
			}
		}	
	}
	List(T key) : _key(key), _right_ptr(nullptr), _left_ptr(nullptr) {}
	List(T key, List* right, List* left) : _key(key), _right_ptr(right), _left_ptr(left) {}
	List(T key, List* right, List* left, List* root) : _key(key), _right_ptr(right), _left_ptr(left) {}
	~List() {
		this->_key = 0;
	}
	T get_key() { return this->_key; }
	List* get_right() { return this->_right_ptr; }
	List* get_left() { return this->_left_ptr; }
	void set_left(List* left) { this->_left_ptr = left; }
	void set_right(List* right) { this->_right_ptr = right; }
	void print() {
		// Обход ЛКП - левый корень правый
		if (this->get_left() != nullptr) {	// обходим левые ветки, спускаемся к самому маленькому эл-ту
			this->get_left()->print();
		}
		else								// доходим до самого левого эл-та, выводим его, возвращаемся назад
		{
			std::cout << this->get_key();
			return;
		}

		std::cout << this->get_key();		// выводим корень

		if (this->get_right() != nullptr)	// обходим правые ветки
		{
			this->get_right()->print();
			return;
		}
		else
		{
			return;
		}
	}
	void insert(T key) {
		List* el = this;
		while (true) {
			if (key < el->get_key() && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (key < el->get_key() && el->get_left() == nullptr) {
				el->set_left(new List(key));
				break;
			}
			else if (key > el->get_key() && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (key > el->get_key() && el->get_right() == nullptr) {
				el->set_right(new List(key));
				break;
			}
			else {
				break;
			}
		}
		
	}
};

