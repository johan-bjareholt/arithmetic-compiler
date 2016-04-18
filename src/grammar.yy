%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%define api.token.constructor
%code requires{
	#include "globals.h"
	#include "nodes.h"
}
%code{
    #include <string>
    #define YY_DECL yy::parser::symbol_type yylex()

    YY_DECL;

    BlockNode* root;
}

%type <BlockNode*> block
%type <Node*> exp
%type <TypeNode*> value
%type <OperatorNode*> binop
%type <ReferenceNode*> reference
%type <ArglistNode*> arglist
%type <ParlistNode*> parlist
%type <DeclarationNode*> declaration
%type <FuncdefNode*> funcdef
%type <FunccallNode*> funccall
%type <Node*> command
%type <void*> cmdend



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
%token BRACE_LEFT
%token BRACE_RIGHT
%token COMMA

%token NEWLINE
%token SEMICOLON
%token QUIT 0 "end of file"

%%

block	: command
	  	{
			$$ = new BlockNode();
			$$->children.push_back((Node*)$1);
			root = (BlockNode*) $$;
		}
		| block command
		{
			$$ = $1;
			$$->children.push_back((Node*)$2);
			root = (BlockNode*) $$;
		}
		;

cmdend	: NEWLINE {}
	   	| SEMICOLON {}
		;

command : exp cmdend {
			$$ = $1;
		}
		| VARNAME EQUALS exp cmdend {
			$$ = new AssignmentNode($1, *$3);
		}
		| funcdef cmdend {
			$$ = $1;
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

arglist	: /* empty */
		{
			$$ = new ArglistNode();
		}
		| exp
		{
			$$ = new ArglistNode();
			$$->children.push_back($1);
		}
		| arglist COMMA exp
		{
			$$ = $1;
			$$->children.push_back($3);
		}

parlist	: /* empty */
		{
			$$ = new ParlistNode();
		}
		| declaration
		{
			$$ = new ParlistNode();
			$$->children.push_back($1);
		}
		| parlist COMMA declaration
		{
			$$ = $1;
			$$->children.push_back($3);
		}

declaration: VARNAME VARNAME
		{
			$$ = new DeclarationNode($1, $2);
		}
		;

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

funcdef	: declaration PAR_LEFT parlist PAR_RIGHT BRACE_LEFT block BRACE_RIGHT
		{
			// TODO: add type returns, do not ignore type varname
			$$ = new FuncdefNode($1, $3, $6);
		}

funccall: VARNAME PAR_LEFT arglist PAR_RIGHT
		{
			$$ = new FunccallNode($1, $3);
		}

reference: VARNAME 
		{
			$$ = new ReferenceNode($1);
		}
