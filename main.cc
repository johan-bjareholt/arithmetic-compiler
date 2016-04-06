#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include "grammar.tab.hh"

#include "globals.h"


bool debug_lex = true;
bool debug_cfg = true;


void yy::parser::error(const std::string& err){
    std::cout << "It's one of the bad ones... " << err << std::endl;
    exit(-1);
}


int main(int argc, char** argv){
	yy::parser parser;
	if (!parser.parse()){
		std::stringstream ss;
		root->dumps_str(ss);
		std::cout << ss.str();
		ss.clear();
	}
    return 0;
}



