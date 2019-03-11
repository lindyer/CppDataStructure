#pragma once

#include "Capacity.h"
#include "Vector.h"
#include "LinkedList.h"
#include "Pair.h"
#include "String.h"

#include <unordered_map>

template <typename K,typename V>
class Hash : public Capacity {
public:
	Hash() {}
	struct StrHash {
		size_t operator()(const String &str) const {
			return 0;
		}
	};
private:
	Vector<int> _hash;
	Vector<LinkedList<Pair<K, V>>> _buckets;
};
