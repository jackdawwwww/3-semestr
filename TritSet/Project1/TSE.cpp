#include<iostream>
#include<cassert>
#include "TSE.h"
#include <string>
#include <algorithm>
using namespace MySetEmulation;

const int capacity_in_chain_element = sizeof(unsigned int) * 4;
const int num_of_bits_in_chain_element = sizeof(unsigned int) * 8;

//
//PRIVATE
//
void Trit_set::raise_chain(size_t size) {
	if (this->tr_chain == nullptr) {
		this->tr_chain = new unsigned int[size];
		this->length = 2 * size / 8 / sizeof(unsigned int) + (size % capacity_in_chain_element != 0);
		this->capacity = size;
		for (size_t i = 0; i<this->length; i++)this->tr_chain[i] = (unsigned int)0;
	}
	else {
		unsigned int* tmp_chain = new unsigned int[size];
		for (size_t i = 2 * size / 8 / sizeof(unsigned int) + 1; i >this->get_length(); i--)tmp_chain[i-1] = (unsigned int)0;
		for (size_t i = 0; i < this->get_length(); i++)tmp_chain[i] = this->tr_chain[i];
		delete[] this->tr_chain;
		this->tr_chain = tmp_chain;
		this->length = 2 * size / 8 / sizeof(unsigned int) + (size % capacity_in_chain_element != 0);
		this->capacity = size;
		return;
	}
}
Trit Trit_set::complete_tr(Trit value)const {
	if (value == True)return False;
	if (value == False)return True;
	return Unknown;
}

//
//PUBLIC
//
Trit_set::Trit_set() :tr_chain(nullptr), length(0), capacity(0) {}
Trit_set::Trit_set(unsigned int size) {
	this->tr_chain = new unsigned int[size];
	this->length= 2 * size /8/sizeof(unsigned int)+(size%capacity_in_chain_element!=0);
	this->capacity = size;
	for (size_t i = 0; i < this->length; i++) this->tr_chain[i] = unsigned int(0);
}
Trit_set::Trit_set(const Trit_set& tr) {
unsigned int* tr_chain = new unsigned int[tr.get_length()];
	for (size_t i = 0; i < tr.get_length(); i++) {
		tr_chain[i] = tr.tr_chain[i];
	}
	this->capacity = tr.get_capacity();
	this->length = tr.get_length();
	this->tr_chain = tr_chain;
}
Trit_set::~Trit_set() {
	if (this->tr_chain != nullptr) {
		delete[] this->tr_chain;
		this->tr_chain = nullptr;
	}
}
size_t Trit_set::get_length() const {
	return this->length;
}
size_t Trit_set::get_capacity() const {
	return this->capacity;
}
void Trit_set::trim(unsigned int last_index) {
	if (!(last_index >= 0 && last_index < this->get_capacity()))return;
	if (last_index == this->get_capacity() - 1)return;
	unsigned int new_length = last_index / capacity_in_chain_element + (last_index % capacity_in_chain_element != 0);
	unsigned int* tmp = new unsigned int[new_length];
	for (size_t i = 0; i < new_length; i++)tmp[i] = this->tr_chain[i];
	delete this->tr_chain;
	this->capacity = last_index + 1;
	this->length = new_length;
	this->tr_chain = tmp;
	return;
}
size_t Trit_set::_length() {
	 int ind = this->get_length();
	for(; ind >0; ind--) {
		if (this->tr_chain[ind-1] != 0) {
			for (int i = capacity_in_chain_element*ind-1; i >=capacity_in_chain_element * (ind-1); i--) {
				if ((*this)[i] != Unknown) {
					return i;
				}
			}
		}
	}
	return 0;
}
void Trit_set::shrink() {
	unsigned int ind = this->_length();
	this->trim(ind);
	return;
}

//
//REFERENCE
//
Trit_set::reference::reference(size_t index, Trit_set* tr) :position(index), parent(tr) {};
Trit_set::reference::~reference() {}

