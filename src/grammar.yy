%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires{
	#include "globals.h"
	#include "node.h"
}
%code{
    #include <string>
    #define YY_DECL yy::parser::symbol_type yylex()

    YY_DECL;

    RootblockNode* root;
}

%type <ContainerNode*> block
%type <Node*> exp
%type <TypeNode*> value
%type <OperatorNode*> binop
%type <ReferenceNode*> reference
%type <ArglistNode*> arglist
%type <FunccallNode*> funccall
%type <Node*> command



 /* Operators */
%token PLUS
%token MINUS
%token EQUALS

 /* Types */
%token <std::string> INT
%token <std::string> FLOAT

 /* Variable handling */
%token <std::string> VARNAME

/* Misc */
%token PAR_LEFT
%token PAR_RIGHT
%token COMMA

%token NEWLINE
%token QUIT 0 "end of file"

%%


block	: command
	  	{
			$$ = new RootblockNode();
			$$->children.push_back((Node*)$1);
			root = (RootblockNode*) $$;
		}
		| block command
		{
			$$ = $1;
			$$->children.push_back((Node*)$2);
			root = (RootblockNode*) $$;
		}
		;

command : exp NEWLINE {
			$$ = $1;
		}
		| VARNAME EQUALS exp NEWLINE {
			$$ = new AssignmentNode($1, *$3);
		}
		;

exp		: exp binop exp
		{
			$$ = $2;
			$2->children.push_back($1);
			$2->children.push_back($3);
		}
		| value
	 	{
			$$ = $1;
		}
		| funccall
		{
			$$ = $1;
		}
		| reference
		{
			$$ = $1;
		}
		;

arglist	: /* empty */ {
			$$ = new ArglistNode();
		}
		| exp {
			$$ = new ArglistNode();
			$$->children.push_back($1);
		}
		| arglist COMMA exp {
			$$ = $1;
			$$->children.push_back($3);
		}

value	: INT
	 	{
			$$ = new IntNode($1);
	 	}
		| FLOAT
		{
			std::cout << "Floats are not supported yet" << std::endl;
			exit(-1);
			//$$ = new FloatNode($1);
		}
		;

binop	: PLUS
	  	{
			$$ = new PlusNode();
		}
		| MINUS
		{
			$$ = new MinusNode();
		}
		;

funccall: VARNAME PAR_LEFT arglist PAR_RIGHT {
			$$ = new FunccallNode($1, $3);
		}

reference: VARNAME {
			$$ = new ReferenceNode($1);
		}
