#pragma once

#include "Capacity.h"
#include <iostream>
#include <cassert>

/**
 * \brief 动态数组
 * \tparam T Any
 */
template <typename T>
class Vector : public Capacity {
public:
	/**
	 * \brief Constructs an empty vector.
	 */
	Vector() {
		_allotor(0);
	}

	/**
	 * \brief  Constructs a vector with an initial size of size elements.
	 *			The elements are initialized with a default-constructed value.
	 * \param size 
	 */
	Vector(size_t size) {
		_allotor(size);
	}

	/**
	 * \brief 
	 * \param size 
	 * \param value 
	 */
	Vector(size_t size,const T &value) {
		_allotor(size, value);
	}

	Vector(const Vector<T> &other) {
		_capacity = other._capacity;
		_arrPtr = new T[_capacity];
		_count = other._count;
		for(int i = 0;i < _count; i++) {
			*(_arrPtr + i) = *(other._arrPtr + i);
		}
	}

	Vector(std::initializer_list<T> args) {
		int size = args.size();
		_capacitySelector(size);
		_arrPtr = new T[_capacity];
		_count = size;
		int index = 0;
		for(auto item: args) {
			*(_arrPtr + index) = item;
			index++;
		}
	}

	~Vector() {
		clear();
	}

	virtual void clear() override final {
		delete[]_arrPtr;
		_count = 0;
		_capacity = DefaultCapacity;
	}

	void insert(size_t index, const T &t) {
		
	}

	T &last() {
		return *(_arrPtr + _count - 1);
	}

	void append(const T &t) {
		size_t size = _count + 1;
		if(size > _capacity) { 
			size_t oldCapacity = _capacity;
			_capacitySelector(size);
			T *newBlock = new T[_capacity];
			for(int i = 0;i < oldCapacity; i++) { 
				*(newBlock + i) = *(_arrPtr + i);
			}
			delete[]_arrPtr;
			_arrPtr = newBlock;
		}
		*(_arrPtr + _count) = t;
		_count++;
	}

	T &operator[](size_t index) {
		assert(index >= 0 && index < _count);
		return *(_arrPtr + index);
	}

	const T &operator[](size_t index) const {
		assert(index >= 0 && index < _count);
		return *(_arrPtr + index);
	}

	T &at(size_t index) {
		return (*this)[index];
	}

	const T &at(size_t index) const {
		return (*this)[index];
	}

	void remove(size_t index) {
		assert(index < _count);
		//int loop = _count - index - 1; // 0,1 0
		if(_count == 1 || index == _count - 1) {
			_count--;
		} else {
			do {
				*(_arrPtr + index) = *(_arrPtr + index + 1);
				index++;
			} while (index == _count - 2);
		}
	}

	void removeFirst() {
		remove(0);
	}

	void removeLast() {
		_count--;
	}

	struct Iterator {
		Vector<T> *parent = nullptr;
		size_t cursor = 0;
		bool operator!=(const Iterator &iter) {
			return iter.cursor != cursor;
		}
		void operator++() {
			cursor++;
		}
		const T &operator*() & {
			return *(parent->_arrPtr + cursor);
		}
	};

	struct ConstIterator {
		Vector<T> *parent = nullptr;
		size_t cursor;
		bool operator!=(const ConstIterator &iter) {
			return iter.cursor != cursor + 1;
		}
		void operator++() {
			cursor++;
		}
		const T &operator*() & {
			return *(parent->_arrPtr + cursor);
		}
	};

	Iterator begin() {
		Iterator iter;
		iter.parent = this;
		iter.cursor = 0;
		return iter;
	}

	Iterator end() {
		Iterator iter;
		iter.cursor = _count;
		return iter;
	}

	const ConstIterator &begin() const {
		ConstIterator constIter;
		constIter.cursor = 0;
		return constIter;
	}

	const ConstIterator &end() const {
		Iterator iter;
		iter.cursor = _count;
		return iter;
	}

private:
	void _capacitySelector(size_t size) {
		while(size > _capacity) {
			_capacity *= 2;
		}
	}

	void _allotor(size_t size = 0, const T &t = T()) {
		_capacitySelector(size);
		_arrPtr = new T[_capacity];
		_count = size;
		while(size--) {
			*(_arrPtr + size) = t;
		}
	}

private:
	T* _arrPtr = nullptr; //数组指针
	size_t _capacity = DefaultCapacity;
	const static size_t DefaultCapacity = 8;
};
