#pragma once
#include <stdio.h>

/**
 * \brief Base Class
 */
class Object {
public:
	Object() = default;
	virtual ~Object() = default; 
	virtual char* toString() {
		char *buf = new char[32];
		sprintf_s(buf, 32,"Object(0x%p)",this);
		return buf;
	}
};