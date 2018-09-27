%{
#include "parser.tab.h"
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
"int"				{printf("found int\n");return INT;}
"boolean"			{printf("found boolean\n");return BOOLEAN;}
"void"				{printf("found void\n");return VOID;}
"if"				{printf("found if\n");return IF;}
"for"				{printf("found for\n");return FOR;}
"return"			{printf("found return\n");return RETURN;}
"break"				{printf("found break\n");return BREAK;}
"continue"			{printf("found continue\n");return CONTINUE;}
"else"				{printf("found else\n");return ELSE;}
"callout"			{printf("found callout\n");return CALLOUT;}
"true"				{printf("found true\n");return TRUE;}
"false"				{printf("found false\n");return FALSE;}
">="				{printf("found ge\n");return GE;}
"<="				{printf("found le\n");return LE;}
"+="				{printf("found +=\n");return '+=';}
"-="				{printf("found -=\n");return '-=';}
"=="				{printf("found ==\n");return EE;}
"!="				{printf("found !=\n");return NE;}
"!"					{printf("found excl\n");return EXCL;}
"="					{printf("found =\n");return '=';}
">"					{printf("found gt\n");return GT;}
"<"					{printf("found lt\n");return LT;}
"+"					{printf("found PLUS\n");return PLUS;}
"-"					{printf("found minus\n");return MINUS;}
"*"					{printf("found mul\n");return MUL;}
"/"					{printf("found div\n");return DIV;}
"%"					{printf("found MOD\n");return MOD;}
"&&"				{printf("found and\n");return AND;}
"||"				{printf("found or\n");return OR;}
","					{printf("found ,\n");return ',';}
"{"					{printf("found {\n");return '{';}
"}"					{printf("found }\n");return '}';}
"["					{printf("found [\n");return '[';}
"]"					{printf("found ]\n");return ']';}
"("					{printf("found (\n");return '(';}
")"					{printf("found )\n");return ')';}
";"					{printf("found ;\n");return ';';}
{number}			{printf("found number\n");return NUMBER;}
{hex_number}		{printf("found HEX_number\n");return HEX_NUMBER;}
{id}				{printf("found id\n");return ID;}
{character} 		{printf("found char\n");return CHAR;}
\"{string}*\" 		{printf("found string\n");return STRING;}
{delim}				/* Ignore whitespaces tabs and newlines */
"//".*				/* Inline comments So Ignore */
"\n"		     	{printf("---------------------Line number %d\n",lineno+1);++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }
%%

