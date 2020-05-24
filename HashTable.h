#pragma once
#include <string>
#include "Person.h"

class PersonHashTable{
private:
	int size, numItems, numCollisions;
	Person** hashtable;
	int getSumOfDigits(int);
	int bdayToInt(std::string);
	int getHashCode(int);
	bool allTrue(bool*);
	int getNumItems();
	int getCollisions();
	double getLoadFactor();
	Person* operator[](int index);

public:
	PersonHashTable(int);
	~PersonHashTable();
	int getSize();
	void add(Person* per);
	Person* find(std::string);
	friend std::ostream& operator<<(std::ostream& out, PersonHashTable& table);
};