#include "node.h"
#include "globals.h"

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <typeinfo>

void ContainerNode::dumps_str(std::stringstream& ss, int depth) {
	if (depth == 0)
		ss << to_str() << std::endl;
    for(std::list<Node*>::iterator i=children.begin(); i!=children.end(); i++){
		Node* child = *i;
    	for(int i=0; i<depth+1; i++)
        	ss << " ";
    	ss << child->to_str() << std::endl;
		if (typeid(child) == typeid(ContainerNode*)){
        	((ContainerNode*)child)->dumps_str(ss, depth+1);
		}
	}
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

IntNode::IntNode(int value){
	this->value = value;
	this->srcline = linenr;
}

std::string IntNode::to_str(){
	std::stringstream ss;
	ss << "int: " << std::to_string(value);
	return ss.str();
}

FloatNode::FloatNode(float value){
	this->value = value;
	this->srcline = linenr;
}

std::string FloatNode::to_str(){
	std::stringstream ss;
	ss << "float: " << std::to_string(value);
	return ss.str();
}
