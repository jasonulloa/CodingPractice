#pragma once
#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include "List.h"

template <typename T>
class Unordered_Set {
	public:
		Unordered_Set();  //default construct
		~Unordered_Set();  //destructor
		Unordered_Set(const Unordered_Set<T>& other);  //copy constructor
		Unordered_Set<T>& operator=(const Unordered_Set<T>& other);  //assignment operator
		int size() const;  //returns size of set
		bool empty() const;  //checks if set is empty
		T& begin();  //sets pointer curr to the first node and returns value
		T const & begin() const;  //sets pointer curr to the first node and returns value
		T& end();  //sets pointer curr to the last node and returns value
		T const & end() const;  //sets pointer curr to the last node and returns value
		T& next();  //sets pointer curr to the next node and returns value; only returns value if at last node
		T const & next() const;  //sets pointer curr to the next node and returns value; only returns value if at last node
		T& prev();  //sets pointer curr to the previous node; only returns value if at first node
		T const & prev() const;  //sets pointer curr to the previous node; only returns value if at first node
		ListNode<T> const* find(const T& val);  //returns a pointer to node with value of T, if in set; returns nullptr otherwise
		void insert(const T& val);  //inserts a value into set; does nothing if value exists in set
		void erase(const T& val);  //erases a value from set; does nothing if value does not exist
		void clear();  //clear the set
		Unordered_Set<T> union_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2);  //returns new union set of 1&2
		Unordered_Set<T> intersect_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2);  //returns new intersect set

	private:
		List<T> setlist;
		ListNode<T>* curr;
};

template <typename T>
Unordered_Set<T>::Unordered_Set() {
	curr = this->setlist.head;
}

template <typename T>
Unordered_Set<T>::~Unordered_Set() {

}

template <typename T>
Unordered_Set<T>::Unordered_Set(const Unordered_Set<T>& other) {
	if (other.size() < 1) {  //counter should never be negative, so only size() == 0 should reach here
		this->setlist.head = nullptr;
		this->setlist.tail = nullptr;
		this->setlist.counter = 0;
		this->curr = this->setlist.head;
	}
	else if (other.size() == 1) {
		T tempval = other.begin();
		this->insert(tempval);
	}
	else {  //for size() > 1
		for (int i = 0; i < other.size(); i++) {
			T tempval = other.setlist.getNodeAt(i)->val;
			this->insert(tempval);
		}
	}
}

template <typename T>
Unordered_Set<T>& Unordered_Set<T>::operator=(const Unordered_Set<T>& other) {
	if (*this == other) {
		return *this;
	}

	if (!this->empty()) {
		this->clear();
	}

	this->setlist = other.setlist;

	return *this;
}

template <typename T>
int Unordered_Set<T>::size() const {
	return this->setlist.size();
}

template <typename T>
bool Unordered_Set<T>::empty() const {
	return this->setlist.empty();
}

template <typename T>
T& Unordered_Set<T>::begin() {
	curr = this->setlist.head;

	return curr->val;
}

template <typename T>
T const & Unordered_Set<T>::begin() const {
	curr = this->setlist.head;

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::end() {
	curr = this->setlist.tail;

	return curr->val;
}

template <typename T>
T const & Unordered_Set<T>::end() const {
	curr = this->setlist.tail;

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::next() {
	if (curr == nullptr) {
		curr = this->setlist.head;
	}

	if (curr != this->setlist.tail) {
		curr = curr->next;
	}

	return curr->val;
}

template <typename T>
T const & Unordered_Set<T>::next() const {
	if (curr == nullptr) {
		curr = this->setlist.head;
	}

	if (curr != this->setlist.tail) {
		curr = curr->next;
	}

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::prev() {
	if (curr == nullptr) {
		curr = this->setlist.tail;
	}

	if (curr != this->setlist.head) {
		curr = curr->prev;
	}

	return curr->val;
}

template <typename T>
T const & Unordered_Set<T>::prev() const {
	if (curr == nullptr) {
		curr = this->setlist.tail;
	}

	if (curr != this->setlist.head) {
		curr = curr->prev;
	}

	return curr->val;
}

template <typename T>
ListNode<T> const* Unordered_Set<T>::find(const T& val) {
	if (this->empty()) {  //throws exception if set is empty
		throw ListException(true, 0);
	}

	for (int i = 0; i < this->size(); i++) {
		ListNode<T>* temp = this->setlist.getNodeAt(i);
		if (temp->val == val) {
			return temp;
		}
	}

	return nullptr;  //if val is not found in set
}

template <typename T>
void Unordered_Set<T>::insert(const T& val) {
	ListNode<T>* temp = this->find(val);

	if (temp == nullptr) {
		this->setlist.push_back(val);
	}
}

template <typename T>
void Unordered_Set<T>::erase(const T& val) {
	if (this->empty()) {  //throws exception if set is empty
		throw ListException(true, 0);
	}

	for (int i = 0; i < this->size(); i++) {
		ListNode<T>* temp = this->setlist.getNodeAt(i);
		if (temp->val == val) {
			this->setlist.erase(i);
			return;
		}
	}
}

template <typename T>
void Unordered_Set<T>::clear() {
	this->setlist.clear();
}

template <typename T>
Unordered_Set<T> Unordered_Set<T>::union_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2) {
	Unordered_Set<T> newSet;
	bool empty1 = set1.empty();
	bool empty2 = set2.empty();

	if (empty1 && empty2) {  //both empty
		return newSet;
	}
	else if (!empty1 && empty2) {  //set2 empty
		newSet = set1;
		return newSet;
	}
	else if (empty1 && !empty2) {  //set1 empty
		newSet = set2;
		return newSet;
	}
	else {  //neither empty
		newSet = set1;
		for (int i = 0; i < set2.size(); i++) {
			T tempval = set2.setlist.getNodeAt(i)->val;
			newSet.insert(tempval);
		}
	}

	return newSet;
}

template <typename T>
Unordered_Set<T> Unordered_Set<T>::intersect_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2) {
	Unordered_Set<T> newSet;
	bool empty1 = set1.empty();
	bool empty2 = set2.empty();

	if (empty1 && empty2) {  //both empty
		return newSet;
	}
	else if (!empty1 && empty2) {  //set2 empty
		return newSet;
	}
	else if (empty1 && !empty2) {  //set1 empty
		return newSet;
	}
	else {  //neither empty
		for (int i = 0; i < set1.size(); i++) {
			T tempval = set1.setlist.getNodeAt(i)->val;
			if (set2.find(tempval) != nullptr) {
				newSet.insert(tempval);
			}
		}
	}

	return newSet;
}
#endif