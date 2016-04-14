#pragma once

#include "variable.h"

#include <string>
#include <unordered_map>


class VarTable {
	public:
	std::unordered_map<std::string, Variable*> table;
	VarTable* parenttable;

	VarTable();
	VarTable(VarTable&);
	~VarTable();
	void addvar(const std::string name, Variable& value);
	bool setvar(const std::string name, Variable& value);
	bool delvar(const std::string name);
	std::pair<const std::string, Variable*>* getentry(const std::string name);
	Variable* getvar(const std::string name);
};
