#pragma once

template<typename T>
class BinaryTree {
public:
	struct Node {
		Node *left = nullptr;
		T t;
		Node *right = nullptr;
	};
	Node &root() const {
		return _root;
	}
private:
	Node _root;
};

