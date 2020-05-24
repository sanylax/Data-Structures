#include "PersonHashTable.h"
//Creates a PersonHashTable of length len
//Pre: None
//Post: PersonHashTable created
PersonHashTable::PersonHashTable(int len) {
	size = len;
	hashtable = new Person*[size];
	for (int i = 0; i < size; i++) {
		hashtable[i] = nullptr;
	}
	
}

//converts the bday string to an int of the same value
//Pre: None
//Post: int is returned
int PersonHashTable::bdayToInt(std::string bday) {
	int number = 0;
	for (int i = 0; i < 4; i++) {
		number += bday[i] - '0';
		number *= 10;
	}
	for (int i = 5; i < 7; i++) {
		number += bday[i] - '0';
		number *= 10;
	}
	for (int i = 8; i < 10; i++) {
		number += bday[i] - '0';
		number *= 10;
	}
	return number/10;

}

//Allows you to directly access the array
//Pre: HashTable exists
//Post: value returned
Person* PersonHashTable::operator[](int index) {
	return hashtable[index];
}

//Returns size of array
//Pre: HashTable exists
//Post: value returned
int PersonHashTable::getSize() {
	return size;
}

//Returns sum of the digits in an int
//Pre: none
//Post: value returned
int PersonHashTable::getSumOfDigits(int x) {
	int sum = 0;
	while (x != 0) {
		sum += x % 10;
		x = x / 10;
	}
	if(sum%10 == 0) sum /= 10;
	return sum;
}

//Returns the hashcode between 0 and 9 corresponding to a bday int
//Pre: HashTable exists
//Post: code returned
int PersonHashTable::getHashCode(int bday) {
	int code = getSumOfDigits(bday);
	while (code > 9) code = getSumOfDigits(code);
	return code;
}
//Returns the number of items added to the array
//Pre: HashTable exists
//Post: value returned
int PersonHashTable::getNumItems() {
	return numItems;
}

//Returns the number of collisions 
//Pre: HashTable exists
//Post: value returned
int PersonHashTable::getCollisions() {
	return numCollisions;
}

//Returns the percent of slots filled in the array
//Pre: HashTable exists
//Post: value returned
double PersonHashTable::getLoadFactor() {
	return (double)numItems/ (double)size;
}

//Adds a number to the array using hashcode
//Using quadratic probing for collision resolution and reverting to linear probing if cyclic hash is detected
//Pre: HashTable exists
//Post: value is added
void PersonHashTable::add(Person* per) {
	int cyclic = 0, cyclicCounter;
	int i = 1;
	int x = bdayToInt(per->getBday());
	int OGcode = getHashCode(bdayToInt(per->getBday()));
	int code = OGcode;
	int prevCode = code;
	if (hashtable[code%size] != nullptr) numCollisions++;
	while (hashtable[code%size] != nullptr) {
		if ((code%size == prevCode % size) && (i > 1)) {
			cyclic++; 
			cyclicCounter = i;
		}

		if (cyclic > 1 && (cyclicCounter - i) < 3) break;
		if(i%2 == 1) prevCode = code;
		code = OGcode + i * i;
		i++;
	}
	//If cyclic hashing happens, revert to linear probe
	if (cyclic > 1) {
		do{
			code ++;
		} while (hashtable[code%size] != nullptr);
		
	}
	hashtable[code%size] = per;
	numItems++;
}

//Returns true if every element in a boolean array is true
//Pre: Array of booleans exists
//Post: bool returned
bool PersonHashTable::allTrue(bool* arr){
	int size = sizeof(arr);
	for (int i = 0; i < size; i++) {
		if (arr[i] == false) return false;
	}
	return true;
}

//Searches the hashtable for a bday
//Follows the same steps as add to search for a value
//Uses an array to keep track of the checked indexes
//If every index has been checked return false
//Pre: Hashtable Exists
//Post: Person object is returned if found or null if not found
Person* PersonHashTable::find(std::string search) {
	int cyclic = 0, cyclicCounter;
	int i = 1;
	int checkCounter = 0;
	bool* indexesChecked = new bool[size];
	for (int i = 0; i < size; i++) indexesChecked[i] = false;
	int x = bdayToInt(search);
	int OGcode = getHashCode(bdayToInt(search));
	int code = OGcode;
	int prevCode = code;
	if (hashtable[code%size]->getBday() == search) return hashtable[code%size];
	while (hashtable[code%size]->getBday() != search) {
		if (indexesChecked[code%size] == false) indexesChecked[code%size] = true;
		if (allTrue(indexesChecked)) return nullptr;
		if ((code%size == prevCode % size) && (i > 1)) {
			cyclic++;
			cyclicCounter = i;
		}

		if (cyclic > 1 && (cyclicCounter - i) < 3) break;
		if (i % 2 == 1) prevCode = code;
		code = OGcode + i * i;
		i++;
		if (hashtable[code%size]->getBday() == search) return hashtable[code%size];
	}
	//If cyclic hashing happens, revert to linear probe
	if (cyclic > 1) {
		do {
			code++;
			if (hashtable[code%size]->getBday() == search) return hashtable[code%size];
			if (indexesChecked[code%size] == false) indexesChecked[code%size] = true;
			if (allTrue(indexesChecked)) return nullptr;
		} while (hashtable[code%size]->getBday() != search);

	}
	return nullptr;
}
//Deletes all objects in the hashtable
//Pre: Hashtable exists
//Post: All elements are deleted
PersonHashTable::~PersonHashTable() {
	for (int i = 0; i < size; i++) {
		if (hashtable[i] != nullptr) delete hashtable[i];
	}

}
//Prints out the values in the array as well as the number of items, collisions, and load factor
//Pre: Hashtable exists
//Post: Values are printed
std::ostream& operator<<(std::ostream& out, PersonHashTable& table) {
	for (int i = 0; i < table.getSize(); i++) {
		if (table[i] == nullptr) out << "[" << i << "] Empty Slot" << std::endl;
		else out  << "[" << i << "] " << *(table[i]) << std::endl;
	}
	out << "Number of items: " << table.getNumItems() << std::endl;
	out << "Collisions: " << table.getCollisions() << std::endl;
	out << "Load Factor: " << table.getLoadFactor()*100 << "%" << std::endl;
	return out;
}