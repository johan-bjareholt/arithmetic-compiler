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
	virtual std::string to_asm() = 0;
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
    void dumps_str(std::stringstream& ss, int depth=0);
};

class BlockNode : public ContainerNode {
	public:
	BlockNode();
	std::string to_str();
	std::string to_asm();
};

class ArglistNode : public ContainerNode {
	public:
	ArglistNode();
	std::string to_str();
	std::string to_asm();
};

class ParlistNode : public ContainerNode {
	public:
	ParlistNode();
	std::string to_str();
	std::string to_asm();
};


class DeclarationNode : public Node {
	public:
	std::string name;
	std::string type; // TODO: change to TypeNode
	DeclarationNode(std::string type, std::string varname);
	std::string to_str();
	std::string to_asm();
	void dumps_str(std::stringstream& ss, int depth);
};

class DecllistNode : public ContainerNode {
	public:
	DecllistNode();
	std::string to_str();
	std::string to_asm();
};

/*
   Funcdef
*/

class FuncdefNode : public Node {
	public:
	// type
	ParlistNode* args = nullptr;
	BlockNode* codeblock = nullptr;
	FuncdefNode(DeclarationNode* declnode, ParlistNode* args, BlockNode* codeblock);
	std::string to_str();
	std::string to_asm();
	void dumps_str(std::stringstream& ss, int depth);
};



/*

	Types

*/

class TypeNode : public Node {
	public:
	std::string value;
	TypeNode();	
	virtual void dumps_str(std::stringstream& ss, int depth);
};


class FunccallNode : public TypeNode {
	public:
	std::string name;
	ArglistNode* args = nullptr;

	FunccallNode(std::string name, ArglistNode* args);
	void dumps_str(std::stringstream& ss, int depth);
	std::string to_str();
	std::string to_asm();
};



class ReferenceNode : public TypeNode {
	public:
	ReferenceNode(std::string value);
	std::string to_str();
	std::string to_asm();
};

class DataNode : public TypeNode {
	public:
	int bsize;

	DataNode(int bsize);
};

class IntNode : public DataNode {
	public:
	IntNode(std::string value);
	std::string to_str();
	std::string to_asm();
};

class FloatNode : public DataNode {
	public:
	FloatNode(std::string value);
	std::string to_str();
	std::string to_asm() = 0;
};


/*

  Operators 
 
*/


class OperatorNode : public ContainerNode {
	public:
	OperatorNode();	
	std::string to_str() = 0;
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
 
	Assignment

*/

class AssignmentNode : public Node {
	public:
	std::string name;
	Node* value;

	AssignmentNode(std::string, Node&);
	void dumps_str(std::stringstream& ss, int depth);
	std::string to_str();
	std::string to_asm();
};


