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

exp		: value
	 	{
			$$ = $1;
		}

value	: intnum
	 	{
			$$ = new IntNode(std::stoi($1));
	 	}
		| floatnum
		{
			$$ = new FloatNode(std::stof($1));
		}
		;
