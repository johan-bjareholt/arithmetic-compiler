#pragma once

#include <string>

enum Classes {
	CLASS_INT,
	CLASS_FLOAT,
	CLASS_STR,
};

class Class {
	public:
	int bytesize;
	Class(int bytesize);
	virtual std::string to_string() = 0;
};

class IntClass : public Class {
	public:
	IntClass();
	virtual std::string to_string();
};
