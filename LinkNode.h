#pragma once

template<class T>
class LinkNode
{
private:
	LinkNode* next;
	T* val;

public:
	LinkNode();
	LinkNode(LinkNode<T>*, T*);

	T* getVal();
	LinkNode* getNext();
	void setVal(T*);
	void setNext(LinkNode<T>*);
};

//Creates an empty LinkNode object 
//Pre: none
//Post: Empty LinkNode object created
template<class T>
LinkNode<T>::LinkNode() {
	next = nullptr;
	val = nullptr;
}

//Creates a LinkedNode object 
//Pre: none
//Post: LinkedNode object created with specified values
template<class T>
LinkNode<T>::LinkNode(LinkNode<T>* n, T* v) {
	next = n;
	val = v;
}



//Returns pointer to value of node
//Pre: LinkNode Object exists
//Post: value is returned
template<class T>
T* LinkNode<T>::getVal()
{
	return val;
}

//Returns pointer to next node
//Pre: LinkNode Object exists
//Post: value is returned
template<class T>
LinkNode<T>* LinkNode<T>::getNext()
{
	return next;
}

//Sets pointer to next node
//Pre: LinkNode Object exists
//Post: next is set
template<class T>
void LinkNode<T>::setNext(LinkNode<T>* n)
{
	next = n;
}

//Sets pointer to value of node
//Pre: LinkNode Object exists
//Post: value is set
template<class T>
void LinkNode<T>::setVal(T* v)
{
	val = v;
}




