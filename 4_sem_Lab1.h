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
public:
	Node() = default;
	Node(Node&  obj) {
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
public:
	Node() = default;
	Node(Node< std::complex<T>>& obj) {
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
	My_set(My_set<T>& obj) {
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
	My_set(Node<T>& node) {
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
protected:
	class Is_inside_and_ptr {	// Класс для работы метода поиска 
	public:
		bool _is_inside;
		Node<std::complex<T>>* _ptr;	// При использовании insert будет храть указатель на самый близкий к вставляемому эл-ту корню
										// При использ. contains будет хранить эл-т на необходимы эл-т
		Is_inside_and_ptr() = default;
		Is_inside_and_ptr(bool is_inside, Node<std::complex<T>>* ptr): _is_inside(is_inside), _ptr(ptr) {}
	};

	Node<std::complex<T>>* _element;
	int _count;

	long double length(std::complex<T>* cmp) {
		return sqrt(powl(cmp->real(), 2) + powl(cmp->imag(), 2));
	}
	bool areEqual(long double one, long double two, long double epsilon = 0.00001) {
		return std::abs(one - two) < epsilon;
	}
	bool compare(Node<std::complex<T>>& root, std::complex<T> key, Node<std::complex<T>>* & ptr_obj) {	// Если ф-я возвращает false - значит эл-т не найден
																								// out: is_in - возвращает либо сам эл-т, если он есть, либо ближайший корень 
		Node<std::complex<T>>* el = &root;
		auto k_real = key.real();
		auto k_imag = key.imag();
		while (true) {
			std::complex<T> el_cmp = el->get_key();
			auto el_real = el_cmp.real();
			auto el_imag = el_cmp.imag();
			if (k_real == el_real && k_imag == el_imag)
			{
				ptr_obj = el;
				return true;
			}
			else if (k_real < el_real && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (k_real < el_real && el->get_left() == nullptr) {
				ptr_obj = el;
				return false;
			}
			else if (k_real > el_real && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (k_real > el_real && el->get_right() == nullptr) {
				ptr_obj = el;
				return false;
			}
			else if(k_real == el_real){
				if (k_imag < el_imag && el->get_left() != nullptr)
				{
					el = el->get_left();
				}
				else if (k_imag < el_imag && el->get_left() == nullptr)
				{
					ptr_obj = el;
					return false;
				}
				else if (k_imag > el_imag && el->get_right() != nullptr)
				{
					el = el->get_right();
				}
				else if (k_imag > el_imag && el->get_right() == nullptr) {
					ptr_obj = el;
					return false;
				}
			}
		}
			
	}
public:
	My_set() : _element(new Node<std::complex<T>>(0, 0)), _count(1) {};
	My_set(std::complex<T> key) : _count(1) {
		this->_element = new Node<std::complex<T>>(key);
	}
	My_set(Node<std::complex<T>>* el) : _count(1) {
		this->_element = new Node<std::complex<T>>(*el);
	};
	My_set(My_set<std::complex<T>>& obj) {
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
	My_set(Node<std::complex<T>>& node) {
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
		Node<std::complex<T>>* ptr_obj = nullptr;

		bool res = this->compare(*el, key, ptr_obj);
		if (res) return false;
		else {
			std::complex<T> obj = ptr_obj->get_key();
			auto k_real = key.real();
			auto o_real = obj.real();
			if (k_real < o_real && ptr_obj->get_left() == nullptr)
			{
				ptr_obj->set_left(new Node<std::complex<T>>(key));
				return true;
			}
			else if (k_real > o_real && ptr_obj->get_right() == nullptr) {
				ptr_obj->set_right(new Node<std::complex<T>>(key));
				return true;
			}
			else if (k_real == o_real)
			{
				auto k_imag = key.imag();
				auto o_imag = obj.imag();
				if (k_imag < o_imag && ptr_obj->get_left() == nullptr)
				{
					ptr_obj->set_left(new Node<std::complex<T>>(key));
					return true;
				}
				else if (k_imag > o_imag && ptr_obj->get_right() == nullptr) {
					ptr_obj->set_right(new Node<std::complex<T>>(key));
					return true;
				}
			}
		}
		return false;
	}
	bool contains(std::complex<T> key) {	// переделать
		Node<std::complex<T>>* el = this->_element;
		Node<std::complex<T>>* ptr = nullptr;
		if (!el) return false;
		return this->compare(*el, key, ptr);

	} 
	bool erase(std::complex<T> key) {
		Node<std::complex<T>>* el = this->_element;
		if (el == nullptr) return false;
		std::stack<Node<std::complex<T>>*> stk;
		std::complex<T> el_cmp = el->get_key();
		stk.push(el);

		auto k_real = key.real();
		auto k_imag = key.imag();
		while(true) {
			auto el_real = el_cmp.real();
			auto el_imag = el_cmp.imag();
			if (k_real == el_real && k_imag == el_imag)
			{
				if (el->get_left() != nullptr && el->get_right() != nullptr) // Если два потомка, то самый правый, левого поддерева
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
					Node<std::complex<T>>* root = el;
					if (stk.size() == 1) {
						this->_element = el->get_left();
					}
					else
					{
						stk.pop();
						root = stk.top();
						if (root->get_left() == el) {
							root->set_left(el->get_left());
						}
						else if (root->get_right() == el)
						{
							root->set_right(el->get_left());
						}
					}
					this->_count--;
					delete el;
					return true;
				}
				else if (el->get_left() == nullptr && el->get_right() != nullptr)
				{
					Node<std::complex<T>>* root = el;
					if (stk.size() == 1) {
						this->_element = el->get_left();
					}
					else
					{
						stk.pop();
						root = stk.top();
						if (root->get_left() == el) {
							root->set_left(el->get_right());
						}
						else if (root->get_right() == el)
						{
							root->set_right(el->get_right());
						}
					}
					this->_count--;
					delete el;
					return true;
				}
				else
				{
					Node<std::complex<T>>* root = el;
					if (stk.size() == 1) {
						this->_element = nullptr;
					}
					else
					{
						stk.pop();
						root = stk.top();
						if (root->get_left() == el) {
							root->set_left(nullptr);
						}
						else if (root->get_right() == el)
						{
							root->set_right(nullptr);
						}
					}
					this->_count--;
					delete el;
					return true;
				}
			}
			else if (k_real < el_real && el->get_left() != nullptr)
			{
				el = el->get_left();
			}
			else if (k_real < el_real && el->get_left() == nullptr) {
				return false;
			}
			else if (k_real > el_real && el->get_right() != nullptr)
			{
				el = el->get_right();
			}
			else if (k_real > el_real && el->get_right() == nullptr) {
				return false;
			}
			else if (k_real == el_real) {
				if (k_imag < el_imag && el->get_left() != nullptr)
				{
					el = el->get_left();
				}
				else if (k_imag < el_imag && el->get_left() == nullptr)
				{
					return false;
				}
				else if (k_imag > el_imag && el->get_right() != nullptr)
				{
					el = el->get_right();
				}
				else if (k_imag > el_imag && el->get_right() == nullptr) {
					return false;
				}
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
