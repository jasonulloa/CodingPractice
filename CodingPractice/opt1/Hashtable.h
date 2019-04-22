#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <sstream>

template <typename T>
unsigned int hashfunc(const T& val) {  //returns an unsigned int value hashed from input
	std::ostringstream oss;
	oss << val;
	std::string ostr = oss.str();  //converts input to string
	char* hashstr = new char[ostr.length() + 1];
	int hashlen = ostr.copy(hashstr, std::string::npos);  //converts string to C-string
	hashstr[hashlen] = '\0';  //null-terminates C-string
	unsigned int hashint = 31;

	while (*hashstr) {  //hash function
		hashint = (hashint * 64013) ^ (hashstr[0] * 52795);
		hashstr++;
	}

	delete hashstr;
	return hashint % 86753;
}

template <typename T>
class Hashtable {
	public:
		Hashtable(int size);  //default constructor
		~Hashtable();  //destructor
		Hashtable(const Hashtable<T>& other);  //copy constructor
		Hashtable<T>& operator=(const Hashtable<T>& other);  //assignment operator
		//TODO

	private:
		std::vector<T>** data;
		int size;
};

template <typename T>
Hashtable<T>::Hashtable(int size) {
	//TODO
}

template <typename T>
Hashtable<T>::~Hashtable() {
	//TODO
}

template <typename T>
Hashtable<T>::Hashtable(const Hashtable<T>& other) {
	//TODO
}

template <typename T>
Hashtable<T>::operator=(const Hashtable<T>& other) {
	//TODO

	return *this;
}
#endif