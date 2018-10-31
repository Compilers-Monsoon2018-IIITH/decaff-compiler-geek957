%{
#include <bits/stdc++.h>
#include "parser.tab.hpp"
#define YY_DECL extern "C" int yylex()
/*extern union Node yylval;*/
using namespace std;
int lineno = 0;
%}

number [0-9][0-9]*
id [a-zA-Z][0-9a-zA-Z]*
delim [ \t]+
char [ -~]
character   \'{char}\'
string (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])
hex_number 0x[0-9a-fA-F][0-9a-fA-F]*


%%
"class"             {printf("found class\n");return CLASS;}
"Program"			{printf("found program\n");return PROGRAM;}
"int"				{yylval.str = strdup(yytext);printf("found int\n");return TYPE;}
"boolean"			{yylval.str = strdup(yytext);printf("found boolean\n");return TYPE;}
"void"				{yylval.str = strdup(yytext);printf("found void\n");return VOID;}
"if"				{printf("found if\n");return IF;}
"for"				{printf("found for\n");return FOR;}
"return"			{printf("found return\n");return RETURN;}
"break"				{printf("found break\n");return BREAK;}
"continue"			{printf("found continue\n");return CONTINUE;}
"else"				{printf("found else\n");return ELSE;}
"callout"			{printf("found callout\n");return CALLOUT;}
"true"				{yylval.str = strdup(yytext);printf("found true\n");return BOOL_LIT;}
"false"				{yylval.str = strdup(yytext);printf("found false\n");return BOOL_LIT;}
">="				{yylval.str = strdup(yytext);printf("found ge\n");return GE;}
"<="				{yylval.str = strdup(yytext);printf("found le\n");return LE;}
"+="				{yylval.str = strdup(yytext);printf("found +=\n");return PLE;}
"-="				{yylval.str = strdup(yytext);printf("found -=\n");return SUE;}
"=="				{yylval.str = strdup(yytext);printf("found ==\n");return EE;}
"!="				{yylval.str = strdup(yytext);printf("found !=\n");return NE;}
"!"					{yylval.str = strdup(yytext);printf("found excl\n");return EXCL;}
"="					{yylval.str = strdup(yytext);printf("found =\n");return '=';}
">"					{yylval.str = strdup(yytext);printf("found gt\n");return GT;}
"<"					{yylval.str = strdup(yytext);printf("found lt\n");return LT;}
"+"					{yylval.str = strdup(yytext);printf("found PLUS\n");return PLUS;}
"-"					{yylval.str = strdup(yytext);printf("found minus\n");return MINUS;}
"*"					{yylval.str = strdup(yytext);printf("found mul\n");return MUL;}
"/"					{yylval.str = strdup(yytext);printf("found div\n");return DIV;}
"%"					{yylval.str = strdup(yytext);printf("found MOD\n");return MOD;}
"&&"				{yylval.str = strdup(yytext);printf("found and\n");return AND;}
"||"				{yylval.str = strdup(yytext);printf("found or\n");return OR;}
","					{printf("found ,\n");return ',';}
"{"					{printf("found {\n");return '{';}
"}"					{printf("found }\n");return '}';}
"["					{printf("found [\n");return '[';}
"]"					{printf("found ]\n");return ']';}
"("					{printf("found (\n");return '(';}
")"					{printf("found )\n");return ')';}
";"					{printf("found ;\n");return ';';}
{number}			{yylval.number = atoi(yytext);printf("found number\n");return INT_LIT;}
{hex_number}		{yylval.number = atoi(yytext);printf("found HEX_number\n");return INT_LIT;}
{id}				{yylval.str = strdup(yytext);printf("found id\n");return ID;}
{character} 		{yylval.str = strdup(yytext);printf("found char\n");return CHAR;}
\"{string}*\" 		{yylval.str = strdup(yytext);printf("found string\n");return STRING;}
{delim}				/* Ignore whitespaces tabs and newlines */
"//".*				/* Inline comments So Ignore */
"\n"		     	{printf("---------------------Line number %d\n",lineno+1);++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }
%%

