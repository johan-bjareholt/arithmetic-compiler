#pragma once
#include "node.h"

extern void set_input_file(const char*);

extern unsigned int total;
extern ContainerNode* root;
extern int linenr;

extern bool debug_lex;
extern bool debug_cfg;
