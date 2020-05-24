#pragma once

#include "SinglyLinkedList.h"

template<class T>
class Queue : protected SinglyLinkedList<T>
{
public:
	Queue();
	void enqueue(T*);
	T dequeue();
	T* front();
	T* rear();
	bool empty();
};

/* Creates an empty Queue object.
 * Pre: None
 * Post: Inherited sort member is set to UNSORTED by default */
template<class T>
Queue<T>::Queue() { SinglyLinkedList<T>::sort = UNSORTED; }

/* Adds a new value to the queue's rear.
 * Pre: Queue exists
 * Post: A new element is added to the queue */
template<class T>
void Queue<T>::enqueue(T* value) { SinglyLinkedList<T>::add(value); }

/* Removes an element from the queue's head.
 * Pre: Queue exists
 * Post: Returns true if element is removed successfully */
template<class T>
T Queue<T>::dequeue() { 
	T returnVal = *((SinglyLinkedList<T>::head)->getVal());
	SinglyLinkedList<T>::remove(*((SinglyLinkedList<T>::head)->getVal())); 
	return returnVal;
}

/* Returns the value at the queue's head.
 * Pre: Queue exists
 * Post: Returns a pointer to the value in the head node. */
template<class T>
T* Queue<T>::front() { return (SinglyLinkedList<T>::head)->getVal(); }

/* Returns the value at the queue's tail.
 * Pre: Queue exists
 * Post: Returns a pointer to the value in the tail node. */
template<class T>
T* Queue<T>::rear() { return (SinglyLinkedList<T>::tail)->getVal(); }

/* Returns if the queue is empty or not.
 * Pre: Queue exists
 * Post: Returns false if the head pointer point to anything and true otherwise */
template<class T>
bool Queue<T>::empty() { return SinglyLinkedList<T>::head == nullptr; };


