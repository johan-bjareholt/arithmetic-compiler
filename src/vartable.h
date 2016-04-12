#pragma once

#include "classes.h"

#include <string>
#include <unordered_map>


class VarTable {
	public:
	std::unordered_map<std::string, Class*> table;
	VarTable* parenttable;

	VarTable();
	VarTable(VarTable&);
	~VarTable();
	void addvar(const std::string name, Class& value);
	bool setvar(const std::string name, Class& value);
	bool delvar(const std::string name);
	std::pair<const std::string, Class*>* getentry(const std::string name);
	Class* getvar(const std::string name);
};
