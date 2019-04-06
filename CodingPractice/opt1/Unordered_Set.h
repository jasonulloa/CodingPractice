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
		T& end();  //sets pointer curr to the last node and returns value
		T& next();  //sets pointer curr to the next node and returns value; only returns value if at last node
		T& prev();  //sets pointer curr to the previous node; only returns value if at first node
		T& now();  //returns value at curr node; returns head node if curr == nullptr
		ListNode<T>* find(const T& val) const;  //returns a pointer to node with value of T, if in set; returns nullptr otherwise
		void insert(const T& val);  //inserts a value into set; does nothing if value exists in set
		void erase(const T& val);  //erases a value from set; does nothing if value does not exist
		void clear();  //clear the set
		void union_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2);  //returns new union set of 1&2
		void intersect_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2);  //returns new intersect set
		void print_set();  //prints the set contents; throws exception if empty

	private:
		List<T> setlist;
		ListNode<T>* curr;
};

template <typename T>
Unordered_Set<T>::Unordered_Set() {
	curr = nullptr;
}

template <typename T>
Unordered_Set<T>::~Unordered_Set() {

}

template <typename T>
Unordered_Set<T>::Unordered_Set(const Unordered_Set<T>& other) {
	if (other.size() < 1) {  //counter should never be negative, so only size() == 0 should reach here
		this->curr = nullptr;
	}
	else if (other.size() == 1) {
		T tempval = other.setlist.get(0);
		this->insert(tempval);
	}
	else {  //for size() > 1
		for (int i = 0; i < other.size(); i++) {
			T tempval = other.setlist.get(i);
			this->insert(tempval);
		}
	}
}

template <typename T>
Unordered_Set<T>& Unordered_Set<T>::operator=(const Unordered_Set<T>& other) {
	if (this == &other) {
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
	curr = this->setlist.headnode();

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::end() {
	curr = this->setlist.tailnode();

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::next() {
	if (curr == nullptr) {
		curr = this->setlist.headnode();
	}

	if (curr != this->setlist.tailnode()) {
		curr = curr->next;
	}

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::prev() {
	if (curr == nullptr) {
		curr = this->setlist.tailnode();
	}

	if (curr != this->setlist.headnode()) {
		curr = curr->prev;
	}

	return curr->val;
}

template <typename T>
T& Unordered_Set<T>::now() {
	if (curr == nullptr) {
		curr = this->setlist.headnode();
	}

	return curr->val;
}

template <typename T>
ListNode<T>* Unordered_Set<T>::find(const T& val) const {
	if (this->empty()) {  //throws exception if set is empty
		throw ListException(true, 0);
	}

	ListNode<T>* temp = this->setlist.headnode();
	for (int i = 0; i < this->size(); i++) {
		T tempval = this->setlist.get(i);
		if (tempval == val) {
			return temp;
		}
		temp = temp->next;
	}

	return nullptr;  //if val is not found in set
}

template <typename T>
void Unordered_Set<T>::insert(const T& val) {
	ListNode<T>* temp = nullptr;
	
	if (!this->empty()) {
		temp = this->find(val);
	}

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
		T tempval = this->setlist.get(i);
		if (tempval == val) {
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
void Unordered_Set<T>::union_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2) {
	Unordered_Set<T> newSet;
	bool empty1 = set1.empty();
	bool empty2 = set2.empty();

	if (empty1 && empty2) {  //both empty
		*this = newSet;
		return;
	}
	else if (!empty1 && empty2) {  //set2 empty
		*this = set1;
		return;
	}
	else if (empty1 && !empty2) {  //set1 empty
		*this = set2;
		return;
	}
	else {  //neither empty
		newSet = set1;
		for (int i = 0; i < set2.size(); i++) {
			T tempval = set2.setlist.get(i);
			newSet.insert(tempval);
		}
	}

	*this = newSet;
}

template <typename T>
void Unordered_Set<T>::intersect_set(const Unordered_Set<T>& set1, const Unordered_Set<T>& set2) {
	Unordered_Set<T> newSet;
	bool empty1 = set1.empty();
	bool empty2 = set2.empty();

	if (empty1 && empty2) {  //both empty
		*this = newSet;
		return;
	}
	else if (!empty1 && empty2) {  //set2 empty
		*this = newSet;
		return;
	}
	else if (empty1 && !empty2) {  //set1 empty
		*this = newSet;
		return;
	}
	else {  //neither empty
		for (int i = 0; i < set1.size(); i++) {
			T tempval = set1.setlist.get(i);
			if (set2.find(tempval) != nullptr) {
				newSet.insert(tempval);
			}
		}
	}

	*this = newSet;
}

template <typename T>
void Unordered_Set<T>::print_set() {
	this->setlist.print_list();
}
#endif