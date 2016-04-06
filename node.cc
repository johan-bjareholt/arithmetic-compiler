#include "node.h"
#include "globals.h"

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <typeinfo>

void ContainerNode::dumps_str(std::stringstream& ss, int depth) {
   	for(int i=0; i<depth+1; i++)
       	ss << " ";
   	ss << "Container" << std::endl;
    for(std::list<Node*>::iterator i=children.begin(); i!=children.end(); i++){
		(*i)->dumps_str(ss, depth+1);
	}
}

void OperatorNode::dumps_str(std::stringstream& ss, int depth) {
   	for(int i=0; i<depth+1; i++)
       	ss << " ";
   	ss << to_str() << std::endl;
    for(std::list<Node*>::iterator i=children.begin(); i!=children.end(); i++){
		(*i)->dumps_str(ss, depth+1);
	}
}

void TypeNode::dumps_str(std::stringstream& ss, int depth){
    for(int i=0; i<depth+1; i++)
       	ss << " ";
	ss << to_str() << std::endl;
}


ContainerNode::ContainerNode(){
	this->srcline = linenr;
}

ContainerNode::ContainerNode(std::string tag){
	this->tag = tag;
	this->srcline = linenr;
}

std::string ContainerNode::to_str(){
	std::stringstream ss;
	ss << "container: " << tag;
	return ss.str();
}

IntNode::IntNode(std::string value){
	this->value = value;
	this->srcline = linenr;
}

std::string IntNode::to_str(){
	std::stringstream ss;
	ss << "int: " << value;
	return ss.str();
}

FloatNode::FloatNode(std::string value){
	this->value = value;
	this->srcline = linenr;
}

std::string FloatNode::to_str(){
	std::stringstream ss;
	ss << "float: " << value;
	return ss.str();
}

PlusNode::PlusNode(){
	this->srcline = linenr;
}

std::string PlusNode::to_str(){
	std::stringstream ss;
	ss << "plus: ";
	return ss.str();
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
	return ss.str();
}

MinusNode::MinusNode(){
	this->srcline = linenr;
}

std::string MinusNode::to_str(){
	std::stringstream ss;
	ss << "minus: ";
	return ss.str();
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
	return ss.str();
}
