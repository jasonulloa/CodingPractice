#include <iostream>
#include "Opt1.h"

Opt1::Opt1() {

}

Opt1::~Opt1() {

}

void Opt1::run() {
	int select = 0;
	bool loop = true;

	std::ostringstream menu;
	menu << "\nOption #1: Data Structure Test Runs\n" << std::endl;
	menu << "1. Doubly Linked List Tests" << std::endl;
	menu << "2. Unordered Set Tests" << std::endl;
	menu << "3. Hashtable Tests" << std::endl;
	menu << "4. N-ary Heap Tests" << std::endl;
	menu << "5. Return to Main Menu" << std::endl << ">";

	while (loop) {  //loop until "Exit" is selected
		std::cout << menu.str();

		std::string input;
		while (std::getline(std::cin, input)) {  //read user input
			std::stringstream ss(input);
			if (ss >> select) {  //if the input is an int
				if (ss.eof()) {  //escape input loop if input is only an int
					break;
				}
			}
			std::cout << "Please make a valid selection." << std::endl << ">";
		}  //escape input loop

		switch (select) {
			case 1: {
				list_test();
				break;
			}
			case 2: {
				set_test();
				break;
			}
			case 3: {
				ht_test();
				break;
			}
			case 4: {
				heap_test();
				break;
			}
			case 5: {
				std::cout << "Returning to Main Menu.\n" << std::endl;
				loop = false;
				break;
			}
			default: {
				std::cout << "That option does not exist.\n" << std::endl;
				break;
			}
		}
	}  //escape main loop
}

void Opt1::list_test() {
	std::cout << "\nDoubly Linked List Tests\n" << std::endl;

	std::cout << "List Creation/Deletion:\n" << std::endl;
	List<int>* intlist1 = new List<int>();
	std::cout << "List created.\nintlist1 is empty: " << std::boolalpha << intlist1->empty() << std::endl;
	std::cout << "Adding numbers 1-10." << std::endl;
	for (int i = 1; i <= 10; i++) {
		intlist1->push_back(i);
	}
	std::cout << "intlist1 is empty: " << std::boolalpha << intlist1->empty() << std::endl;
	intlist1->print_list();
	std::cout << "Copy creating list....";
	List<int>* intlist2 = new List<int>(*intlist1);
	std::cout << "List created.\nintlist2 is empty: " << std::boolalpha << intlist2->empty() << std::endl;
	intlist2->print_list();
	std::cout << "Creating new list....";
	List<int>* intlist3 = new List<int>();
	std::cout << "List created.\nintlist3 is empty: " << std::boolalpha << intlist3->empty() << std::endl;
	std::cout << "Set *intlist3 = *intlist1....";
	*intlist3 = *intlist1;
	std::cout << "List changed.\nintlist3 is empty: " << std::boolalpha << intlist3->empty() << std::endl;
	intlist3->print_list();
	std::cout << "Adding 55 to intlist1." << std::endl;
	intlist1->push_back(55);
	std::cout << "For intlist1: ";
	intlist1->print_list();
	std::cout << "For intlist3: ";
	intlist3->print_list();
	std::cout << "Removing 55 from intlist1." << std::endl;
	intlist1->pop_back();
	intlist3->clear();
	std::cout << "intlist3 cleared.\nintlist3 is empty: " << std::boolalpha << intlist3->empty() << std::endl;
	delete intlist3;
	std::cout << "intlist3 deleted. ";
	delete intlist2;
	std::cout << "intlist2 deleted.\n" << std::endl;

	std::cout << "List Manipulation:\n" << std::endl;
	std::cout << "Popping front and back." << std::endl;
	intlist1->pop_front();
	intlist1->pop_back();
	intlist1->print_list();
	std::cout << "Pushing 100 to front and 0 to back." << std::endl;
	intlist1->push_front(100);
	intlist1->push_back(0);
	intlist1->print_list();
	std::cout << "Erasing 3 from third position." << std::endl;
	intlist1->erase(2);
	intlist1->print_list();
	std::cout << "Inserting 3 between 8 and 9 (third from end)." << std::endl;
	intlist1->insert(intlist1->size() - 2, 3);
	intlist1->print_list();
	std::cout << "Changing 6 to 1." << std::endl;
	intlist1->set(4, 1);
	intlist1->print_list();
	std::cout << "Swaping 2 and 9." << std::endl;
	intlist1->swap(1, intlist1->size() - 2);
	intlist1->print_list();
	std::cout << "Reversing the list." << std::endl;
	intlist1->reverse();
	intlist1->print_list();

	std::cout << "\nEnd of tests." << std::endl;
	delete intlist1;
}

