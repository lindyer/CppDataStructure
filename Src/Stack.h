#pragma once
#include "Object.h"
#include "Capacity.h"
#include <initializer_list>
#include "Vector.h"

/**
 * \brief 栈
 * \tparam T Any
 */
template <typename T>
class Stack : public Vector<T> {
	using Vector<T>::_count;
public: // virtual void clear() override {
	// 	while (_cursor) {
	// 		Node *node = _cursor;
	// 		_cursor = _cursor->prev;
	// 		delete node;
	// 	}
	// }
	Stack() {}
	Stack(std::initializer_list<T> list): Vector<T>(list) { }

	virtual ~Stack() {
		// clear();
	}

	void push(const T& t) {
		append(t); // Node *n = new Node();
		// n->value = t;
		// n->prev = _cursor;
		// _cursor = n;
		// _count++;
	}

	T pop() {
		// if(_cursor) {
		// 	T t = _cursor->value;
		// 	_cursor = _cursor->prev;
		// 	_count--;
		// 	return t;
		// }
		T t = last();
		removeLast();
		return t;
	}

	T& top() {
		return last(); // return _cursor->value;
	}

	const T& top() const {
		return last(); // return _cursor->value;
	} // private:
	// 	struct Node {
	// 		Node* prev = nullptr;
	// 		T value;
	// 	};
	// 	Node *_cursor = nullptr;
};

template <typename T>
class LinkedStack : public Capacity {
public:
	virtual void clear() override final {
		while (_cursor) {
			Node* node = _cursor;
			_cursor = _cursor->prev;
			delete node;
		}
	}

	LinkedStack() {}
	LinkedStack(std::initializer_list<T> list) {
		for(auto item: list) {
			push(item);
		}
	}

	virtual ~LinkedStack() {
		clear();
	}

	void push(const T& t) {
		Node* n = new Node();
		n->value = t;
		n->prev = _cursor;
		_cursor = n;
		++_count;
	}

	T pop() {
		if (_cursor) {
			T t = _cursor->value;
			_cursor = _cursor->prev;
			--_count;
			return t;
		}
		return T();
	}

	T& top() {
		return _cursor->value;
	}

	const T& top() const {
		return _cursor->value;
	}

	struct Iterator {
		typename LinkedStack<T>::Node *cursor = nullptr;
		bool operator!=(const Iterator &iter) {
			return iter.cursor != cursor;
		}
		void operator++() {
			cursor = cursor->prev;
		}
		T &operator*() {
			return cursor->value;
		}
	};

	struct ConstIterator {
		typename LinkedStack<T>::Node *cursor = nullptr;
		bool operator!=(const ConstIterator &iter) {
			return iter.cursor != cursor;
		}
		void operator++() {
			cursor = cursor->prev;
		}
		const T &operator*() & {
			return cursor->value;
		}
	};

	Iterator begin() {
		Iterator iter;
		iter.cursor = _cursor;
		return iter;
	}

	Iterator end() {
		return Iterator();
	}

	const ConstIterator &begin() const {
		ConstIterator constIter;
		constIter.cursor = _head;
		return constIter;
	}

	const ConstIterator &end() const {
		return ConstIterator();
	}

private:
	struct Node {
		Node* prev = nullptr;
		T value;
	};

	Node* _cursor = nullptr;
};
