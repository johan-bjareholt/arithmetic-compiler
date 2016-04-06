#pragma once

#include <sstream>
#include <list>

class Node {
    public:
	int srcline;
	virtual std::string to_str() = 0;
	virtual void dumps_str(std::stringstream& ss, int depth) = 0;
};


class ContainerNode : public Node {
	public:
	std::string tag;
    std::list<Node*> children;
	ContainerNode();
    ContainerNode(std::string tag);
	std::string to_str();
    void dumps_str(std::stringstream& ss, int depth=0);
};

class TypeNode : public Node {
	public:
	std::string value;
	
	void dumps_str(std::stringstream& ss, int depth);
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


class OperatorNode : public Node {
	public:
	std::list<Node*> children;
	
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
Containers

*/
