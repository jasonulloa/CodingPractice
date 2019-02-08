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
	menu << "2. Unordered Set Tests (TODO)" << std::endl;
	menu << "3. Exit" << std::endl << ">";

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
				std::cout << "Normally, you'd see some tests run here. However, I haven't finished\n" <<
					"coding them yet. Please wait until then.\n" << std::endl;
				break;
			}
			case 3: {
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