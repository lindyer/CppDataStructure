#include "Src/Queue.h"
#include "Src/String.h"
#include "Src/Vector.h"
#include "Src/Stack.h"
#include "Src/DoubleLinkedList.h"

#include <sys/timeb.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <list>
#include <string>

using namespace std;
using namespace chrono;

void test_stack() {
	Stack<int> stack{ 1, 2, 3 };
	cout << stack.size() << endl;
	cout << stack.pop() << endl;
	cout << stack.top() << endl;
	cout << stack.size() << endl;
}

void test_double_list() {
	DoubleLinkedList<int> l{1,2,3,4,5};
	l.remove(1,2);
	l[2] = 6;
	l.removeOne(4);
	for(auto item: l) {
		cout << item << endl;
	}
}

void benchmark_my_list_1s() {
	DoubleLinkedList<int> l;
	auto start = system_clock::now();
	while(duration_cast<microseconds>(system_clock::now() - start).count() < 1000) {
		l.append(0);
	}
	cout << "my list insert " << l.size() << " times in 1s" << endl;
	// start = system_clock::now();
	// l.removeAll();
	// cout << duration_cast<microseconds>(system_clock::now() - start).count() << endl;
}

void benchmark_std_list_1s() {
	std::list<int> l;
	auto start = system_clock::now();
	while (duration_cast<microseconds>(system_clock::now() - start).count() < 1000) {
		l.push_back(0);
	}
	cout << "std list insert " << l.size() << " times in 1s" << endl;

	start = system_clock::now();
	l.clear();
	cout << duration_cast<microseconds>(system_clock::now() - start).count() << endl;
}

void test_my_string() {
	String str = "hel";
	cout << str << str.size() << endl;
	str[6] = '#';
	cout << str << endl;
}

void test_my_vector() {
	Vector<int> v{ 9,2,5,6 };
	for (auto item : v) {
		std::cout << item << endl;
	}
}

void test_my_stack() {
	Stack<int> s{ 6,5,2 };
	std::cout << s.pop() << endl;
	s.push(7);
	for (auto item : s) {
		std::cout << item << endl;
	}
}

void test_my_linkedStack() {
	LinkedStack<int> s{ 6,5,2 };
	std::cout << s.pop() << endl;
	s.push(7);
	for (auto item : s) {
		std::cout << item << endl;
	}
}

void test_my_queue() {
	Queue<int> queue;
	queue.enqueue(1);
	queue.enqueue(3);
	cout << queue.dequeue() << endl;
	for(auto item: queue) {
		cout << item << endl;
	}
}

int main()
{
	//test_double_list();
	//test_my_vector();
	//test_my_stack();
	test_my_queue();
	std::getchar();
}

