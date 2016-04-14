#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <typeinfo>
#include "grammar.tab.hh"

#include "globals.h"
#include "vartable.h"
#include "variable.h"
#include "func.h"
#include "nodes.h"
#include "classes.h"

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
	BlockNode* rb = root;

	// Get all global variables
	std::stringstream datastream;
	std::stringstream funcdefstream;
	datastream << "_CompilerInfoStr: .asciz \"arithmetic-compiler v0.1 alpha\"" << std::endl;
	for (std::pair<std::string, Variable*> entry : roottable.table){
		std::string& varname = entry.first;
		if (dynamic_cast<Class*>(entry.second)){
			Class* object = (Class*) entry.second;
			datastream << "_" << varname << ": .space "<< object->bytesize << std::endl;
		}
		else if (dynamic_cast<Function*>(entry.second)){
			Function* funcdef = (Function*) entry.second;
			funcdefstream << std::endl;
			funcdefstream << ".global " << varname << std::endl;
			funcdefstream << varname << ":" << std::endl;
			funcdefstream << funcdef->to_asm() << std::endl;
			funcdefstream << "    ret" << std::endl;
			funcdefstream << std::endl;
		}
	}

	// Data section
	of << ".data" << std::endl;
	of << std::endl;
	of << datastream.str();
	of << std::endl;
	of << std::endl;

	// Text section
	of << ".text" << std::endl;
	of << std::endl;
	// Main function
	of << ".global main" << std::endl;
	of << "main:" << std::endl;
	of << "    movq $_CompilerInfoStr, %rdi" << std::endl;
	of << "    call prints" << std::endl << std::endl; // Print compiler info string
	of << rb->to_asm(); // Insert main function code
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
