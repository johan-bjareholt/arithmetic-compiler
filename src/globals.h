#pragma once

extern void set_input_file(const char*);
extern bool debug_lex;
extern bool debug_cfg;
extern int linenr;

class BlockNode;
extern BlockNode* root;

class VarTable;
extern VarTable roottable;

