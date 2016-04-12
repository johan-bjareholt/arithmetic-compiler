#include "classes.h"

Class::Class(int bytesize){
	this->bytesize = bytesize;
}

IntClass::IntClass() : Class(8) {}

std::string IntClass::to_string(){
	return "int";
}
