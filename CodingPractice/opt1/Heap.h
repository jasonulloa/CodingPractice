#pragma once
#ifndef HEAP_H
#define HEAP_H
#include <stdexcept>
#include <vector>
#include <functional>

template <typename T, typename Comparator>
class Heap {
	public:
		Heap(int n, Comparator c);  //default constructor for any N-ary heap n >= 2
		~Heap();  //destructor
		Heap(const Heap<T, Comparator>& other);  //copy constructor
		Heap<T, Comparator>& operator=(const Heap<T, Comparator>& other);  //assignment operator
		void push(const T& item);  //adds item to heap
		T const& top() const;  //returns element from top of heap; max, if max-heap, or min, if min-heap
		void pop();  //removes top element from heap
		bool empty() const;  //returns true if heap is empty
		int size();  //returns size of heap
		void clear();  //clears the heap
		void display_heap();  //displays contents of heap

	private:
		std::vector<T> heap;
		int children;
		Comparator comp;
};

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(int n, Comparator c) : children(n), comp(c) {
	if (n < 2) {
		children = 2;
	}
}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap() {}

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(const Heap<T, Comparator>& other) {
	this->children = other.children;
	this->comp = other.comp;

	for (int i = 0; i < other.heap.size(); i++) {
		this->heap[i] = other.heap[i];
	}
}

template <typename T, typename Comparator>
Heap<T, Comparator>& Heap<T, Comparator>::operator=(const Heap<T, Comparator>& other) {
	if (this == &other) {
		return *this;
	}

	if (!this->empty()) {
		this->clear();
	}

	for (int i = 0; i < other.heap.size(); i++) {
		this->heap[i] = other.heap[i];
	}

	return *this;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item) {
	//TODO
}

template <typename T, typename Comparator>
T const& Heap<T, Comparator>::top() const {
	//TODO
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
	//TODO
}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const {
	return heap.empty();
}

template <typename T, typename Comparator>
int Heap<T, Comparator>::size() {
	return heap.size();
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::clear() {
	heap.clear();
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::display_heap() {
	//TODO
}
#endif