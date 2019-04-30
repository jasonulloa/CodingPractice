#pragma once
#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <string>

class ListException : public std::exception {
	private:
		bool emptyList;
		int index;
	public:
		ListException(bool b, int i) {
			emptyList = b;
			index = i;
		}

		std::string what() {
			if (emptyList) {
				std::string message = "ListException: The list is empty.\n";

				return message;
			}
			std::string message = "ListException: The index " + std::to_string(index) + "does not exist.\n";

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
		List(const List<T>& other);  //copy constructor
		List<T>& operator=(const List<T>& other);  //assignment operator
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
		void pop_front();  //removes element from front of list; throws exception if list is empty
		void push_back(const T& val);  //adds value to back of list
		void pop_back();  //removes element from back of list; throws exception if list is empty
		void insert(int pos, const T& val);  //inserts a value at index pos; throws exception if out of bounds
		void erase(int pos);  //erases element at index pos; throws exception if out of bounds
		void swap(int pos1, int pos2);  //swaps values between nodes at pos1 and pos2
		void reverse();  //reverses the order of elements in list
		void clear();  //clear the list
		void print_list();  //prints the list contents; throws exception if list is empty
		ListNode<T>* headnode() const;  //returns head
		ListNode<T>* tailnode() const;  //returns tail

	private:
		ListNode<T>* get_node_at(int pos) const;  //returns a pointer to node at pos; throws exception if empty or out of bounds

		ListNode<T>* head;
		ListNode<T>* tail;
		int counter;
};

template <typename T>
List<T>::List() {
	this->head = nullptr;
	this->tail = nullptr;
	this->counter = 0;
}

template <typename T>
List<T>::~List() {
	clear();
}

template <typename T>
List<T>::List(const List<T>& other) {
	if (other.size() < 1) {  //counter should never be negative, so only size() == 0 should reach here
		this->head = nullptr;
		this->tail = nullptr;
		this->counter = 0;
	}
	else if (other.size() == 1) {
		T tempval = other.front();
		this->push_front(tempval);
	}
	else {  //for size() > 1
		for (int i = 0; i < other.size(); i++) {
			T tempval = other.get_node_at(i)->val;
			this->push_back(tempval);
		}
	}
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other) {
		return *this;
	}

	if (!this->empty()) {
		this->clear();
	}

	if (other.size() < 1) {  //counter should never be negative, so only size() == 0 should reach here
		this->head = nullptr;
		this->tail = nullptr;
		this->counter = 0;
	}
	else if (other.size() == 1) {
		T tempval = other.front();
		this->push_front(tempval);
	}
	else {  //for size() > 1
		for (int i = 0; i < other.size(); i++) {
			T tempval = other.get_node_at(i)->val;
			this->push_back(tempval);
		}
	}

	return *this;
}

template <typename T>
int List<T>::size() const {
	return counter;
}

template <typename T>
bool List<T>::empty() const {
	return counter == 0;
}

template <typename T>
T& List<T>::front() {
	ListNode<T>* temp = get_node_at(0);
	return temp->val;
}

template <typename T>
T const & List<T>::front() const {
	ListNode<T>* temp = get_node_at(0);
	return temp->val;
}

template <typename T>
T& List<T>::back() {
	ListNode<T>* temp = get_node_at(size() - 1);
	return temp->val;
}

template <typename T>
T const & List<T>::back() const {
	ListNode<T>* temp = get_node_at(size() - 1);
	return temp->val;
}

template <typename T>
void List<T>::set(int pos, const T& val) {
	ListNode<T>* temp = get_node_at(pos);
	temp->val = val;
}

template <typename T>
T& List<T>::get(int pos) {
	ListNode<T>* temp = get_node_at(pos);
	return temp->val;
}

template <typename T>
T const & List<T>::get(int pos) const {
	ListNode<T>* temp = get_node_at(pos);
	return temp->val;
}

template <typename T>
void List<T>::push_front(const T& val) {
	if (counter > 0) {  //if list is not empty
		ListNode<T>* temp = new ListNode<T>();
		temp->next = head;
		temp->prev = nullptr;
		temp->val = val;
		head = temp;
		temp = temp->next;
		temp->prev = head;
		counter++;
	}
	else {  //counter should never be negative, so this is effectively if == 0
		ListNode<T>* temp = new ListNode<T>();
		temp->next = nullptr;
		temp->prev = nullptr;
		temp->val = val;
		head = temp;
		tail = temp;
		counter++;
	}
}

