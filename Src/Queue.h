#pragma once

#include "DoubleLinkedList.h"

template <typename T>
class Queue : public DoubleLinkedList<T> {
	using DoubleLinkedList<T>::first;
	using DoubleLinkedList<T>::removeFirst;
	using DoubleLinkedList<T>::append;
public:
	using DoubleLinkedList<T>::size;
	using DoubleLinkedList<T>::empty;
public:
	virtual ~Queue() {
	}

	virtual T dequeue() {
		T t = first();
		removeFirst();
		return t;
	}

	virtual void enqueue(const T &t) {
		append(t);
	}

	T & head() {
		return first();
	}
	const T & head() const {
		return first();
	}

	char *toString() {
		// for(auto item: size()) {  //begin / end
		// 	
		// }
		//FIXME
		char *buf = new char[32];
		sprintf_s(buf, 32, "Queue(0x%p)", this);
		return buf;
	}
};