void Opt1::set_test() {
	std::cout << "\nUnordered Set Tests\n" << std::endl;

	std::cout << "Unordered Set Creation/Deletion:\n" << std::endl;
	Unordered_Set<int>* intset1 = new Unordered_Set<int>();
	std::cout << "Set created.\nintset1 is empty: " << std::boolalpha << intset1->empty() << std::endl;
	std::cout << "Adding numbers 1-10." << std::endl;
	for (int i = 1; i <= 10; i++) {
		intset1->insert(i);
	}
	std::cout << "intset1 is empty: " << std::boolalpha << intset1->empty() << std::endl;
	intset1->print_set();
	std::cout << "Copy creating set....";
	Unordered_Set<int>* intset2 = new Unordered_Set<int>(*intset1);
	std::cout << "Set created.\nintset2 is empty: " << std::boolalpha << intset2->empty() << std::endl;
	intset2->print_set();
	std::cout << "Creating new set....";
	Unordered_Set<int>* intset3 = new Unordered_Set<int>();
	std::cout << "Set created.\nintset3 is empty: " << std::boolalpha << intset3->empty() << std::endl;
	std::cout << "Set *intset3 = *intset1....";
	*intset3 = *intset1;
	std::cout << "Set changed.\nintset3 is empty: " << std::boolalpha << intset3->empty() << std::endl;
	intset3->print_set();
	std::cout << "Adding 55 to intset1." << std::endl;
	intset1->insert(55);
	std::cout << "For intset1: ";
	intset1->print_set();
	std::cout << "For intset3: ";
	intset3->print_set();
	std::cout << "Removing 55 from intset1." << std::endl;
	intset1->erase(55);
	intset3->clear();
	std::cout << "intset3 cleared.\nintset3 is empty: " << std::boolalpha << intset3->empty() << std::endl;
	delete intset3;
	std::cout << "intset3 deleted. ";
	delete intset2;
	std::cout << "intset2 deleted.\n" << std::endl;

	std::cout << "Set Manipulation:\n" << std::endl;
	std::cout << "Adding unique and non-unique values to set." << std::endl;
	std::cout << "Inserting 42." << std::endl;
	intset1->insert(42);
	intset1->print_set();
	std::cout << "Inserting 5." << std::endl;
	intset1->insert(5);
	intset1->print_set();
	std::cout << "Removing existing element: 1." << std::endl;
	intset1->erase(1);
	intset1->print_set();
	std::cout << "Removing non-existing element: 23." << std::endl;
	intset1->erase(23);
	intset1->print_set();
	std::cout << "99 is in intset1: " << std::boolalpha << (intset1->find(99) != nullptr) << std::endl;
	std::cout << "3 is in intset1: " << std::boolalpha << (intset1->find(3) != nullptr) << std::endl;
	std::cout << "Moving curr pointer and returning curr's values." << std::endl;
	std::cout << "The last node is: " << intset1->end() << std::endl;
	std::cout << "The first node is: " << intset1->begin() << std::endl;
	std::cout << "intset1's curr currently points to: " << intset1->now() << std::endl;
	std::cout << "The next node is: " << intset1->next() << std::endl;
	std::cout << "The next node is: " << intset1->next() << std::endl;
	std::cout << "The next node is: " << intset1->next() << std::endl;
	std::cout << "The previous node is: " << intset1->prev() << std::endl;
	std::cout << "The previous node is: " << intset1->prev() << std::endl;
	std::cout << "The previous node is: " << intset1->prev() << "\n" << std::endl;

	std::cout << "Unioning and Intersecting Sets:\n" << std::endl;
	std::cout << "Creating new empty set....";
	Unordered_Set<int>* intset4 = new Unordered_Set<int>();
	std::cout << "Set created.\nintset4 is empty: " << std::boolalpha << intset4->empty() << std::endl;
	std::cout << "Creating union of non-empty set with an empty set." << std::endl;
	Unordered_Set<int>* intset5 = new Unordered_Set<int>();
	intset5->union_set(*intset1, *intset4);
	intset5->print_set();
	intset5->clear();
	std::cout << "intset5 cleared.\nintset5 is empty: " << std::boolalpha << intset5->empty() << std::endl;
	std::cout << "Inserting numbers into set....";
	intset5->insert(23);
	intset5->insert(-11);
	intset5->insert(35);
	intset5->insert(2);
	intset5->insert(69);
	intset5->insert(8);
	intset5->insert(5);
	std::cout << "Done.\nintset5 is empty: " << std::boolalpha << intset5->empty() << std::endl;
	intset5->print_set();
	intset1->print_set();
	Unordered_Set<int>* intset6 = new Unordered_Set<int>();
	std::cout << "Set created.\nintset6 is empty: " << std::boolalpha << intset6->empty() << std::endl;
	std::cout << "Unioning two non-empty sets." << std::endl;
	intset6->union_set(*intset1, *intset5);
	intset6->print_set();
	intset6->clear();
	std::cout << "intset6 cleared.\nintset6 is empty: " << std::boolalpha << intset6->empty() << std::endl;
	std::cout << "Intersecting non-empty set with an empty set." << std::endl;
	intset6->intersect_set(*intset1, *intset4);
	try {
		intset6->print_set();
	}
	catch (ListException le) {
		std::cout << le.what();
	}
	std::cout << "Intersecting two non-empty sets." << std::endl;
	intset6->intersect_set(*intset1, *intset5);
	intset6->print_set();

	std::cout << "\nEnd of tests." << std::endl;
	delete intset1;
	delete intset4;
	delete intset5;
	delete intset6;
}

