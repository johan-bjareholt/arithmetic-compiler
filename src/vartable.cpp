#include "globals.h"
#include "vartable.h"

#include <string>


VarTable::VarTable(){
	this->parenttable = nullptr;
}

VarTable::VarTable(VarTable& parenttable){
	this->parenttable = &parenttable;
}

VarTable::~VarTable(){
	// TODO: Implement cleanup
}

void VarTable::addvar(const std::string name, Class& value){
	// TODO: Copy over DataNode so VarTable can have ownership and take care of cleanup.
	std::pair<std::string,Class*> entry (name.c_str(), &value);
	table.insert(entry);
}

bool VarTable::setvar(const std::string name, Class& value){
	// TODO: Not a very good solution
	delvar(name);
	addvar(name, value);
}

bool VarTable::delvar(const std::string name){
	table.erase(name);
}

std::pair<const std::string, Class*>* VarTable::getentry(const std::string name){
	std::pair<const std::__cxx11::basic_string<char>, Class*>* returnval = nullptr;
	auto result = table.find(name);
	if (result != table.end())
		returnval = &*result;
	return returnval;
}

Class* VarTable::getvar(const std::string name){
	Class* returnval = nullptr;
	auto entry = getentry(name);
	if (entry != nullptr)
		returnval = entry->second;
	return returnval;
}
