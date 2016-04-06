%top{
    #include "grammar.tab.hh"
	#include "globals.h"
    #define YY_DECL yy::parser::symbol_type yylex()

	int linenr = 0;

	void log(std::string message, std::string text){
		if (debug_lex == true)
			std::cout << message << ": " << text << std::endl;
	}
}

%option noyywrap nounput batch noinput

%%

[0-9]+\.[0-9]+		{ log("float", yytext); return yy::parser::make_floatnum(yytext); }
[0-9]+				{ log("int", yytext); return yy::parser::make_intnum(yytext); }
\+					{ log("plus",yytext); return yy::parser::make_plus(yytext); }
-					{ log("minus",yytext); return yy::parser::make_minus(yytext); }

<<EOF>>				{ log("end",""); return yy::parser::make_QUIT(); }

%%

void set_input_file(const char* filename){
	yyin = fopen(filename, "r");
}

