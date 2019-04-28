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
		int size();  //returns size of hashtable
		int holds();  //returns number of entries in hashtable
		float get_loadfactor();  //returns load factor of hashtable
		bool find(const T& val);  //returns true if val exists in hashtable
		void insert(const T& val);  //adds value to hashtable; does nothing if value already exists
		void remove(const T& val);  //removes value from hashtable; does nothing if value doesn't exist
		void resize();  //doubles size of hashtable if load surpasses load factor
		float loadfactor() const;  //returns the current load factor of hashtable
		float max_loadfactor() const;  //returns the current max load factor for hashtable
		void max_loadfactor(float lf);  //sets max load factor for hashtable; default is 0.75

	private:
		void destroy();  //clears and deletes the hashtable
		std::vector<T>* get_vector(int pos);  //gets vector at array index pos

		std::vector<T>** data;
		int size;
		int contains;
		float load_factor;
};

template <typename T>
Hashtable<T>::Hashtable(int size) {
	this->size = size;
	this->contains = 0;
	this->load_factor = 0.75;
	data = new std::vector<T>*[size];

	for (int i = 0; i < size; i++) {
		data[i] = new std::vector<T>;
	}
}

template <typename T>
Hashtable<T>::~Hashtable() {
	destroy();
}

template <typename T>
Hashtable<T>::Hashtable(const Hashtable<T>& other) {
	this->size = other.size();
	this->contains = other.holds();
	this->load_factor = other.get_loadfactor();
	data = new std::vector<T>*[this->size];

	for (int i = 0; i < this->size; i++) {
		data[i] = new std::vector<T>;
		std::vector<T>* othervec = other.get_vector(i);
		for (auto entry : othervec) {
			data[i]->emplace_back(entry);
		}
	}
}

template <typename T>
Hashtable<T>& Hashtable<T>::operator=(const Hashtable<T>& other) {
	if (this == &other) {
		return *this;
	}

	destroy();
	this->size = other.size();
	this->contains = other.holds();
	this->load_factor = other.get_loadfactor();
	data = new std::vector<T>*[this->size];

	for (int i = 0; i < this->size; i++) {
		data[i] = new std::vector<T>;
		std::vector<T>* othervec = other.get_vector(i);
		for (auto entry : othervec) {
			data[i]->emplace_back(entry);
		}
	}

	return *this;
}

template <typename T>
int Hashtable<T>::size() {
	return size;
}

template <typename T>
int Hashtable<T>::holds() {
	return contains;
}

template <typename T>
float Hashtable<T>::get_loadfactor() {
	return load_factor;
}

template <typename T>
bool Hashtable<T>::find(const T& val) {
	unsigned int hash = hashfunc(val);
	hash = hash % size;

	std::vector<T>* vec = data[hash];
	for (auto entry : vec) {  //check where val is supposed to be
		if (entry == val) {
			return true;
		}
	}

	for (int i = 0; i < size; i++) {  //check in case val was stored elsewhere
		vec = data[i];
		for (auto entry : vec) {
			if (entry == val) {
				return true;
			}
		}
	}

	return false;
}

template <typename T>
void Hashtable<T>::insert(const T& val) {
	//TODO
}

template <typename T>
void Hashtable<T>::remove(const T& val) {
	//TODO
}

template <typename T>
void Hashtable<T>::resize() {
	//TODO
}

template <typename T>
float Hashtable<T>::loadfactor() const {
	float load;
	//TODO

	return load;
}

template <typename T>
float Hashtable<T>::max_loadfactor() const {
	return load_factor;
}

template <typename T>
void Hashtable<T>::max_loadfactor(float lf) {
	load_factor = lf;
}

template <typename T>
void Hashtable<T>::destroy() {
	for (int i = 0; i < size; i++) {
		delete data[i];
	}

	delete[] data;
}

template <typename T>
std::vector<T>* Hashtable<T>::get_vector(int pos) {
	return data[pos];
}
#endif