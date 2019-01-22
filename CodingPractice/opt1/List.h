#pragma once
#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <string>

class OutOfBounds : public std::exception {
	private:
		int index;
	public:
		OutOfBounds(int i) {
			index = i;
		}

		std::string what() {
			std::string message = "OutOfBounds: The index " + std::to_string(index) + "does not exist.\n";

			return message;
		}
};

template <typename T>
struct ListNode {
	T val;
	ListNode<T>* prev;
	ListNode<T>* next;
};

template <typename T>
class List {
	public:
		List();  //default construct
		~List();  //destructor
		List(const List& other);  //copy constructor
		List& operator=(const List& other);  //assignment operator
		int size() const;  //returns size of list
		bool empty() const;  //checks if list is empty
		T& front();  //returns value at front of list
		T const & front() const;  //returns const value at front of list
		T& back();  //returns value at back of list
		T const & back() const;  //returns const value at back of list
		void set(int pos, const T& val);  //overwrites old value at index pos with val
		T& get(int pos);  //returns value at index pos
		T const & get(int pos) const;  //returns const value at index pos
		void push_front(const T& val);  //adds value to front of list
		void pop_front();  //removes element from front of list
		void push_back(const T& val);  //adds value to back of list
		void pop_back();  //removes element from back of list
		void insert(int pos, const T& val);  //inserts a value at index pos
		void erase(int pos);  //erases element at index pos
		void swap(int pos1, int pos2);  //swaps values between nodes at indicies pos1 and pos2
		void listswap(List& other);  //swaps contents of list with other list
		void reverse();  //reverses the order of elements in list
		void clear();  //clear the list

	private:
		ListNode* getNodeAt(int pos) const;  //returns a pointer to node at index pos

		ListNode<T>* head;
		ListNode<T>* tail;
		int counter;
};

template <typename T>
List::List() {
	this->head = nullptr;
	this->tail = nullptr;
	this->counter = 0;
}

template <typename T>
List::~List() {
	clear();
}

template <typename T>
List::List(const List& other) {
	if (other.empty()) {
		this->head = nullptr;
		this->tail = nullptr;
		this->counter = 0;
	}
	else if (other.size() == 1) {
		//TODO
	}
}

template <typename T>
List& List::operator=(const List& other) {
	//TODO
}

template <typename T>
int List::size() const {
	return counter;
}

template <typename T>
bool List::empty() const {
	return counter == 0;
}

template <typename T>
T& List::front() {
	ListNode* temp = getNodeAt(0);
	return temp->val;
}

template <typename T>
T const & List::front() const {
	ListNode* temp = getNodeAt(0);
	return temp->val;
}

template <typename T>
T& List::back() {
	ListNode* temp = getNodeAt(size() - 1);
	return temp->val;
}

template <typename T>
T const & List::back() const {
	ListNode* temp = getNodeAt(size() - 1);
	return temp->val;
}

template <typename T>
void List::set(int pos, const T& val) {
	//TODO
}

template <typename T>
T& List::get(int pos) {
	//TODO
}

template <typename T>
T const & List::get(int pos) const {
	//TODO
}

template <typename T>
void List::push_front(const T& val) {
	//TODO
}

template <typename T>
void List::pop_front() {
	//TODO
}

template <typename T>
void List::push_back(const T& val) {
	//TODO
}

template <typename T>
void List::pop_back() {
	//TODO
}

template <typename T>
void List::insert(int pos, const T& val) {
	//TODO
}

template <typename T>
void List::erase(int pos) {
	//TODO
}

template <typename T>
void List::swap(int pos1, int pos2) {
	//TODO
}

template <typename T>
void List::listswap(List& other) {
	//TODO
}

template <typename T>
void List::reverse() {
	//TODO
}

template <typename T>
void List::clear() {
	while (head != nullptr) {
		ListNode<T>* oldhead = head;
		head = head->next;
		delete oldhead;
	}
	tail = nullptr;
	counter = 0;
}

template <typename T>
ListNode* List::getNodeAt(int pos) const {
	ListNode *temp = head;

	if (pos >= 0 && pos < counter) {
		while (temp != nullptr && pos > 0) {
			temp = temp->next;
			pos--;
		}

		return temp;
	}
	else {
		throw OutOfBounds(pos);
		return nullptr;
	}
}
#endif