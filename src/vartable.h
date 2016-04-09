#pragma once

#include "node.h"

#include <string>
#include <unordered_map>


class VarTable {
	private:
	std::unordered_map<std::string, TypeNode*> table;
	VarTable* parenttable;

	public:
	VarTable();
	VarTable(VarTable&);
	~VarTable();
	void addvar(const std::string name, TypeNode& value);
	bool setvar(const std::string name, TypeNode& value);
	bool delvar(const std::string name);
	std::pair<const std::string, TypeNode*>* getentry(const std::string name);
	TypeNode* getvar(const std::string name);
};
