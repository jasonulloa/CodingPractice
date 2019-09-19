#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <sstream>
#include <cstring>

template <typename T>
unsigned int hashfunc(const T& val) {  //returns an unsigned int value hashed from input
	std::ostringstream oss;
	oss << val;
	std::string ostr = oss.str();  //converts input to string
	const char* hashstr = ostr.c_str();  //converts string to C-string
	unsigned int hashint = 31;

	while (*hashstr) {  //hash function
		hashint = (hashint * 64013) ^ (hashstr[0] * 52795);
		hashstr++;
	}

	return hashint % 86753;
}

template <typename T>
class Hashtable {
	public:
		Hashtable(int size);  //default constructor
		~Hashtable();  //destructor
		Hashtable(const Hashtable<T>& other);  //copy constructor
		Hashtable<T>& operator=(const Hashtable<T>& other);  //assignment operator
		int size() const;  //returns size of hashtable
		bool empty() const;  //checks if hashtable is empty
		int holds() const;  //returns number of entries in hashtable
		bool find(const T& val);  //returns true if val exists in hashtable
		void insert(const T& val);  //adds value to hashtable; does nothing if value already exists
		void remove(const T& val);  //removes value from hashtable; does nothing if value doesn't exist
		void clear();  //clears the hashtable
		double loadfactor() const;  //returns the current load factor of hashtable
		double max_loadfactor() const;  //returns the current max load factor for hashtable
		void max_loadfactor(double lf);  //sets max load factor for hashtable; default is 0.75

	private:
		void destroy();  //clears and deletes the hashtable
		std::vector<T>* get_vector(int pos) const;  //gets vector at array index pos
		void insert_nosize(const T& val);  //inserts val into hashtable without checking for resizing
		void resize();  //doubles size of hashtable if load surpasses load factor

		std::vector<T>** data;
		int table_size;
		int contains;
		double load_factor;
};

template <typename T>
Hashtable<T>::Hashtable(int size) {
	this->table_size = size;
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
	this->table_size = other.size();
	this->contains = other.holds();
	this->load_factor = other.max_loadfactor();
	data = new std::vector<T>*[this->table_size];

	for (int i = 0; i < this->table_size; i++) {
		data[i] = new std::vector<T>;
		std::vector<T>* othervec = other.get_vector(i);
		for (unsigned int j = 0; j < othervec->size(); j++) {
			T tempval = (*othervec)[j];
			data[i]->emplace_back(tempval);
		}
	}
}

template <typename T>
Hashtable<T>& Hashtable<T>::operator=(const Hashtable<T>& other) {
	if (this == &other) {
		return *this;
	}

	destroy();
	this->table_size = other.size();
	this->contains = other.holds();
	this->load_factor = other.max_loadfactor();
	data = new std::vector<T>*[this->table_size];

	for (int i = 0; i < this->table_size; i++) {
		data[i] = new std::vector<T>;
		std::vector<T>* othervec = other.get_vector(i);
		for (unsigned int i = 0; i < othervec->size(); i++) {
			T tempval = (*othervec)[i];
			data[i]->emplace_back(tempval);
		}
	}

	return *this;
}

template <typename T>
int Hashtable<T>::size() const {
	return table_size;
}

template <typename T>
bool Hashtable<T>::empty() const {
	return contains == 0;
}

template <typename T>
int Hashtable<T>::holds() const {
	return contains;
}

template <typename T>
bool Hashtable<T>::find(const T& val) {
	unsigned int hash = hashfunc(val);
	hash = hash % table_size;

	std::vector<T>* vec = data[hash];
	for (unsigned int i = 0; i < vec->size(); i++) {  //check where val is supposed to be
		T vecval = (*vec)[i];
		if (vecval == val) {
			return true;
		}
	}

	for (int i = 0; i < table_size; i++) {  //check in case val was stored elsewhere
		vec = data[i];
		for (unsigned int i = 0; i < vec->size(); i++) {
			T vecval = (*vec)[i];
			if (vecval == val) {
				return true;
			}
		}
	}

	return false;
}

template <typename T>
void Hashtable<T>::insert(const T& val) {
	if (find(val)) {
		return;
	}

	insert_nosize(val);
	contains++;

	if (loadfactor() >= max_loadfactor()) {
		resize();
	}
}

template <typename T>
void Hashtable<T>::remove(const T& val) {
	if (!find(val)) {
		return;
	}

	unsigned int hash = hashfunc(val);
	hash = hash % table_size;

	std::vector<T>* vec = data[hash];
	for (unsigned int i = 0; i < vec->size(); i++) {
		T vecval = (*vec)[i];
		if (vecval == val) {
			vec->erase(vec->begin() + i);
			break;
		}
	}

	contains--;
}

template <typename T>
void Hashtable<T>::clear() {
	for (int i = 0; i < this->table_size; i++) {
		std::vector<T>* tempvec = data[i];
		tempvec->clear();
	}

	this->contains = 0;
}

template <typename T>
double Hashtable<T>::loadfactor() const {
	double load;
	load = (double)contains / (double)table_size;

	return load;
}

template <typename T>
double Hashtable<T>::max_loadfactor() const {
	return load_factor;
}

template <typename T>
void Hashtable<T>::max_loadfactor(double lf) {
	load_factor = lf;
}

template <typename T>
void Hashtable<T>::destroy() {
	for (int i = 0; i < table_size; i++) {
		delete data[i];
	}

	delete[] data;
}

template <typename T>
std::vector<T>* Hashtable<T>::get_vector(int pos) const {
	return data[pos];
}

template <typename T>
void Hashtable<T>::insert_nosize(const T& val) {
	unsigned int hash = hashfunc(val);
	hash = hash % table_size;
	data[hash]->emplace_back(val);
}

template <typename T>
void Hashtable<T>::resize() {
	std::vector<T>** tempdata;
	int newsize = table_size * 2;
	unsigned int newhash;
	tempdata = new std::vector<T>*[newsize];  //create new hashtable

	for (int i = 0; i < newsize; i++) {
		tempdata[i] = new std::vector<T>;
	}

	for (int i = 0; i < this->table_size; i++) {  //fill new hashtable using new hash
		std::vector<T>* oldvec = this->get_vector(i);
		for (unsigned int i = 0; i < oldvec->size(); i++) {
			T oldval = (*oldvec)[i];
			newhash = hashfunc(oldval);
			newhash = newhash % newsize;
			tempdata[newhash]->emplace_back(oldval);
		}
	}

	this->destroy();  //delete old copy of hashtable
	this->table_size = newsize;
	data = tempdata;  //point to new hashtable
}
#endif