#pragma once
#include "Capacity.h"
#include <cstring>
#include <ostream>
#include <istream>

/**
 * \brief 
 */
class String : public Capacity {
public:
	String(const char* str = nullptr) {
		if (!str) {
			_count = 0;
			_ptr = new char[1];
			*_ptr = '\0';
		} else {
			_count = strlen(str);
			_ptr = new char[_count + 1];
			strcpy_s(_ptr, _count + 1, str);
		}
	}
	String(const String& str) {
		_count = str.length();
		_ptr = new char[_count + 1];
		strcpy_s(_ptr, _count + 1,str.c_str());
	}

	~String() {
		clear();
	}

	String operator+(const String& str) const {
		String ret;
		ret._count = _count + str.length();
		ret._ptr = _quickStrcat(_ptr, str._ptr, ret._count);
		return ret;
	}

	String& operator=(const char* str) {
		size_t len = strlen(str);
		if (len >= _count) {
			delete[]_ptr;
			_count = len;
			_ptr = new char[_count + 1];
		}
		strcpy_s(_ptr, _count + 1, str);
		return *this;
	}

	String& operator=(const String& str) {
		if (this == &str) {
			return *this;
		}
		*this = str._ptr;
		return *this;
	}

	String operator+=(const String &str) {
		_count += str._count;
		char* buf = _quickStrcat(_ptr, str._ptr,_count);
		delete[]_ptr;
		_ptr = buf;
		return *this;
	}

	bool operator==(const String &str) {
		if(_count != str._count) {
			return false;
		}
		return *this == str._ptr;
	}

	bool operator==(const char *str) {
		return strcmp(_ptr, str) == 0;
	}

	char &operator[](int index) const {
		if(index >= _count) {
			return _ptr[_count - 1];
		}
		return _ptr[index];
	}

	const char &at(int index) const {
		return (*this)[index];
	}

	void clear() override final {
		delete[]_ptr;
		_count = 0;
	}

	const char* c_str() const {
		return _ptr;
	}

private:
	char * _quickStrcat(char *head,char *tail,size_t bufSize) const {
		char *buf = new char[bufSize + 1];
		char *cursor = buf;
		do {
			if(*head != '\0') {
				*cursor = *head;
				head++;
			} else if(*tail != '\0') {
				*cursor = *tail;
				tail++;
			} else {
				break;
			}
			cursor++;
		} while (true);
		*cursor = '\0';
		return buf;
	}
private:
	char* _ptr = nullptr;
};

inline std::ostream & operator<<(std::ostream &os, const String &str) {
	os << str.c_str();
	return os;
}

inline std::istream & operator>>(std::istream &is, String &str) {
	char buf[1024];
	is >> buf;
	str = buf;
	return is;
}
