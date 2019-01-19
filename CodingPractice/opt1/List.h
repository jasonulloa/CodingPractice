#pragma once
#ifndef LIST_H
#define LIST_H

template <typename T>
struct ListNode {
	T val;
	ListNode<T>* prev;
	ListNode<T>* next;
};

template <typename T>
class List {
	public:
		List();
		~List();
		ListNode* get(int index);
		void insert(const T& value);
		void insertAt(const T& value, int index);
		void remove(const T& value);
		void removeAt(int index);
		bool find(const T& value);
		bool isEmpty();

	private:
		ListNode<T>* head;
		ListNode<T>* tail;
		int counter;
};
#endif