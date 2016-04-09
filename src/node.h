#pragma once

#include <sstream>
#include <list>

#include "globals.h"


/*

	Baseclass

*/

class Node {
    public:
	Node();
	int srcline;
	void writeline(std::stringstream& ss, int depth);
	virtual std::string to_str() = 0;
	virtual void dumps_str(std::stringstream& ss, int depth) = 0;
};


/*

	Containers

*/

class ContainerNode : public Node {
	public:
	std::string tag;
    std::list<Node*> children;
	ContainerNode();
	virtual std::string to_str() = 0;
    void dumps_str(std::stringstream& ss, int depth=0);
};

class RootblockNode : public ContainerNode {
	public:
	RootblockNode();
	std::string to_str();
};

/*

	Types

*/

class TypeNode : public Node {
	public:
	std::string value;

	TypeNode();	
	void dumps_str(std::stringstream& ss, int depth);
};


class FunccallNode : public TypeNode {
	public:
	std::string name;
	
	FunccallNode(std::string name);
	std::string to_str();
	std::string to_asm();
};


class VariableNode : public TypeNode {
	public:
	VariableNode(std::string value);
	std::string to_str();
};

class IntNode : public TypeNode {
	public:
	IntNode(std::string value);
	std::string to_str();
};

class FloatNode : public TypeNode {
	public:
	FloatNode(std::string value);
	std::string to_str();
};


/*

  Operators 
 
*/


class OperatorNode : public Node {
	public:
	std::list<Node*> children;

	OperatorNode();	
	std::string to_str() = 0;
    void dumps_str(std::stringstream& ss, int depth=0);
	virtual std::string to_asm() = 0;
};

class PlusNode : public OperatorNode {
	public:

	PlusNode();
	std::string to_str();
	std::string to_asm();
};

class MinusNode : public OperatorNode {
	public:

	MinusNode();
	std::string to_str();
	std::string to_asm();
};

/*
 
Assignments (type, operands)
	- Right to left simplifies the implementation

*/
