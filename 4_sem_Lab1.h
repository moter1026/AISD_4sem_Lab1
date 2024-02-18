// 4_sem_Lab1.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <stack>
#include <algorithm>
#include <complex>


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
	void set_key(T key) { this->_key = key; }
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
class Node<std::complex<T>> {
private:
	std::complex<T> _key;
	Node< std::complex<T>>* _right_ptr;
	Node< std::complex<T>>* _left_ptr;
	//List* _root_ptr;
public:
	Node() = default;
	Node(Node< std::complex<T>>& const obj) {
		this->_key = obj.get_key();
		this->_left_ptr = nullptr;
		this->_right_ptr = nullptr;
	}
	Node(std::complex<T> key) : _key(key), _right_ptr(nullptr), _left_ptr(nullptr) {}
	Node(std::complex<T> key, Node< std::complex<T>>* right, Node< std::complex<T>>* left) : _key(key), _right_ptr(right), _left_ptr(left) {}
	~Node() = default;

	std::complex<T> get_key() { return this->_key; }
	Node< std::complex<T>>* get_right() { return this->_right_ptr; }
	Node< std::complex<T>>* get_left() { return this->_left_ptr; }
	void set_key(std::complex<T> key) { this->_key = key; }
	void set_left(Node< std::complex<T>>* left) { this->_left_ptr = left; }
	void set_right(Node< std::complex<T>>* right) { this->_right_ptr = right; }
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
	int _count;
public:
	My_set(): _element(new Node<T>(0)), _count(1) {};
	My_set(T key): _count(1) {
		this->_element = new Node<T>(key);
	}
	My_set(Node<T>* el): _count(1) {
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
				this->_count++;
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
				this->_count++;
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
				this->_count++;
				return true;
			}
			else if (key > el->get_key() && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (key > el->get_key() && el->get_right() == nullptr) {
				el->set_right(new Node(key));
				this->_count++;
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
	bool contains(T key) {
		Node<T>* el = this->_element;
		if (!el) return false;

		while (true) {
			if (key < el->get_key() && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (key < el->get_key() && el->get_left() == nullptr) {
				return false;
			}
			else if (key > el->get_key() && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (key > el->get_key() && el->get_right() == nullptr) {
				return false;
			}
			else if (key == el->get_key()) {
				return true;
			}
		}
		return false;
	}
	bool erase(T key) {
		Node<T>* el = this->_element;
		if (el == nullptr) return false;
		std::stack<Node<T>*> stk;
		stk.push(el);

		while (true) {
			if (key < el->get_key() && el->get_left() != nullptr)
			{
				el = el->get_left();
				stk.push(el);
			}
			else if (key < el->get_key() && el->get_left() == nullptr) {
				return false;
			}
			else if (key > el->get_key() && el->get_right() != nullptr)
			{
				el = el->get_right();
				stk.push(el);
			}
			else if (key > el->get_key() && el->get_right() == nullptr) {
				return false;
			}
			else if (key == el->get_key()) {
				if (el->get_left() != nullptr && el->get_right() != nullptr)
				{
					Node<T>* now = el;
					el = el->get_left();
					stk.push(el);
					while (el->get_right() != nullptr)
					{
						el = el->get_right();
						stk.push(el);
					}
					now->set_key(el->get_key());
				}
				
				if (el->get_left() != nullptr && el->get_right() == nullptr)
				{
					stk.pop();
					Node<T>* root = stk.top();
					if (root->get_left() == el) {
						root->set_left(el->get_left());
					}
					else if(root->get_right() == el)
					{
						root->set_right(el->get_left());
					}
					this->_count--;
					delete el;
					return true;
				}
				else if (el->get_left() == nullptr && el->get_right() != nullptr)
				{
					stk.pop();
					Node<T>* root = stk.top();
					if (root->get_left() == el) {
						root->set_left(el->get_right());
					}
					else if (root->get_right() == el)
					{
						root->set_right(el->get_right());
					}
					this->_count--;
					delete el;
					return true;
				}
				else
				{
					stk.pop();
					Node<T>* root = stk.top();
					if (root->get_left() == el) {
						root->set_left(nullptr);
					}
					else if (root->get_right() == el)
					{
						root->set_right(nullptr);
					}
					this->_count--;
					delete el;
					return true;
				}
			}
		}
		return false;
	}
	
};

template<typename T>
class My_set<std::complex<T>>  {
	Node<std::complex<T>>* _element;
	int _count;
	double length(std::complex<T>* cmp) {
		return sqrt(powl(cmp->real(), 2) + powl(cmp->imag(), 2));
	}
	bool areEqual(double one, double two, double epsilon = 0.00001) {
		return std::abs(one - two) < epsilon;
	}
public:
	My_set() : _element(new Node<std::complex<T>>(0, 0)), _count(1) {};
	My_set(std::complex<T> key) : _count(1) {
		this->_element = new Node<std::complex<T>>(key);
	}
	My_set(Node<std::complex<T>>* el) : _count(1) {
		this->_element = new Node<std::complex<T>>(*el);
	};
	My_set(My_set<std::complex<T>>& const obj) {
		if (!&obj) { throw std::runtime_error("Передан пустой объект"); }

		Node<std::complex<T>>* el = obj.get_element(); // создаю один Node, чтобы у первого элемента был адрес и ключ
		this->_element = new Node<std::complex<T>>(el->get_key());
		std::stack<Node<std::complex<T>>*> stk;
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
				this->_count++;
				el = el->get_left();
			}
		}
	}
	My_set(Node<std::complex<T>>& const node) {
		if (!&node) { throw std::runtime_error("Передан пустой объект"); }

		Node<std::complex<T>>* el = &node;
		this->_element = new Node<std::complex<T>>(el->get_key());
		std::stack<Node<std::complex<T>>*> stk;
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
				this->_count++;
				el = el->get_left();
			}
		}
	}
	~My_set() {
		std::stack<Node<std::complex<T>>*> stack;
		stack.push(_element);

		while (!stack.empty()) {
			Node<std::complex<T>>* current = stack.top();
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


	Node<std::complex<T>>* get_element() { return this->_element; }
	bool insert(std::complex<T> key) {
		Node<std::complex<T>>* el = this->_element;


		double key_length = this->length(&key);

		while (true) {
			std::complex<T> el_cmp = el->get_key();
			double el_length = this->length(&el_cmp);
			if (areEqual(key_length, el_length))
			{
				break;
			}
			else if (key_length < el_length && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (key_length < el_length && el->get_left() == nullptr) {
				el->set_left(new Node(key));
				this->_count++;
				return true;
			}
			else if (key_length > el_length && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (key_length > el_length && el->get_right() == nullptr) {
				el->set_right(new Node(key));
				this->_count++;
				return true;
			}
			else {
				break;
			}
		}
		return false;
	}
	bool contains(std::complex<T> key) {
		Node<std::complex<T>>* el = this->_element;
		if (!el) return false;
		

		double key_length = this->length(&key);

		while (true) {
			std::complex<T> el_cmp = el->get_key();
			double el_length = this->length(&el_cmp);

			if (areEqual(key_length, el_length)) {
				return true;
			}
			else if (key_length < el_length && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (key_length < el_length && el->get_left() == nullptr) {
				return false;
			}
			else if (key_length > el_length && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (key_length > el_length && el->get_right() == nullptr) {
				return false;
			}
			 
		}
		return false;
	}
	bool erase(std::complex<T> key) {
		Node<std::complex<T>>* el = this->_element;
		if (el == nullptr) return false;
		std::stack<Node<std::complex<T>>*> stk;
		stk.push(el);


		double key_length = this->length(&key);

		while (true) {
			std::complex<T> el_cmp = el->get_key();
			double el_length = this->length(&el_cmp);

			if (areEqual(key_length, el_length)) {
				if (el->get_left() != nullptr && el->get_right() != nullptr)
				{
					Node<std::complex<T>>* now = el;
					el = el->get_left();
					stk.push(el);
					while (el->get_right() != nullptr)
					{
						el = el->get_right();
						stk.push(el);
					}
					now->set_key(el->get_key());
				}

				if (el->get_left() != nullptr && el->get_right() == nullptr)
				{
					stk.pop();
					Node<std::complex<T>>* root = stk.top();
					if (root->get_left() == el) {
						root->set_left(el->get_left());
					}
					else if (root->get_right() == el)
					{
						root->set_right(el->get_left());
					}
					this->_count--;
					delete el;
					return true;
				}
				else if (el->get_left() == nullptr && el->get_right() != nullptr)
				{
					stk.pop();
					Node<std::complex<T>>* root = stk.top();
					if (root->get_left() == el) {
						root->set_left(el->get_right());
					}
					else if (root->get_right() == el)
					{
						root->set_right(el->get_right());
					}
					this->_count--;
					delete el;
					return true;
				}
				else
				{
					stk.pop();
					Node<std::complex<T>>* root = stk.top();
					if (root->get_left() == el) {
						root->set_left(nullptr);
					}
					else if (root->get_right() == el)
					{
						root->set_right(nullptr);
					}
					this->_count--;
					delete el;
					return true;
				}
			}
			else if (key_length < el_length && el->get_left() != nullptr)
			{
				el = el->get_left();
				stk.push(el);
			}
			else if (key_length < el_length && el->get_left() == nullptr) {
				return false;
			}
			else if (key_length > el_length && el->get_right() != nullptr)
			{
				el = el->get_right();
				stk.push(el);
			}
			else if (key_length > el_length && el->get_right() == nullptr) {
				return false;
			}
			 
		}
		return false;
	}
	void print() {
		this->_element->print();
	}
};


std::vector<int> repeat_els(std::vector<int>* _vec) {
	size_t size = (*_vec).size();
	std::vector<int> new_vector;
	if (size == 0) return new_vector;
		
	My_set<int> my_set((*_vec)[0]);
	for (size_t i = 1; i < size; ++i)
	{
		if (my_set.insert((*_vec)[i])) continue;
		else {
			int el = (*_vec)[i];
			auto it = std::find(new_vector.begin(), new_vector.end(), el);
			if (new_vector.end() == it)
			{
				new_vector.push_back(el);
			}
		}
	}

	return new_vector;
}
