// 4_sem_Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.


template<typename T>
class Set_analog {
private:
	T _key;
	T* _next_el;
	T* _prev_el;
public:
	Set_analog() = default;
	Set_analog(Set_analog& const obj) {

	}
	~Set_analog() {

	}
	get_key() { return this->_key; }
	get_next() { return this->_next_el; }
	get_prev() { return this->_prev_el; }
};