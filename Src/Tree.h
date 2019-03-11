#pragma once

#include "List.h"

/**
 * \brief 树
 * \tparam T Any 
 */
template <typename T>
class Tree: public Object {
public:
	class Node {
	public:
		virtual ~Node() {
			children.removeAll();
		}
		T t;
		Node *parent = nullptr;
		LinkedList<Node *> children;
		void append(Node* node) {
			children.append(node);
			node->parent = this;
			node->setDepth(_depth + 1);
		}
		void remove(Node *node) {
			children.removeOne(node);
		}
		void setDepth(const size_t depth) {
			_depth = depth;
		}
		size_t depth() const {
			return _depth;
		}
	private:
		size_t _depth = 0;
	};
	virtual ~Tree() {}

protected:
	Node _root;
};