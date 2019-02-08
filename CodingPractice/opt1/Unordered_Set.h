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
		ListNode<T> const* begin();  //returns a pointer to the first node
		ListNode<T> const* end();  //returns a pointer to the last node
		void insert(const T& val);  //inserts a value into set; does nothing if value exists in set

	private:
		List<T> setlist;
		ListNode<T> const *curr;
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
	this->setlist = other.setlist;
}

template <typename T>
Unordered_Set<T>& Unordered_Set<T>::operator=(const Unordered_Set<T>& other) {
	if (this == &other) {
		return *this;
	}

	if (!this->empty()) {
		this->setlist.clear();
	}

	for (int i = 0; i < other.size(); i++) {
		this->insert(other.setlist.get(i));
	}

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
#endif