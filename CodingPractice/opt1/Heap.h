#pragma once
#ifndef HEAP_H
#define HEAP_H
#include <stdexcept>
#include <vector>
#include <functional>
#include <utility>

class HeapException : public std::exception {
private:
	bool emptyHeap;
public:
	HeapException(bool b) {
		emptyHeap = b;
	}

	std::string what() {
		if (emptyHeap) {
			std::string message = "HeapException: The heap is empty.\n";

			return message;
		}
		std::string message = "HeapException: The heap only supports min-heap and max-heap operations.\n";

		return message;
	}
};

template <typename T, typename Comparator>
class Heap {
	public:
		Heap(int n, Comparator c);  //default constructor for any N-ary heap n >= 2
		~Heap();  //destructor
		Heap(const Heap<T, Comparator>& other);  //copy constructor
		Heap<T, Comparator>& operator=(const Heap<T, Comparator>& other);  //assignment operator
		void push(const T& item);  //adds item to heap
		void push_vector(const std::vector<T>& vec);  //adds vector of items to heap
		T const& top() const;  //returns element from top of heap; max, if max-heap, or min, if min-heap
		void pop();  //removes top element from heap
		bool empty() const;  //returns true if heap is empty
		int size();  //returns size of heap
		void clear();  //clears the heap
		void display_heap();  //displays contents of heap

	private:
		void heapify(int pos);  //recursive function that ensures elements adhere to properties of heap
		void bubble_up(int pos);  //insert function that ensures elements adhere to properties of heap
		void trickle_down(int pos);  //remove function that ensures elements adhere to properties of heap
		std::vector<T> heap;
		int children;
		Comparator comp;  //will be std::less<T> for min-heap or std::greater<T> for max-heap
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

	for (unsigned int i = 0; i < other.heap.size(); i++) {
		this->heap.emplace_back(other.heap[i]);
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

	this->children = other.children;
	this->comp = other.comp;

	for (unsigned int i = 0; i < other.heap.size(); i++) {
		this->heap.emplace_back(other.heap[i]);
	}

	this->heapify(this->size() - 1);

	return *this;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item) {
	heap.push_back(item);
	bubble_up(size() - 1);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push_vector(const std::vector<T>& vec) {
	for (auto item : vec) {
		push(item);
	}

	heapify(size() - 1);
}

template <typename T, typename Comparator>
T const& Heap<T, Comparator>::top() const {
	if (empty()) {
		throw HeapException(true);
	}

	return heap[0];
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
	if (empty()) {
		throw HeapException(true);
	}

	std::swap(heap[0], heap[size() - 1]);
	heap.pop_back();
	trickle_down(0);
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
	std::cout << "heap size is " << size() << std::endl;
	std::cout << "0: " << top() << " ||" << std::endl;
	int count = 1, level = 1, last = children;
	while (count < size()) {
		std::cout << count << ": " << heap[count] << ", ";
		if (count == last) {
			std::cout << "||\n";
			level++;
			last += static_cast<int>(pow(children, level));
		}
		count++;
	}
	std::cout << std::endl;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int pos) {
	if (pos < 0) {
		return;
	}

	int top = pos;
	for (int i = 1; i < children; i++) {
		int left = children * pos + i, right = children * pos + i + 1;
		if (left >= size()) {  //if no leaf nodes, don't bother checking
			break;
		}

		if (right < size()) {  //if in range
			top = comp(heap[top], heap[right]) ? top : right;  //the bigger(max)/smaller(min) value index goes to top
		}

		top = comp(heap[top], heap[left]) ? top : left;  //the bigger(max)/smaller(min) value index goes to top
	}

	if (pos != top) {  //if either one switched with top
		std::swap(heap[pos], heap[top]);
		trickle_down(top);
	}

	heapify(pos - 1);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::bubble_up(int pos) {
	if (pos > 0 && comp(heap[pos], heap[(pos - 1) / children])) {
		std::swap(heap[pos], heap[(pos - 1) / children]);
		bubble_up((pos - 1) / children);
	}
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::trickle_down(int pos) {
	int compindex = children * pos + 1;

	for (int i = 1; i < children; i++) {
		if (children * pos + i + 1 < size()) {
			//finds the min/max value among the children of pos
			compindex = comp(heap[compindex], heap[children * pos + i + 1]) ? compindex : children * pos + i + 1;
		}
		else {
			break;
		}
	}

	if (compindex >= size()) {  //out-of-range check
		return;
	}

	if (comp(heap[compindex], heap[pos])) {
		std::swap(heap[pos], heap[compindex]);  //if heap[compindex] is the bigger/smaller value, swap
		trickle_down(compindex);  //check if the leaves of the swapped node also need swapping
	}  //if nothing swapped, no need to check
}
#endif