#include "node.h"
#include "globals.h"
#include "vartable.h"

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

std::string RootblockNode::to_asm(){
	std::stringstream ss;
	// Print compiler info
	ss << "    movq $_CompilerInfoStr, %rdi" << std::endl; 
	ss << "    call prints" << std::endl;
	ss << std::endl;

	for (Node* node : children){
		ss << node->to_asm();
		ss << std::endl;
	}
	return ss.str();
}

ArglistNode::ArglistNode() : ContainerNode(){}

std::string ArglistNode::to_str(){
	return "explist";
}
std::string ArglistNode::to_asm(){
	std::stringstream ss;
	for (Node* arg : children){
		ss << arg->to_asm() << std::endl;
		ss << "    decq %rsp" << std::endl;
		ss << "    movq %rax,(%rsp)" << std::endl;
	}
	const std::string argregs[] = {"%rdi","%rsi","rdx","rcx","r8","r9"};
	for(int i=0; i<children.size(); i++){
		ss << "    movq (%rsp)," << argregs[i] << std::endl;
		ss << "    incq %rsp" << std::endl;
	}
	return ss.str();
}

AssignmentNode::AssignmentNode(std::string name, Node& exp) : Node() {
	this->name = name;
	roottable.addvar(name, *(DataNode*)&exp);
	value = &exp;
}

void AssignmentNode::dumps_str(std::stringstream& ss, int depth) {
	writeline(ss, depth);
	value->dumps_str(ss, depth+1);
}

std::string AssignmentNode::to_str(){
	std::stringstream ss;
	ss << "assignment: " << name;
	return ss.str();
}

std::string AssignmentNode::to_asm(){
	std::stringstream ss;

	if (dynamic_cast<OperatorNode*>(value) != nullptr){
		ss << ((OperatorNode*)value)->to_asm();
	}
	else if (dynamic_cast<IntNode*>(value) != nullptr){
		ss << ((IntNode*)value)->to_asm();
	}
	ss << std::endl;
	ss << "    movq %rax, _"<<name<<std::endl;
	return ss.str();
}

/*

   Types
 
*/

TypeNode::TypeNode() : Node() {}

void TypeNode::dumps_str(std::stringstream& ss, int depth){
	writeline(ss, depth);
}

FunccallNode::FunccallNode(std::string name, ArglistNode* args) : TypeNode() {
	this->name = name;
	this->args = args;
}

void FunccallNode::dumps_str(std::stringstream& ss, int depth) {
	writeline(ss, depth);
	args->dumps_str(ss, depth+1);
}



std::string FunccallNode::to_str(){
	std::stringstream ss;
	ss << "funccall: " << name;
	return ss.str();
}

std::string FunccallNode::to_asm(){
	std::stringstream ss;
	if (this->args->children.size() > 6){
		std::cout << "Functions currently does not support more than 6 arguments" << std::endl;
		exit(-1);
	}
	ss << args->to_asm() << std::endl;

	if (this->name == "printi"){
		if (this->args->children.size() != 1){
			std::cout << "Invalid argument count" << std::endl;
			exit(-1);
		}
		//ss << "    movq %rax, %rdi" << std::endl;
		ss << "    call printi" << std::endl;
	}
	else if (this->name == "prints"){
		if (this->args->children.size() != 1){
			std::cout << "Invalid argument count" << std::endl;
			exit(-1);
		}
		//ss << "    movq %rax, %rdi" << std::endl;
		ss << "    call prints" << std::endl;
	}
	else {
		std::cout << "Function " << this->name << " is not defined" << std::endl;
		exit(-1);
	}
	ss << std::endl;
	return ss.str();
}

ReferenceNode::ReferenceNode(std::string value) : TypeNode() {
	this->value = value;
}

std::string ReferenceNode::to_str(){
	std::stringstream ss;
	ss << "var: " << value;
	return ss.str();
}

std::string ReferenceNode::to_asm(){
	std::stringstream ss;
	ss << "    movq _" << value << ", %rax" << std::endl;
	return ss.str();
}

DataNode::DataNode(int bsize) : TypeNode() {
	this->bsize = bsize;
}

IntNode::IntNode(std::string value) : DataNode(8) {
	this->value = value;
}

std::string IntNode::to_str(){
	std::stringstream ss;
	ss << "int: " << value;
	return ss.str();
}

std::string IntNode::to_asm(){
	std::stringstream ss;
	ss << "    movq $" << value << ", %rax" << std::endl;
	return ss.str();
}

FloatNode::FloatNode(std::string value) : DataNode(8) {
	this->value = value;
}

std::string FloatNode::to_str(){
	std::stringstream ss;
	ss << "float: " << value;
	return ss.str();
}

/*

	Operators

*/

OperatorNode::OperatorNode() : ContainerNode() {}

/*
void OperatorNode::dumps_str(std::stringstream& ss, int depth) {
	writeline(ss, depth);
    for(std::list<Node*>::iterator i=children.begin(); i!=children.end(); i++){
		(*i)->dumps_str(ss, depth+1);
	}
}
*/

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

	ss << op2.to_asm();
	ss << "    movq %rax, %rbx" << std::endl;
	ss << op1.to_asm();
	
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

	ss << op2.to_asm();
	ss << "    movq %rax, %rbx" << std::endl;
	ss << op1.to_asm();

	ss << "    ";
	ss << "subq ";
  	ss << "%rbx" << "," << "%rax";
	ss << std::endl;
	ss << std::endl;
	return ss.str();
}