template <typename T>
void List<T>::pop_front() {
	if (empty()) {
		throw ListException(true, 0);
	}

	ListNode<T>* temp = head;
	if (head->next != nullptr) {  //if list size() > 1
		head = temp->next;
		head->prev = nullptr;
	}
	else {  //if list size() == 1
		tail = nullptr;
		head = nullptr;
	}

	delete temp;
	counter--;
}

template <typename T>
void List<T>::push_back(const T& val) {
	if (counter > 0) {  //if list is not empty
		ListNode<T>* temp = new ListNode<T>();
		temp->next = nullptr;
		temp->prev = tail;
		temp->val = val;
		tail = temp;
		temp = temp->prev;
		temp->next = tail;
		counter++;
	}
	else {  //counter should never go below 0, so this is effectively if == 0
		ListNode<T>* temp = new ListNode<T>();
		temp->next = nullptr;
		temp->prev = nullptr;
		temp->val = val;
		head = temp;
		tail = temp;
		counter++;
	}
}

template <typename T>
void List<T>::pop_back() {
	if (empty()) {
		throw ListException(true, 0);
	}

	ListNode<T>* temp = tail;
	if (tail->prev != nullptr) {  //if list size() > 1
		tail = temp->prev;
		tail->next = nullptr;
	}
	else {  //if list size() == 1
		tail = nullptr;
		head = nullptr;
	}
	
	delete temp;
	counter--;
}

template <typename T>
void List<T>::insert(int pos, const T& val) {
	if (pos < 0 || pos > size()) {
		throw ListException(false, pos);
	}

	if (pos == 0) {
		push_front(val);
		return;
	}

	if (pos > 0 && pos < size()) {
		ListNode<T>* oldpos = get_node_at(pos);
		ListNode<T>* newpos = new ListNode<T>();
		newpos->val = val;
		newpos->prev = oldpos->prev;
		newpos->next = oldpos;
		oldpos->prev->next = newpos;
		oldpos->prev = newpos;
		counter++;
		return;
	}

	push_back(val);
}

template <typename T>
void List<T>::erase(int pos) {
	if (pos < 0 || pos >= size()) {
		throw ListException(false, pos);
	}

	if (pos == 0) {  //for first pos
		pop_front();
		return;
	}

	if (pos > 0 && pos < size() - 1) {  //for pos between first and last
		ListNode<T>* temp = get_node_at(pos);
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
		counter--;
		return;
	}

	pop_back();  //for last pos
}

template <typename T>
void List<T>::swap(int pos1, int pos2) {
	T val1 = get(pos1);
	T val2 = get(pos2);
	set(pos1, val2);
	set(pos2, val1);
}

template <typename T>
void List<T>::reverse() {
	int headpos = 0;
	int tailpos = size() - 1;

	while (tailpos > headpos) {
		swap(headpos, tailpos);
		headpos++;
		tailpos--;
	}
}

template <typename T>
void List<T>::clear() {
	while (head != nullptr) {
		ListNode<T>* oldhead = head;
		head = head->next;
		delete oldhead;
	}
	tail = nullptr;
	counter = 0;
}

template <typename T>
void List<T>::print_list() {
	if (empty()) {
		throw ListException(true, 0);
	}

	std::cout << "The list contains: ";
	for (int i = 0; i < this->size(); i++) {
		std::cout << this->get(i) << ", ";
	}
	
	std::cout << std::endl;
}

template <typename T>
ListNode<T>* List<T>::get_node_at(int pos) const {
	if (empty()) {
		throw ListException(true, pos);
	}

	ListNode<T>* temp = head;

	if (pos >= 0 && pos < counter) {
		while (temp != nullptr && pos > 0) {
			temp = temp->next;
			pos--;
		}

		return temp;
	}
	else {
		throw ListException(false, pos);
	}
}

template <typename T>
ListNode<T>* List<T>::headnode() const {
	return this->head;
}

template <typename T>
ListNode<T>* List<T>::tailnode() const {
	return this->tail;
}
#endif