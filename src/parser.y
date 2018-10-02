%{
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
extern char* yytext;
%}



%token CLASS
%token PROGRAM
%token INT
%token BOOLEAN
%token VOID
%token IF
%token FOR
%token RETURN
%token BREAK
%token CONTINUE
%token ELSE
%token CALLOUT
%token TRUE
%token FALSE
%token GE
%token LE
%token '+='
%token '-='
%token EE
%token NE
%token EXCL
%token '='
%token GT
%token LT
%token PLUS
%token MINUS
%token MUL
%token DIV
%token MOD
%token AND
%token OR
%token ','
%token '}'
%token '{'
%token ']'
%token '['
%token ')'
%token '('
%token ';'
%token NUMBER
%token HEX_NUMBER
%token CHAR
%token STRING
%token ID

%left EE NE
%left AND OR
%left LT GT LE GE
%left PLUS MINUS
%left MUL DIV MOD
%right EXCL '='




%%
program : CLASS  PROGRAM '{' field_decls method_decls '}'
		| CLASS  PROGRAM '{' field_decls '}'
		| CLASS  PROGRAM '{' method_decls '}'
		| CLASS  PROGRAM '{' '}'

/* FIELD DECLARATIONS */
field_decls : field_decl 
			| field_decls field_decl

field_decl : type vars_array_incl ';'

vars_array_incl : var_array_incl 
				| vars_array_incl ',' var_array_incl

var_array_incl : ID 
			   | ID '[' int_lit ']'

/* METHOD DECLARATIONS */
method_decls : method_decl 
			 | method_decls method_decl

method_decl : type ID '(' meth_arg_decls ')' block
			| type ID '(' ')' block
			| VOID ID '(' meth_arg_decls ')' block
			| VOID ID '(' ')' block

meth_arg_decls : meth_arg_decl 
			   | meth_arg_decls ',' meth_arg_decl

meth_arg_decl : type ID

block : '{' field_decls statements '}'
	  | '{' field_decls '}'
	  | '{' statements '}'
	  | '{' '}'

type : INT 
	 | BOOLEAN

statements : statement 
		   | statements statement

statement : location assign_op expr ';'
 		  | method_call ';'
 		  | IF '(' expr ')' block ELSE block
 		  | IF '(' expr ')' block
 		  | FOR ID '=' expr ',' expr block
 		  | RETURN expr ';'
 		  | RETURN ';'
 		  | BREAK ';'
 		  | CONTINUE ';'
 		  | block



assign_op : '='
		  | '+='
		  | '-=' 

method_call : ID '(' exprs ')'
			| ID '(' ')'
			| CALLOUT '(' STRING  callout_args ')'
			| CALLOUT '(' STRING ')'

exprs : expr
	  | exprs ',' expr

callout_args : ',' callout_arg 
			 | callout_args ',' callout_arg

callout_arg : expr
			| STRING

location : ID
		 | ID '[' expr ']'

expr : location
	 | method_call
	 | lit
	 | expr PLUS expr
	 | expr MINUS expr
	 | expr MUL expr
	 | expr DIV expr
	 | expr MOD expr
	 | expr LT expr
	 | expr GT expr
	 | expr LE expr
	 | expr GE expr
	 | expr EE expr
	 | expr NE expr
	 | expr AND expr
	 | expr OR expr
	 | MINUS expr
	 | EXCL expr
	 | '(' expr ')'


lit : int_lit
	| CHAR
	| bool_lit


int_lit : NUMBER
		| HEX_NUMBER



bool_lit : TRUE
		 | FALSE




%%

main(int argc, char **argv)
{
	if(argc == 1)
    {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}
	if(argc > 2)
    {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}
	printf("About to start\n");
	yyin = fopen(argv[1], "r");
	yyparse();
	printf("Parsing Over\n");
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}