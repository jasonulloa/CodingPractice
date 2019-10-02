#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include "Opt2.h"

Opt2::Opt2() {

}

Opt2::~Opt2() {

}

void Opt2::run() {
	int select = 0;
	bool loop = true;

	std::ostringstream menu;
	menu << "\nOption #2: OpenGL Stuff\n" << std::endl;
	menu << "1. OpenGL Window Test" << std::endl;
	menu << "2. OpenGL View Test" << std::endl;
	menu << "3. OpenGL Raytracer" << std::endl;
	menu << "4. Return to Main Menu" << std::endl << ">";

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
				gl_test();
				break;
			}
			case 2: {
				gl_view_test();
				break;
			}
			case 3: {
				gl_raytracer();
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

void Opt2::gl_test() {
	std::cout << "Testing...." << std::endl;
	GL1::GL1();
	std::cout << "Test complete." << std::endl;
}

void Opt2::gl_view_test() {
	std::cout << "Testing...." << std::endl;
	GL2::GL2();
	std::cout << "Test complete." << std::endl;
}

void Opt2::gl_raytracer() {
	std::string input, name;
	char** scene = new char* [2];
	FILE* sFile;
	std::cout << "Enter *.scene filename:" << std::endl;
	while (std::getline(std::cin, input)) {
		auto result = input.find(".scene");
		if (result != std::string::npos) {  //if find ".scene"
			name = input.substr(0, result);  //strip ".scene" and everything after, just in case
			std::string fname = "..\\external\\scenes\\" + name + ".scene";  //reapply ".scene" and add the file path
			int len = fname.length();
			char* temp = new char[len];
			for (int i = 0; i < len; i++) {
				temp[i] = fname[i];
			}
			temp[len] = '\0';
			fopen_s(&sFile, temp, "r");  //try to open file
			if (sFile != nullptr) {  //if pointer isn't null, then file exists
				scene[0] = scene[1] = temp;
				fclose(sFile);  //don't need the file yet, so close for now
				break;
			}
			std::cout << "\nThat file does not exist." << std::endl;
			std::cout << "Enter *.scene filename:" << std::endl;
		}
	}
	std::cout << "Preparing " << name << ".scene...." << std::endl;
	GL3::GL3(1, scene);
	std::cout << "Scene complete." << std::endl;
}