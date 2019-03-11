#pragma once

#include "Capacity.h"
#include "AbstractList.h"
#include <cassert>
#include <initializer_list>

/**
 * \brief 列表
 * \tparam T Any
 */
template <typename T>
class DoubleLinkedList : public AbstractList<T> {
	using Capacity::_count;
public:
	void clear() override {
		removeAll();
	}
	DoubleLinkedList() = default;
	DoubleLinkedList(std::initializer_list<T> list) {
		for (auto item : list) {
			append(item);
		}
	}

	virtual ~DoubleLinkedList() override {
		removeAll();
	}

	void prepend(const T & t) override {
		Node *n = new Node();
		n->value = t;
		if(_head) {
			n->next = _head;
			_head->prev = n;
		} else {
			_tail = n;
		}
		_head = n;
		_count++;
	}

	void append(const T & t) override {
		Node *n = new Node();
		n->value = t;
		if(_tail) {
			n->prev = _tail;
			_tail->next = n;
		} else {
			_head = n;
		}
		_tail = n;
		_count++;
	}

	void insert(size_t index, const T & t) override {
		if(index >= _count) {
			append(t);
		} else if (index == 0) {
			prepend(t);
		} else {
			Node *n = new Node();
			n->value = t;
			_count++;
			if(index > _count / 2) {
				Node *cursor = _tail;
				int dValue = _count - 1 - index;
				while (dValue--) {
					cursor = cursor->prev;
				}
				cursor->next->prev = n;
				n->next = cursor->next;
				cursor->next = n;
				n->prev = cursor;
			} else {
				Node *cursor = _head;
				while (index--) {
					cursor = cursor->next;
				}
				cursor->prev->next = n;
				n->prev = cursor->prev;
				cursor->prev = n;
				n->next = cursor;
			}
		}
	}

	void removeFirst() override {
		assert(_head != nullptr);
		Node *cursor = _head->next;
		delete _head;
		if(cursor) {
			cursor->prev = nullptr;
			_head = cursor;
		} else {
			_head = nullptr;
			_tail = nullptr;
		}
		_count--;
	}

	void removeLast() override {
		assert(_tail != nullptr);
		Node *cursor = _tail->prev;
		delete _tail;
		if(cursor) {
			cursor->next = nullptr;
			_tail = cursor;
		} else {
			_head = nullptr;
			_tail = nullptr;
		}
		_count--;
	}

	void removeAt(size_t index) override  {
		assert(index < _count);
		if(index == 0) {
			removeFirst();
		} else if(index == _count - 1) {
			removeLast();
		} else if(index > _count / 2) {
			int dValue = _count - index - 1;
			Node *cursor = _tail;
			while (dValue--) {
				cursor = cursor->prev;
			}
			cursor->next->prev = cursor->prev;
			cursor->prev->next = cursor->next;
			delete cursor;
			_count--;
		} else {
			Node *cursor = _head;
			while(index--) {
				cursor = cursor->next;
			}
			cursor->next->prev = cursor->prev;
			cursor->prev->next = cursor->next;
			delete cursor;
			_count--;
		}
	}

	bool removeOne(const T & t) override {
		Node *cursor = _head;
		bool exist = false;
		while (cursor) {
			if (cursor->value == t) {
				exist = true;
				break;
			}
			cursor = cursor->next;
		}
		if(exist) {
			if (cursor == _head) {
				removeFirst();
			} else if (cursor == _tail) {
				removeLast();
			} else {
				cursor->next->prev = cursor->prev; // 1 2 3
				cursor->prev->next = cursor->next;
				delete cursor;
				_count--;
			}
		}
		return exist;
	}

	void remove(size_t start, size_t count) override {
		int dValue;
		if(start + count >= _count) {
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

	T &first() override  {
		return _head->value;
	}

	const T &first() const override {
		return _head->value;
	}

	T & last() override {
		return _tail->value;
	}

	const T & last() const override {
		return _tail->value;
	}

	T & at(size_t index)  override {
		assert(index < _count);
		if (index > _count / 2) {
			Node *cursor = _tail;
			int dValue = _count - index - 1;
			while (dValue--) {
				cursor = cursor->prev;
			}
			return cursor->value;
		}
		else {
			Node *cursor = _head;
			while (index--) {
				cursor = cursor->next;
			}
			return cursor->value;
		}
	}

	const T & at(size_t index) const override {
		assert(index < _count);
		if (index > _count / 2) {
			Node *cursor = _tail;
			int dValue = _count - index - 1;
			while (dValue--) {
				cursor = cursor->prev;
			}
			return cursor->value;
		}
		else {
			Node *cursor = _head;
			while (index--) {
				cursor = cursor->next;
			}
			return cursor->value;
		}
	}

	T & operator[](size_t index) override {
		return at(index);
	}

	const T & operator[](size_t index) const override {
		return at(index);
	}

	struct Iterator {
		typename DoubleLinkedList<T>::Node *cursor = nullptr;
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
		typename DoubleLinkedList<T>::Node *cursor = nullptr;
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

protected:
	struct Node {
		Node* prev = nullptr;
		T value;
		Node* next = nullptr;
	};
	Node *_head = nullptr;
	Node *_tail = nullptr;
};