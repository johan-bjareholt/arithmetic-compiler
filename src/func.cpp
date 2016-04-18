#include "func.h"

#include <iostream>



Function::Function(ParlistNode& parlist, BlockNode& funcbody){
	this->parlist = &parlist;
	this->funcbody = &funcbody;
}

std::string Function::to_str(){
	return "function";
}

std::string Function::to_asm(){
	std::cout << "WARNING: Function to_asm is not yet properly implemented!" << std::endl;
	std::stringstream ss;
	ss << funcbody->to_asm();
	return ss.str();
}
