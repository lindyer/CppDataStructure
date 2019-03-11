#pragma once

template <typename K,typename V>
class Pair {
public:
	Pair(const K &k,const V &v): key(k),value(v) {}

	Pair(const Pair<K, V> &p) {
		key = p.key;
		value = p.value;
	}

	Pair<K, V> & operator=(const Pair<K, V> &p) {
		key = p.key;
		value = p.value;
		return *this;
	}

	bool operator==(const Pair<K,V> &o) {
		return key == p.key && value == p.value;
	}

	K key;
	V value;
};

template<typename K,typename V>
inline Pair<K,V> makePair(const K &k,const V &v) {
	return Pair<K, V>(k, v);
}
