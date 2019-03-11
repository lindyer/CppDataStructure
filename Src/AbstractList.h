#pragma once
#include "Object.h"
#include "Capacity.h"

/**
 * \brief 抽象列表实现接口
 * \tparam T Any
 */
template <typename T>
class AbstractList: public Object, public Capacity {
public:
	virtual ~AbstractList() = default;
	virtual void insert(size_t index,const T & t) = 0;
	virtual void append(const T & t) = 0;
	virtual void prepend(const T & t) = 0;
	virtual T & at(size_t index) = 0;
	virtual const T & at(size_t index) const = 0;
	virtual T & operator[](size_t index) = 0;
	virtual const T & operator[](size_t index) const = 0;
	virtual T & first() = 0;
	virtual const T & first() const = 0;
	virtual T & last() = 0;
	virtual const T & last() const = 0;
	virtual void remove(size_t start, size_t count) = 0;
	virtual void removeAt(size_t index) = 0;
	virtual bool removeOne(const T & t) = 0;
	virtual void removeFirst() = 0;
	virtual void removeLast() = 0;
	virtual void removeAll() = 0;
};