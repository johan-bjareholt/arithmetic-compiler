#include <iostream>

#include "vartable.h"
#include "nodes.h"
#include "classes.h"

int linenr=0;
VarTable roottable;

int main(){
	// Create table
	VarTable roottable;
	// Add var
	roottable.addvar("intnode1", *(new IntClass()));

	// Check that var is in table and is fetchable
	Variable* obj = roottable.getvar("intnode1");
	if (obj == nullptr){
		std::cout << "Couldn't get variable" << std::endl;
		exit(-1);
	}
	std::cout << obj->to_str() << std::endl;
	// Remove variable from table and make sure that it's not there
	roottable.delvar("intnode1");
	obj = roottable.getvar("intnode1");
	if (obj != nullptr){
		std::cout << "Variable was not removed from table!" << std::endl;
		exit(-1);
	}
	// Exit
	return 0;
}
