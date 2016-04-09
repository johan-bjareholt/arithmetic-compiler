#include <iostream>

#include "vartable.h"
#include "node.h"

int linenr=0;

int main(){
	// Create table
	VarTable vt;
	// Add var
	IntNode* sn = new IntNode("1");
	vt.addvar("intnode1", *sn);
	// Check that var is in table and is fetchable
	TypeNode* tn = vt.getvar("intnode1");
	if (tn == nullptr){
		std::cout << "Couldn't get variable" << std::endl;
		exit(-1);
	}
	std::cout << tn->to_str() << std::endl;
	// Remove variable from table and make sure that it's not there
	vt.delvar("intnode1");
	tn = vt.getvar("intnode1");
	if (tn != nullptr){
		std::cout << "Variable was not removed from table!" << std::endl;
		exit(-1);
	}
	// Cleanup
	delete sn;
	// Exit
	return 0;
}