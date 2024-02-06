// 4_sem_Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.


template<typename T>
class Set_analog {
private:
	T _key;
	Set_analog* _right_el;
	Set_analog* _left_el;
public:
	Set_analog() : _key(0), _right_el(nullptr), _left_el(nullptr) {}
	Set_analog(Set_analog& const obj) {
		this->_key = obj.get_key();
		if (obj.get_right() != nullptr)
		{
			this->_right_el = new Set_analog(*(obj.get_left()));
		}
		else {
			this->_right_el = nullptr;
		}

		if (obj.get_left() != nullptr) {
			this->_left_el = new Set_analog(*(obj.get_right()));
		}
		else {
			this->_left_el = nullptr;
		}
	}
	Set_analog(T key) : _key(key), _right_el(nullptr), _left_el(nullptr) {}
	Set_analog(T key, Set_analog* right, Set_analog* left) : _key(key), _right_el(right), _left_el(left) {}
	~Set_analog() {

	}
	T get_key() { return this->_key; }
	Set_analog* get_right() { return this->_right_el; }
	Set_analog* get_left() { return this->_left_el; }
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
};