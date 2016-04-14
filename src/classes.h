#pragma once

#include "variable.h"

#include <string>

enum Classes {
	CLASS_INT,
	CLASS_FLOAT,
	CLASS_STR,
};

class Class : public Variable {
	public:
	int bytesize;
	Class(int bytesize);
	virtual std::string to_str() = 0;
};

class IntClass : public Class {
	public:
	IntClass();
	virtual std::string to_str();
};

class FuncClass : public Class {
	public:
	FuncClass();
	virtual std::string to_str();
};
