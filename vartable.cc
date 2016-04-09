#include <iostream>
#include <utility>

#include "globals.h"
#include "vartable.h"

VarTable::VarTable(){
	this->parenttable = nullptr;
}

VarTable::VarTable(VarTable& parenttable){
	this->parenttable = &parenttable;
}

VarTable::~VarTable(){
	// TODO: Implement cleanup
}

void VarTable::addvar(const std::string name, TypeNode& value){
	std::pair<std::string,TypeNode*> entry (name.c_str(), &value);
	table.insert(entry);
}

bool VarTable::setvar(const std::string name, TypeNode& value){
	
}

bool VarTable::delvar(const std::string name){
}

std::pair<const std::string, TypeNode*>* VarTable::getentry(const std::string name){
	std::pair<const std::__cxx11::basic_string<char>, TypeNode*>* returnval = nullptr;
	auto result = table.find(name);
	if (result != table.end())
		returnval = &*result;
	return returnval;
}

TypeNode* VarTable::getvar(const std::string name){
	TypeNode* returnval = nullptr;
	auto entry = getentry(name);
	if (entry != nullptr)
		returnval = entry->second;
	return returnval;
}
