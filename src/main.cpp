#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <typeinfo>
#include "grammar.tab.hh"

#include "globals.h"
#include "vartable.h"
#include "node.h"

void yy::parser::error(const std::string& err){
    std::cout << "It's one of the bad ones... " << err << std::endl;
    exit(-1);
}

void setup();
void parse_args(int argc, char** argv);

bool debug_lex = true;
bool debug_cfg = true;

std::string inputfile = "";
std::string outputfile = "program.s";

VarTable roottable;

int main(int argc, char** argv){
	parse_args(argc, argv);
	setup();
	// Build ParseTree
	yy::parser parser;
	if (parser.parse()){
		std::cout << "Parsing failed" << std::endl;
		exit(-1);
	}

	// Output ParseTree
	std::stringstream ss;
	root->dumps_str(ss);
	std::cout << ss.str();
	ss.clear();

	// Convert tree to sequential
	std::ofstream of (outputfile, std::ofstream::out);

	// Convert sequential to assembly
	ContainerNode* cn = root;
	cn.push_back()
	std::stringstream codestream;
	for (std::list<Node*>::iterator i = cn->children.begin(); i != cn->children.end(); i++){
		Node* child = *i;
		if (typeid(child) == typeid(TypeNode*)){}
		else if (dynamic_cast<OperatorNode*>(child) != nullptr){
			codestream << ((OperatorNode*)child)->to_asm();
		}
		else if (dynamic_cast<FunccallNode*>(child) != nullptr){
			codestream << ((FunccallNode*)child)->to_asm();
		}
		else if (dynamic_cast<AssignmentNode*>(child) != nullptr){
			codestream << ((AssignmentNode*)child)->to_asm();
		}
		codestream << std::endl;
	}


	// Get all global variables
	std::stringstream datastream;
	datastream << "_CompilerInfoStr: .asciz \"arithmetic-compiler v0.1 alpha\"" << std::endl;
	for (std::pair<std::string, DataNode*> entry : roottable.table){
		std::cout << entry.first << std::endl;
		datastream << "_" << entry.first << ": .space "<< entry.second->bsize << std::endl;
	}

	// Data
	of << ".data" << std::endl;
	of << std::endl;
	of << datastream.str();
	of << std::endl;
	of << std::endl;
	// Text
	of << ".text" << std::endl;
	of << std::endl;
	// Main function
	of << ".global main" << std::endl;
	of << "main:" << std::endl;
	of << "    subq $8,%rsp" << std::endl; // Fix stack alignment
	// Print compiler info
	of << "    movq $_CompilerInfoStr,%rdi" << std::endl; // Set output string as arg1
	of << "    call prints" << std::endl; // Call puts
	of << std::endl;
	// Insert code
	of << codestream.str();
	// Exit
	of << "    call exit" << std::endl;
    return 0;
}


void setup(){
	// Setup input file
	if (!inputfile.empty())
		set_input_file(inputfile.c_str());
	else
		inputfile = "stdin";
	std::cout << "Input: " << inputfile << std::endl;
	std::cout << "Output: " << outputfile << std::endl;
}


void parse_args(int argc, char** argv){
	for (int i=1; i<argc; i++){
		int len = strlen(argv[i]);
		if (len >= 2 && argv[i][0] == '-'){
			switch (argv[i][1]){
				case 'o':
					if (i+1 > argc){
						std::cout << "-o flag needs an argument" << std::endl;
						exit(-1);
					}
					else {
						i++;
						outputfile = std::string(argv[i]);
					}
					break;
				default:
					std::cout << "Unknown flag " << argv[i];
					exit(-1);
			}
		}
		else {
			inputfile = std::string(argv[i]);
		}
	}
}
