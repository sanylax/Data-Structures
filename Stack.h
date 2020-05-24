#pragma once
#include "SinglyLinkedList.h"
/*
	Lab 3: Queue1 by Santosh Lakshman and Gokul Nair
*/
template<class T>
class Stack : protected SinglyLinkedList<T> {
public:
	Stack();
	void push(T);
	void push(T*);
	T pop();
	T* peek();
	void empty();
	bool isEmpty();
};


/* Creates an empty Stack object.
 * Pre: None
 * Post: Inherited sort member is set to UNSORTED by default */
template<class T>
Stack<T>::Stack() {
	SinglyLinkedList<T>::sort = UNSORTED;
}




/* Adds a new value to the top of the stack
 * Pre: Stack exists
 * Post: A new element is added to the stack */
template<class T>
void Stack<T>::push(T* value) {
	SinglyLinkedList<T>::add(value);
}

/* Adds a new value to the top of the stack
 * Pre: Stack exists
 * Post: A new element is added to the stack */
template<class T>
void Stack<T>::push(T value) {
	T* x = new T(value);
	SinglyLinkedList<T>::add(x);
}



/* Removes the top element from the stack and returns it
 * Pre: Stack exists
 * Post: Returns true if element is removed successfully */
template<class T>
T Stack<T>::pop() {
	return SinglyLinkedList<T>::removeAt(SinglyLinkedList<T>::count);
}


/* Returns the value at the top of the stack
 * Pre: Stack exists
 * Post: Returns a pointer to the value in the tail node. */
template<class T>
T* Stack<T>::peek() {
	return (SinglyLinkedList<T>::tail)->getVal();
}


/* Returns if the Stack is empty or not.
 * Pre: Stack exists
 * Post: Returns false if the head pointer point to anything and true otherwise */
template<class T>
bool Stack<T>::isEmpty() {
	return SinglyLinkedList<T>::tail == nullptr;
};


/* Empties Stack.
 * Pre: Stack exists
 * Post: Stack is emptied */
template<class T>
void Stack<T>::empty() {
	SinglyLinkedList<T>::empty();
};


