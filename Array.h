#pragma once
#include <iostream>
template<class T>
class Array
{
	T* arr;
	int len;

public:
	Array(int length);
	//~Array();
	T& operator[](int index);
	int getLen();
	template<class U>
	friend std::ostream& operator<<(std::ostream& out, Array<U>& arr);

};

//Creates an array object of desired type
//Pre: none
//Post:Array of desired object created
template<class T>
Array<T>::Array(int length) {
	len = length;
	arr = new T[len];
}

//Returns item at specified index
//Pre:Array Object exists
//Post: item is returned
template<class T>
T& Array<T>::operator[](int index) {
	return arr[index];
}

//Returns length of array
//Pre:Array Object exists
//Post: length is returned
template<class T>
int Array<T>::getLen()
{
	return len;
}

//Loops through array and outputs all values
//Pre:Array Object exists
//Post: array is printed to the ostream
template<class T>
std::ostream& operator<<(std::ostream& out, Array<T>& arr) {
	for (int i = 0; i < arr.getLen(); i++) {
		out << arr[i] << " ";
	}
	out << std::endl;
	return out;
}