void Opt1::ht_test() {
	std::cout << "\nHashtable Tests\n" << std::endl;

	std::cout << "Hashtable Creation/Deletion:\n" << std::endl;
	Hashtable<int>* ht1 = new Hashtable<int>(10);
	std::cout << "Hashtable of size 10 created.\nht1 is empty: " << std::boolalpha << ht1->empty() << std::endl;
	std::cout << "Adding 5 random integers." << std::endl;
	ht1->insert(42);
	ht1->insert(19);
	ht1->insert(86);
	ht1->insert(5);
	ht1->insert(27);
	std::cout << "ht1 is empty: " << std::boolalpha << ht1->empty() << std::endl;
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "Copy creating hashtable....";
	Hashtable<int>* ht2 = new Hashtable<int>(*ht1);
	std::cout << "Hashtable created.\nht2 is empty: " << std::boolalpha << ht2->empty() << std::endl;
	std::cout << "Checking integers...." << std::endl;
	std::cout << "Hashtable contains 5: " << std::boolalpha << ht2->find(5) << std::endl;
	std::cout << "Hashtable contains 19: " << std::boolalpha << ht2->find(19) << std::endl;
	std::cout << "Hashtable contains 27: " << std::boolalpha << ht2->find(27) << std::endl;
	std::cout << "Hashtable contains 42: " << std::boolalpha << ht2->find(42) << std::endl;
	std::cout << "Hashtable contains 69: " << std::boolalpha << ht2->find(69) << std::endl;
	std::cout << "Hashtable contains 86: " << std::boolalpha << ht2->find(86) << std::endl;
	std::cout << "Creating new hashtable of size 25....";
	Hashtable<int>* ht3 = new Hashtable<int>(25);
	std::cout << "Hashtable created.\nht3 is empty: " << std::boolalpha << ht3->empty() << std::endl;
	std::cout << "ht3 has " << ht3->holds() << " integers and has a size of " << ht3->size() << "." << std::endl;
	std::cout << "Set *ht3 = *ht1....";
	*ht3 = *ht1;
	std::cout << "Hashtable changed.\nht3 is empty: " << std::boolalpha << ht3->empty() << std::endl;
	std::cout << "ht3 has " << ht3->holds() << " integers and has a size of " << ht3->size() << "." << std::endl;
	std::cout << "Checking integers...." << std::endl;
	std::cout << "Hashtable contains 5: " << std::boolalpha << ht3->find(5) << std::endl;
	std::cout << "Hashtable contains 19: " << std::boolalpha << ht3->find(19) << std::endl;
	std::cout << "Hashtable contains 27: " << std::boolalpha << ht3->find(27) << std::endl;
	std::cout << "Hashtable contains 42: " << std::boolalpha << ht3->find(42) << std::endl;
	std::cout << "Hashtable contains 69: " << std::boolalpha << ht3->find(69) << std::endl;
	std::cout << "Hashtable contains 86: " << std::boolalpha << ht3->find(86) << std::endl;
	std::cout << "Inserting 55 to ht1." << std::endl;
	ht1->insert(55);
	std::cout << "Hashtable h1 contains 55: " << std::boolalpha << ht1->find(55) << std::endl;
	std::cout << "Hashtable h3 contains 55: " << std::boolalpha << ht3->find(55) << std::endl;
	std::cout << "Removing 55 from ht1." << std::endl;
	ht1->remove(55);
	ht3->clear();
	std::cout << "ht3 cleared.\nht3 is empty: " << std::boolalpha << ht3->empty() << std::endl;
	std::cout << "Checking integers...." << std::endl;
	std::cout << "Hashtable contains 5: " << std::boolalpha << ht3->find(5) << std::endl;
	std::cout << "Hashtable contains 19: " << std::boolalpha << ht3->find(19) << std::endl;
	std::cout << "Hashtable contains 27: " << std::boolalpha << ht3->find(27) << std::endl;
	std::cout << "Hashtable contains 42: " << std::boolalpha << ht3->find(42) << std::endl;
	std::cout << "Hashtable contains 55: " << std::boolalpha << ht3->find(55) << std::endl;
	std::cout << "Hashtable contains 86: " << std::boolalpha << ht3->find(86) << std::endl;
	delete ht3;
	std::cout << "ht3 deleted. ";
	delete ht2;
	std::cout << "ht2 deleted.\n" << std::endl;

	std::cout << "Hashtable Manipulation:\n" << std::endl;
	std::cout << "Adding unique and non-unique values to hashtable." << std::endl;
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "Inserting 30." << std::endl;
	ht1->insert(30);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "Inserting 5." << std::endl;
	ht1->insert(5);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "Removing existing element: 19." << std::endl;
	ht1->remove(19);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "Removing non-existing element: 23." << std::endl;
	ht1->remove(23);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "The current max load factor is: " << ht1->max_loadfactor() << "." << std::endl;
	std::cout << "Changing max load factor to 0.95..." << std::endl;
	ht1->max_loadfactor(0.95);
	std::cout << "The current max load factor is: " << ht1->max_loadfactor() << "." << std::endl;
	std::cout << "Changing max load factor back to 0.75...\n" << std::endl;
	ht1->max_loadfactor(0.75);

	std::cout << "Hashtable Automatic Resizing:\n" << std::endl;
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "The current max load factor is: " << ht1->max_loadfactor() << "." << std::endl;
	std::cout << "The current load factor is: " << ht1->loadfactor() << "." << std::endl;
	std::cout << "Inserting 91." << std::endl;
	ht1->insert(91);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "The current load factor is: " << ht1->loadfactor() << "." << std::endl;
	std::cout << "Inserting 12." << std::endl;
	ht1->insert(12);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "The current load factor is: " << ht1->loadfactor() << "." << std::endl;
	std::cout << "Inserting 64." << std::endl;
	ht1->insert(64);
	std::cout << "ht1 has " << ht1->holds() << " integers and has a size of " << ht1->size() << "." << std::endl;
	std::cout << "The current load factor is: " << ht1->loadfactor() << "." << std::endl;
	std::cout << "Hashtable contains 5: " << std::boolalpha << ht1->find(5) << std::endl;
	std::cout << "Hashtable contains 12: " << std::boolalpha << ht1->find(12) << std::endl;
	std::cout << "Hashtable contains 27: " << std::boolalpha << ht1->find(27) << std::endl;
	std::cout << "Hashtable contains 30: " << std::boolalpha << ht1->find(30) << std::endl;
	std::cout << "Hashtable contains 42: " << std::boolalpha << ht1->find(42) << std::endl;
	std::cout << "Hashtable contains 64: " << std::boolalpha << ht1->find(64) << std::endl;
	std::cout << "Hashtable contains 86: " << std::boolalpha << ht1->find(86) << std::endl;
	std::cout << "Hashtable contains 91: " << std::boolalpha << ht1->find(91) << std::endl;

	std::cout << "\nEnd of tests." << std::endl;
	delete ht1;
}

