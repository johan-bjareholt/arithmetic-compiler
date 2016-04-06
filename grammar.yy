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




 /* Operators */
%token <std::string> plus
%token <std::string> minus

 /* Types */
%token <std::string> intnum
%token <std::string> floatnum

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
		;

value	: intnum
	 	{
			$$ = new IntNode($1);
	 	}
		| floatnum
		{
			$$ = new FloatNode($1);
		}
		;

binop	: plus
	  	{
			$$ = new PlusNode();
		}
		| minus
		{
			$$ = new MinusNode();
		}
		;
