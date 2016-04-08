#include "node.h"
#include "globals.h"

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <typeinfo>


/*

	Baseclass

*/

Node::Node(){
	this->srcline = linenr;
}

void Node::writeline(std::stringstream& ss, int depth){
	std::string linestr = std::to_string(srcline);
	ss << linestr;
	for (int i=linestr.length(); i<=3; i++)
		ss << " ";
	ss << ":";
    for(int i=0; i<depth; i++)
       	ss << " ";
   	ss << to_str() << std::endl;
}



/*

	Containers 
 
*/

ContainerNode::ContainerNode() : Node(){}

void ContainerNode::dumps_str(std::stringstream& ss, int depth) {
	writeline(ss, depth);
    for(std::list<Node*>::iterator i=children.begin(); i!=children.end(); i++){
		(*i)->dumps_str(ss, depth+1);
	}
}


RootblockNode::RootblockNode() : ContainerNode(){}

std::string RootblockNode::to_str(){
	return "rootblock";
}

/*

   Types
 
*/

TypeNode::TypeNode() : Node() {}

void TypeNode::dumps_str(std::stringstream& ss, int depth){
	writeline(ss, depth);
}

FunccallNode::FunccallNode(std::string name) : TypeNode() {
	this->name = name;
}

std::string FunccallNode::to_str(){
	std::stringstream ss;
	ss << "funccall: " << name;
	return ss.str();
}

std::string FunccallNode::to_asm(){
	std::stringstream ss;
	if (this->name == "printi"){
		ss << "    movq %rax, %rdi" << std::endl;
		ss << "    call printi" << std::endl;
	}
	else if (this->name == "prints"){
		ss << "    movq %rax, %rdi" << std::endl;
		ss << "    call prints" << std::endl;
	}
	else {
		std::cout << "Function " << this->name << " is not defined" << std::endl;
		exit(-1);
	}
	ss << std::endl;
	return ss.str();
}

VariableNode::VariableNode(std::string value) : TypeNode() {
	this->value = value;
}

std::string VariableNode::to_str(){
	std::stringstream ss;
	ss << "var: " << value;
	return ss.str();
}

IntNode::IntNode(std::string value) : TypeNode() {
	this->value = value;
	this->srcline = linenr;
}

std::string IntNode::to_str(){
	std::stringstream ss;
	ss << "int: " << value;
	return ss.str();
}

FloatNode::FloatNode(std::string value) : TypeNode() {
	this->value = value;
	this->srcline = linenr;
}

std::string FloatNode::to_str(){
	std::stringstream ss;
	ss << "float: " << value;
	return ss.str();
}

/*

	Operators

*/

OperatorNode::OperatorNode() : Node() {}

void OperatorNode::dumps_str(std::stringstream& ss, int depth) {
	writeline(ss, depth);
    for(std::list<Node*>::iterator i=children.begin(); i!=children.end(); i++){
		(*i)->dumps_str(ss, depth+1);
	}
}

PlusNode::PlusNode() : OperatorNode() {
	this->srcline = linenr;
}

std::string PlusNode::to_str(){
	return "plus";
}

std::string PlusNode::to_asm(){
	if (dynamic_cast<FloatNode*>(children.front()) || dynamic_cast<FloatNode*>(children.back())){
		std::cout << "Floats are currently not supported" << std::endl;
		exit(-1);
	}
	TypeNode& op1 = *((TypeNode*)children.front());
	TypeNode& op2 = *((TypeNode*)children.back());
	std::stringstream ss;
	ss << "    ";
	ss << "movq ";
  	ss << "$" << op1.value;
	ss << ",";
	ss << "%rax";
	ss << std::endl;
	
	ss << "    ";
	ss << "movq ";
  	ss << "$" << op2.value;
	ss << ",";
	ss << "%rbx";
	ss << std::endl;
	
	ss << "    ";
	ss << "addq ";
  	ss << "%rbx" << "," << "%rax";
	ss << std::endl;
	ss << std::endl;
	return ss.str();
}

MinusNode::MinusNode() : OperatorNode() {
	this->srcline = linenr;
}

std::string MinusNode::to_str(){
	return "minus";
}

std::string MinusNode::to_asm(){
	if (dynamic_cast<FloatNode*>(children.front()) || dynamic_cast<FloatNode*>(children.back())){
		std::cout << "Floats are currently not supported" << std::endl;
		exit(-1);
	}
	TypeNode& op1 = *((TypeNode*)children.front());
	TypeNode& op2 = *((TypeNode*)children.back());
	std::stringstream ss;
	ss << "    ";
	ss << "movq ";
  	ss << "$" << op1.value;
	ss << ",";
	ss << "%rax";
	ss << std::endl;
	
	ss << "    ";
	ss << "movq ";
  	ss << "$" << op2.value;
	ss << ",";
	ss << "%rbx";
	ss << std::endl;
	
	ss << "    ";
	ss << "subq ";
  	ss << "%rbx" << "," << "%rax";
	ss << std::endl;
	ss << std::endl;
	return ss.str();
}
