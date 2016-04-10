#pragma once

#include "node.h"

#include <string>
#include <unordered_map>


class VarTable {
	public:
	std::unordered_map<std::string, DataNode*> table;
	VarTable* parenttable;

	VarTable();
	VarTable(VarTable&);
	~VarTable();
	void addvar(const std::string name, DataNode& value);
	bool setvar(const std::string name, DataNode& value);
	bool delvar(const std::string name);
	std::pair<const std::string, DataNode*>* getentry(const std::string name);
	DataNode* getvar(const std::string name);
};
