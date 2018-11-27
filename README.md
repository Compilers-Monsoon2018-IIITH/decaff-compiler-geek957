# Decaf Compiler
## File Structure
- src
  - Makeile : 
    - use "make" to run
  - parser.ypp : 
    - Reading the code from a file. Creating nodes of AST tree
  - scanne.l : 
    - Return tokens one by one to the parser file
  - ast.h : 
    - contains all the class and method declarations.
    - Has code for traversing the AST tree using vsitor design pattern
    - All semantic erros are handled while creating the AST tree
  - ast.cpp
    - All methods are written here.
    - generate code functions were used for creating LLVM-IR
- test-programs
  - 17 dcf programs, for some of them are outputs are in sample outputs section 
  
## Running
```
- bison -d parser.ypp
- bison -d parser.ypp
- g++ -std=c++11 -o parser parser.tab.cpp lex.yy.c ast.cpp -ll -g -ldl -lfl `llvm-config-6.0 --cppflags --libs --libfiles core --ldflags --system-libs`
- ./parser inputfile
- lli-6.0 outfile
```
## Description
## Sample output
### arraysum.dcf
```
rallaakhil@rallaakhil:~/compilers/project/phase-2$ make
bison -d parser.ypp
flex scanner.l
# g++ -std=c++11 -o parser parser.tab.cpp lex.yy.c ast.cpp -ll
g++ -std=c++11 -o parser parser.tab.cpp lex.yy.c ast.cpp -ll -g -ldl -lfl `llvm-config-6.0 --cppflags --libs --libfiles core --ldflags --system-libs`
rallaakhil@rallaakhil:~/compilers/project/phase-2$ ./parser test-programs/arraysum.dcf 
Starting
Parsing Over
Started dfs
Done dfs
Started generating LLVM-IR
LLVM-IR generated
rallaakhil@rallaakhil:~/compilers/project/phase-2$ lli-6.0 outfile
The sum of given vector is : 45
```

## Output for some more programs
### bubble.dcf
```
rallaakhil@rallaakhil:~/compilers/project/phase-2$ ./parser test-programs/bubble.dcf 
Starting
Parsing Over
Started dfs
Done dfs
Started generating LLVM-IR
LLVM-IR generated
rallaakhil@rallaakhil:~/compilers/project/phase-2$ lli-6.0 outfile
The final sorted order  is : 
1 2 3 4 5 6 7 8 9 10
```
### quick_sort.dcf
```
rallaakhil@rallaakhil:~/compilers/project/phase-2$ ./parser test-programs/quick_sort.dcf 
Starting
Parsing Over
Started dfs
Done dfs
Started generating LLVM-IR
LLVM-IR generated
rallaakhil@rallaakhil:~/compilers/project/phase-2$ lli-6.0 outfile
sorted array : 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 
```
### mergesort.dcf
```
rallaakhil@rallaakhil:~/compilers/project/phase-2$ ./parser test-programs/merge_sort.dcf 
Starting
Parsing Over
Started dfs
Done dfs
Started generating LLVM-IR
LLVM-IR generated
rallaakhil@rallaakhil:~/compilers/project/phase-2$ lli-6.0 outfile
sorted array : 1 2 3 4 5 6 7 8 9 10
```
### gcd.dcf
```
rallaakhil@rallaakhil:~/compilers/project/phase-2$ ./parser test-programs/gcd.dcf 
Starting
Parsing Over
Started dfs
Done dfs
Started generating LLVM-IR
LLVM-IR generated
rallaakhil@rallaakhil:~/compilers/project/phase-2$ lli-6.0 outfile
gcd is 6
```
