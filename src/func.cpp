#include "func.h"

#include <iostream>



Function::Function(ArglistNode& arglist, BlockNode& funcbody){
	this->arglist = &arglist;
	this->funcbody = &funcbody;
}

std::string Function::to_str(){
	return "function";
}

std::string Function::to_asm(){
	std::cout << "WARNING: Function to_asm is not yet properly implemented!" << std::endl;
	return "";
}
