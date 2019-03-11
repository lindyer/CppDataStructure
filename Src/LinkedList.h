#pragma once

#include "AbstractList.h"
#include <cassert>
#include <initializer_list>

/**
 * \brief 列表
 * \tparam T Any
 */
template <typename T>
class LinkedList : public AbstractList<T> {
	using AbstractList<T>::_count;
public:
	void clear() override final {
		removeAll();
	}
	LinkedList() = default;
	LinkedList(std::initializer_list<T> list) {
		for (auto item : list) {
			append(item);
		}
	}

	virtual ~LinkedList() override {
		removeAll();
	}

	void prepend(const T & t) override {
		Node *n = new Node();
		n->value = t;
		if (_head) {
			n->next = _head;
		} else {
			_tail = n;
		}
		_head = n;
		_count++;
	}

	void append(const T & t) override {
		Node *n = new Node();
		n->value = t;
		if (_tail) {
			_tail->next = n;
		} else {
			_head = n;
		}
		_tail = n;
		_count++;
	}

	void insert(size_t index, const T & t) override {
		if (index >= _count) {
			append(t);
		} else if (index == 0) {
			prepend(t);
		} else {
			Node *n = new Node();
			n->value = t;
			_count++;
			Node *cursor = _head;
			Node *last = _head;
			while (index--) {
				last = cursor;
				cursor = cursor->next;
			}
			last->next = n;
			n->next = cursor;	
		}
	}

	void removeFirst() override {
		removeAt(0);
	}

	void removeLast() override {
		removeAt(_count - 1);
	}

	void removeAt(size_t index) override {
		assert(index < _count);
		Node *cursor = _head;
		Node *last = _head;
		while (index--) {
			last = cursor;
			cursor = cursor->next;
		}
		if(cursor == last) {  //index == 0,move _head to next
			_head = cursor->next;
		}
		last->next = cursor->next;
		delete cursor;
		_count--;
	}

	bool removeOne(const T & t) override {
		Node *cursor = _head;
		Node *last = _head;
		bool exist = false;
		while (cursor) {
			if(cursor->value == t) {
				exist = true;
				break;
			}
			last = cursor;
			cursor = cursor->next;
		}
		if (cursor == last) {  //index == 0,move _head to next
			_head = cursor->next;
		}
		last->next = cursor->next;
		delete cursor;
		_count--;
		return exist;
	}

	void remove(size_t start, size_t count) override {
		int dValue;
		if (start + count >= _count) {
			dValue = _count - start;
		} else {
			dValue = count;
		}
		while (dValue > 0 && _count > 0) {
			removeAt(start + dValue - 1);
			dValue--;
		}
	}

	void removeAll() override {
		while (_head) {
			Node *cursor = _head;
			_head = _head->next;
			delete cursor;
		}
		_head = nullptr;
		_tail = nullptr;
	}

	T &first() override {
		return _head->value;
	}

	const T & first() const override {
		return _head->value;
	}

	T & last() override {
		return _tail->value;
	}

	const T & last() const override {
		return _tail->value;
	}

	T & at(size_t index) override {
		assert(index < _count);
		Node *cursor = _head;
		while (index--) {
			cursor = cursor->next;
		}
		return cursor->value;
	}

	const T & at(size_t index) const override {
		assert(index < _count);
		Node *cursor = _head;
		while (index--) {
			cursor = cursor->next;
		}
		return cursor->value;
	}

	T & operator[](size_t index) override {
		return at(index);
	}

	const T & operator[](size_t index) const override {
		return at(index);
	}

	struct Iterator {
		typename LinkedList<T>::Node *cursor = nullptr;
		bool operator!=(const Iterator &iter) {
			return iter.cursor != cursor;
		}
		void operator++() {
			cursor = cursor->next;
		}
		T &operator*() {
			return cursor->value;
		}
	};

	struct ConstIterator {
		typename LinkedList<T>::Node *cursor = nullptr;
		bool operator!=(const ConstIterator &iter) {
			return iter.cursor != cursor;
		}
		void operator++() {
			cursor = cursor->next;
		}
		const T &operator*() & {
			return cursor->value;
		}
	};

	Iterator begin() {
		Iterator iter;
		iter.cursor = _head;
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
		T value;
		Node* next = nullptr;
	};
	Node *_head = nullptr;
	Node *_tail = nullptr;
};