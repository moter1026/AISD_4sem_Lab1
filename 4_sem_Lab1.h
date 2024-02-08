// 4_sem_Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>


// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.


template<typename T>
class Node {
private:
	T _key;
	Node* _right_ptr;
	Node* _left_ptr;
	//List* _root_ptr;
public:
	Node() = default;
	Node(Node& const obj) {
		this->_key = obj.get_key();
		this->_left_ptr = nullptr;
		this->_right_ptr = nullptr;
	}
	Node(T key) : _key(key), _right_ptr(nullptr), _left_ptr(nullptr) {}
	Node(T key, Node* right, Node* left) : _key(key), _right_ptr(right), _left_ptr(left) {}
	~Node() = default;

	T get_key() { return this->_key; }
	Node* get_right() { return this->_right_ptr; }
	Node* get_left() { return this->_left_ptr; }
	void set_left(Node* left) { this->_left_ptr = left; }
	void set_right(Node* right) { this->_right_ptr = right; }
	void print() {
		// Обход ЛКП - левый корень правый
		if (this->get_left() != nullptr) {	// обходим левые ветки, спускаемся к самому маленькому эл-ту
			this->get_left()->print();
		}

		std::cout << this->get_key() << " ";		// выводим корень

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

template<typename T>
class My_set
{
	Node<T>* _element;
public:
	My_set() {};
	My_set(Node<T>* el) {
		this->_element = new Node<T>(*el);
	};
	My_set(My_set<T>& const obj) {
		if (!&obj) { throw std::runtime_error("Передан пустой объект"); }

		Node<T>* el = obj.get_element(); // создаю один Node, чтобы у первого элемента был адрес и ключ
		this->_element = new Node<T>(el->get_key());
		std::stack<Node<T>*> stk;
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
	My_set(Node<T>& const node) {
		if (!&node) { throw std::runtime_error("Передан пустой объект"); }

		Node<T>* el = &node;
		this->_element = new Node<T>(el->get_key());
		std::stack<Node<T>*> stk;
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
	~My_set() {
		std::stack<Node<T>*> stack;
		stack.push(_element);

		while (!stack.empty()) {
			Node<T>* current = stack.top();
			stack.pop();

			if (current->get_right() != nullptr) {
				stack.push(current->get_right());
			}

			if (current->get_left() != nullptr) {
				stack.push(current->get_left());
			}

			delete current;
		}
	}

	bool insert(T key) {
		Node<T>* el = this->_element;
		while (true) {
			if (key < el->get_key() && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (key < el->get_key() && el->get_left() == nullptr) {
				el->set_left(new Node(key));
				return true;
			}
			else if (key > el->get_key() && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (key > el->get_key() && el->get_right() == nullptr) {
				el->set_right(new Node(key));
				return true;
			}
			else {
				break;
			}
		}
		return false;
	}
	Node<T>* get_element() { return this->_element; }
	void print() {
		this->_element->print();
	}

};