//
//OPERATORS
//
Trit_set::reference Trit_set::operator[](size_t ind) {
	return reference(ind, this);
}

Trit Trit_set::reference::operator=(Trit value) {
	if (value == Unknown && this->position > this->parent->get_capacity())return value;
	if(this->position >=this->parent->get_capacity())this->parent->raise_chain(this->position+1);

	unsigned int ind_in_chain = this->position / capacity_in_chain_element;
	int shift = num_of_bits_in_chain_element - 2 * (this->position % capacity_in_chain_element+1);
	unsigned int deleted_mask = ~(0x03 << shift);
	this->parent->tr_chain[ind_in_chain] &= deleted_mask;
	unsigned int mask =(unsigned int)value << shift;
	this->parent->tr_chain[ind_in_chain] += mask;
	return value;
}

Trit_set::reference::operator Trit()const {
	if (!(this->position < this->parent->get_capacity()) && this->position >= 0)return Unknown;
	unsigned int result = this->parent->tr_chain[this->position / capacity_in_chain_element];
	int shift = (num_of_bits_in_chain_element - 2 * (this->position % capacity_in_chain_element + 1));
	result >>= shift;
	result &= 0x03;
	if (result > 2)return Unknown;
	return (Trit)result;
}
Trit Trit_set::operator[](size_t pos) const {
	if (!(pos < get_capacity() && pos >= 0))return Unknown;
	unsigned int result = this->tr_chain[pos / capacity_in_chain_element];
	int shift = num_of_bits_in_chain_element - 2 * (pos % capacity_in_chain_element + 1);
	result >>= shift;
	result &= 0x03;
	if (result > 2)return Unknown;
	return (Trit)result;
}

Trit_set Trit_set::operator&(const Trit_set& tr) {
	Trit_set tmp(*this);
	if (tr.capacity > tmp.capacity)tmp.raise_chain(tr.capacity);
	tmp.trim(tr.capacity);
	for (size_t i = 0; i < tr.capacity; i++) {
		if (tmp[i] == True) {
			if (tr[i] == Unknown) tmp[i] = Unknown;
			else if (tr[i] == False) tmp[i] = False;
		}
		else if (((*this)[i] == Unknown && tr[i] == False)) tmp[i] = False;
	}
	return tmp;
}
Trit_set Trit_set::operator|(const Trit_set& tr) {
	Trit_set tmp(*this);
	if (tr.capacity > tmp.capacity)tmp.raise_chain(tr.capacity);
	tmp.trim(tr.capacity);
	for (size_t i = 0; i < tr.capacity; i++) {
		if (tmp[i] == False) {
			if (tr[i] == True) tmp[i] = True;
			else if (tr[i] == Unknown)tmp[i] = Unknown;
		}
		else if ((tmp[i] == Unknown && tr[i] == True)) tmp[i] = True;
	}
	return tmp;
}
Trit_set Trit_set::operator!() {
	Trit_set tmp(*this);
	for (size_t i = 0; i < this->get_capacity(); i++) {
		Trit value = tmp[i];
		Trit new_value = complete_tr(value);
		tmp[i] = new_value;
	}
	return tmp;
}
bool Trit_set::operator==(const Trit_set& tr) const {
	if (this->get_capacity() != tr.get_capacity()) return false;
	for (size_t i = 0; i < tr.get_length(); i++) {
		if (this->tr_chain[i] != tr.tr_chain[i]) {
			return false;
		}
	}
	return true;
}
bool Trit_set::operator!=(const Trit_set& tr) const {
	return ((*this) == tr) ? false : true;
}

size_t Trit_set::cardinality(Trit value) {
	size_t result = 0;
	for (size_t i = 0; i < this->get_capacity(); i++) { if ((*this)[i] == value)result++; }
	return result;
}
std::unordered_map<Trit, unsigned int> Trit_set::cardinality() {
	std::unordered_map<Trit, unsigned int>un_map;
	un_map[False] = cardinality(False);
	un_map[Unknown] = cardinality(Unknown);
	un_map[True] = cardinality(True);
	return un_map;
}