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

    ContainerNode* root;
}

%type <ContainerNode*> block
%type <Node*> exp
%type <TypeNode*> value
%type <OperatorNode*> binop
%type <VariableNode*> varname
%type <FunccallNode*> funccall




 /* Operators */
%token <std::string> PLUS
%token <std::string> MINUS

 /* Types */
%token <std::string> INT
%token <std::string> FLOAT

 /* Misc */
%token <std::string> VARNAME
%token <std::string> PAR_LEFT
%token <std::string> PAR_RIGHT

%token QUIT 0 "end of file"

%%


block	: exp
	  	{
			$$ = new ContainerNode("block");
			$$->children.push_back((Node*)$1);
			root = $$;
		}
		| block exp
		{
			$$ = $1;
			$$->children.push_back((Node*)$2);
			root = $$;
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
		;

value	: INT
	 	{
			$$ = new IntNode($1);
	 	}
		| FLOAT
		{
			$$ = new FloatNode($1);
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

funccall: varname PAR_LEFT PAR_RIGHT {
			$$ = new FunccallNode($1->value);
			delete $1;
		}

varname	: VARNAME {
			$$ = new VariableNode($1);
		}
