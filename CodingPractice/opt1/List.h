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
		void insert(int pos, const T& val);  //inserts a value at index pos
		void erase(int pos);  //erases element at index pos
		void swap(int pos1, int pos2);  //swaps values between nodes at indicies pos1 and pos2
		void listswap(List& other);  //swaps contents of list with other list
		void reverse();  //reverses the order of elements in list
		void clear();  //clear the list

	private:
		ListNode<T>* getNodeAt(int pos) const;  //returns a pointer to node at pos; throws exception if empty or out of bounds

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
			T tempval = other.getNodeAt(i);
			this->push_back(tempval);
		}
	}
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	this->clear();

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
			T tempval = other.getNodeAt(i);
			this->push_back(tempval);
		}
	}
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
	ListNode<T>* temp = getNodeAt(0);
	return temp->val;
}

template <typename T>
T const & List<T>::front() const {
	ListNode<T>* temp = getNodeAt(0);
	return temp->val;
}

template <typename T>
T& List<T>::back() {
	ListNode<T>* temp = getNodeAt(size() - 1);
	return temp->val;
}

template <typename T>
T const & List<T>::back() const {
	ListNode<T>* temp = getNodeAt(size() - 1);
	return temp->val;
}

template <typename T>
void List<T>::set(int pos, const T& val) {
	ListNode<T>* temp = getNodeAt(pos);
	temp->val = val;
}

template <typename T>
T& List<T>::get(int pos) {
	ListNode<T>* temp = getNodeAt(pos);
	return temp->val;
}

template <typename T>
T const & List<T>::get(int pos) const {
	ListNode<T>* temp = getNodeAt(pos);
	return temp->val;
}

template <typename T>
void List<T>::push_front(const T& val) {
	if (counter > 0) {  //if list is not empty
		ListNode<T>* temp = new ListNode();
		temp->next = head;
		temp->prev = nullptr;
		temp->val = val;
		head = temp;
		temp = temp->next;
		temp->prev = head;
		counter++;
	}
	else {  //counter should never be negative, so this is effectively if == 0
		ListNode<T>* temp = new ListNode();
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
		return;
	}

	ListNode<T>* temp = head;
	head = temp->next;
	head->prev = nullptr;
	delete temp;
}

template <typename T>
void List<T>::push_back(const T& val) {
	if (counter > 0) {  //if list is not empty
		ListNode<T>* temp = new ListNode();
		temp->next = nullptr;
		temp->prev = tail;
		temp->val = val;
		tail = temp;
		temp = temp->prev;
		temp->next = tail;
		counter++;
	}
	else {  //counter should never go below 0, so this is effectively if == 0
		ListNode<T>* temp = new ListNode();
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
		return;
	}

	ListNode<T>* temp = tail;
	tail = temp->prev;
	tail->next = nullptr;
	delete temp;
}

template <typename T>
void List<T>::insert(int pos, const T& val) {
	//TODO//////////////////////////////////////////////////////////
}

template <typename T>
void List<T>::erase(int pos) {
	//TODO//////////////////////////////////////////////////////////
}

template <typename T>
void List<T>::swap(int pos1, int pos2) {
	//TODO//////////////////////////////////////////////////////////
}

template <typename T>
void List<T>::listswap(List& other) {
	//TODO//////////////////////////////////////////////////////////
}

template <typename T>
void List<T>::reverse() {
	//TODO//////////////////////////////////////////////////////////
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
ListNode<T>* List<T>::getNodeAt(int pos) const {
	if (empty()) {
		throw ListException(true, pos);
		return nullptr;
	}

	ListNode *temp = head;

	if (pos >= 0 && pos < counter) {
		while (temp != nullptr && pos > 0) {
			temp = temp->next;
			pos--;
		}

		return temp;
	}
	else {
		throw ListException(false, pos);
		return nullptr;
	}
}
#endif