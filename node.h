#pragma once

#include <sstream>
#include <list>

class Node {
    public:
	int srcline;
	virtual std::string to_str() = 0;
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

};

class IntNode : public TypeNode {
	public:
	int value;

	IntNode(int value);
	std::string to_str();
};

class FloatNode : public TypeNode {
	public:
	float value;

	FloatNode(float value);
	std::string to_str();
};

/*
 
Assignments (type, operands)
	- Right to left simplifies the implementation
Containers


 */
