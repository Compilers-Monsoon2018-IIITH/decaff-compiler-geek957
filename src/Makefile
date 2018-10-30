parser: parser.ypp scanner.l ast.h ast.cpp
		bison -d parser.ypp
		flex scanner.l
		g++ -o parser parser.tab.cpp lex.yy.c ast.cpp -ll