void Opt1::heap_test() {
	std::cout << "\nN-ary Heap Tests\n" << std::endl;

	std::cout << "N-ary Heap Creation/Deletion:\n\n3-ary Max-Heap:\n" << std::endl;
	Heap<int, std::greater<int> >* max3heap1 = new Heap<int, std::greater<int> >(3, std::greater<int>());
	std::cout << "3-ary Max-Heap created.\nmax3heap1 is empty: " << std::boolalpha << max3heap1->empty() << std::endl;
	std::cout << "Adding 15 random integers....";
	max3heap1->push(42);
	max3heap1->push(19);
	max3heap1->push(86);
	max3heap1->push(5);
	max3heap1->push(27);
	max3heap1->push(51);
	max3heap1->push(25);
	max3heap1->push(30);
	max3heap1->push(12);
	max3heap1->push(93);
	max3heap1->push(8);
	max3heap1->push(41);
	max3heap1->push(69);
	max3heap1->push(77);
	max3heap1->push(55);
	std::cout << "Done.\nmax3heap1 is empty: " << std::boolalpha << max3heap1->empty() << std::endl;
	std::cout << "Max value is: " << max3heap1->top() << std::endl;
	std::cout << "Displaying heap contents:" << std::endl;
	max3heap1->display_heap();
	std::cout << "Copy creating heap....";
	Heap<int, std::greater<int> >* max3heap2 = new Heap<int, std::greater<int> >(*max3heap1);
	std::cout << "Done.\nmax3heap2 is empty: " << std::boolalpha << max3heap2->empty() << std::endl;
	std::cout << "Max value is: " << max3heap2->top() << std::endl;
	std::cout << "Displaying heap contents:" << std::endl;
	max3heap2->display_heap();
	std::cout << "Adding 137 to max3heap1...." << std::endl;
	max3heap1->push(137);
	std::cout << "Displaying both heap contents:" << std::endl;
	std::cout << "max3heap1:" << std::endl;
	max3heap1->display_heap();
	std::cout << "max3heap2:" << std::endl;
	max3heap2->display_heap();
	std::cout << "Creating new heap....";
	Heap<int, std::greater<int> >* max3heap3 = new Heap<int, std::greater<int> >(3, std::greater<int>());
	std::cout << "Done.\nmax3heap3 is empty: " << std::boolalpha << max3heap3->empty() << std::endl;
	std::cout << "Set *max3heap3 = *max3heap1....";
	*max3heap3 = *max3heap1;
	std::cout << "Heap changed.\nmax3heap3 is empty: " << std::boolalpha << max3heap3->empty() << std::endl;
	std::cout << "Displaying heap contents:" << std::endl;
	max3heap3->display_heap();
	std::cout << "Popping top value....";
	max3heap3->pop();
	std::cout << "Done.\nDisplaying heap contents:" << std::endl;
	max3heap3->display_heap();
	std::cout << "Deleting max3heap1, max3heap2, and max3heap3....";
	delete max3heap1;
	delete max3heap2;
	delete max3heap3;
	std::cout << "Done.\nCreating vector of 30 random integers....";
	std::vector<int> randvec;
	randvec.push_back(42);
	randvec.push_back(19);
	randvec.push_back(86);
	randvec.push_back(5);
	randvec.push_back(27);
	randvec.push_back(51);
	randvec.push_back(25);
	randvec.push_back(30);
	randvec.push_back(12);
	randvec.push_back(93);
	randvec.push_back(8);
	randvec.push_back(41);
	randvec.push_back(69);
	randvec.push_back(77);
	randvec.push_back(55);
	randvec.push_back(18);
	randvec.push_back(108);
	randvec.push_back(32);
	randvec.push_back(75);
	randvec.push_back(116);
	randvec.push_back(65);
	randvec.push_back(97);
	randvec.push_back(101);
	randvec.push_back(112);
	randvec.push_back(4);
	randvec.push_back(11);
	randvec.push_back(83);
	randvec.push_back(90);
	randvec.push_back(23);
	randvec.push_back(88);
	std::cout << "Done.\n\n4-ary Min-Heap:\n" << std::endl;
	Heap<int, std::less<int> >* min4heap1 = new Heap<int, std::less<int> >(4, std::less<int>());
	std::cout << "4-ary Min-Heap created.\nmin4heap1 is empty: " << std::boolalpha << min4heap1->empty() << std::endl;
	std::cout << "Adding vector of integers....";
	min4heap1->push_vector(randvec);
	std::cout << "Done.\nmin4heap1 is empty: " << std::boolalpha << min4heap1->empty() << std::endl;
	std::cout << "Min value is: " << min4heap1->top() << std::endl;
	std::cout << "Displaying heap contents:" << std::endl;
	min4heap1->display_heap();
	std::cout << "Deleting min4heap1....";
	delete min4heap1;
	std::cout << "Done.\n\nDefault Binary Max-Heap:\n" << std::endl;
	Heap<int, std::greater<int> >* default_binheap = new Heap<int, std::greater<int> >(-7, std::greater<int>());
	std::cout << "-7 not valid; defaulting to 2. Binary Max Heap created.\ndefault_binheap is empty: ";
	std::cout << std::boolalpha << default_binheap->empty() << std::endl;
	std::cout << "Adding vector of integers....";
	default_binheap->push_vector(randvec);
	std::cout << "Done.\ndefault_binheap is empty: " << std::boolalpha << default_binheap->empty() << std::endl;
	std::cout << "Max value is: " << default_binheap->top() << std::endl;
	std::cout << "Displaying heap contents:" << std::endl;
	default_binheap->display_heap();

	std::cout << "\nHeap Manipulation:\n\nPopping 5 values....";
	for (int i = 0; i < 5; i++) {
		default_binheap->pop();
	}
	
	std::cout << "Done.\nAdding 10 random values....";
	default_binheap->push(51);
	default_binheap->push(127);
	default_binheap->push(81);
	default_binheap->push(79);
	default_binheap->push(10);
	default_binheap->push(105);
	default_binheap->push(99);
	default_binheap->push(82);
	default_binheap->push(141);
	default_binheap->push(96);
	std::cout << "Done.\nMax value is: " << default_binheap->top() << std::endl;
	std::cout << "Displaying heap contents:" << std::endl;
	default_binheap->display_heap();

	std::cout << "\nEnd of tests." << std::endl;
	delete default_binheap;
}