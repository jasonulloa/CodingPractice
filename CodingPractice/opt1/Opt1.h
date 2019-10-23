#pragma once
#ifndef OPT1_H
#define OPT1_H
#include "Unordered_Set.h"
#include "Hashtable.h"
#include "Heap.h"

class Opt1 {
	public:
		Opt1();
		~Opt1();
		void run();

	private:
		void list_test();
		void set_test();
		void ht_test();
		void heap_test();
};
#endif