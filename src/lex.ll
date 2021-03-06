%top{
    #include "grammar.tab.hh"
	#include "globals.h"
    #define YY_DECL yy::parser::symbol_type yylex()

	int linenr = 1;

	void log(std::string message, std::string text){
		if (debug_lex == true)
			std::cout << message << ": " << text << std::endl;
	}
}

%option noyywrap nounput batch noinput

%%

[0-9]+\.[0-9]+			{ log("float", yytext); return yy::parser::make_FLOAT(yytext); }
[0-9]+					{ log("int", yytext); return yy::parser::make_INT(yytext); }

\+						{ log("plus",yytext); return yy::parser::make_PLUS(); }
-						{ log("minus",yytext); return yy::parser::make_MINUS(); }	
=						{ log("equals",yytext); return yy::parser::make_EQUALS(); }

[A-Za-z][A-Za-z0-9\_]*	{ log("varname", yytext); return yy::parser::make_VARNAME(yytext); }
\(						{ log("parleft", yytext); return yy::parser::make_PAR_LEFT(); }
\)						{ log("parright", yytext); return yy::parser::make_PAR_RIGHT(); }
\{						{ log("braceleft", yytext); return yy::parser::make_BRACE_LEFT(); }
\}						{ log("braceright", yytext); return yy::parser::make_BRACE_RIGHT(); }
,						{ log("comma",yytext); return yy::parser::make_COMMA(); }

\n						{ log("newline",""); linenr++; return yy::parser::make_NEWLINE(); }
;						{ log("semicolon",yytext); return yy::parser::make_SEMICOLON(); }
<<EOF>>					{ log("end",""); return yy::parser::make_QUIT(); }

%%

void set_input_file(const char* filename){
	yyin = fopen(filename, "r");
}

