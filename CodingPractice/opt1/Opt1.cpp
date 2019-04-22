#include <iostream>
#include <string>
#include <sstream>
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
	menu << "4. Exit" << std::endl << ">";

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
	std::cout << "Got to finish coding the hashtable data structure first.\nThe tests will come later.\n"
		<< std::endl;
}