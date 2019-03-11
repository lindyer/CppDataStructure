#pragma once

#include "LinkedList.h"
#include <cassert>
#include "Vector.h"
/**
 * \brief std-like
 * \tparam T Any
 */
template<typename T>
using ForwardList = LinkedList<T>;

template<typename T>
using List = DoubleLinkedList<T>;

template<typename T>
using ArrayList = Vector<T>;