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
  - arraynumsum.dcf : prints sum of all the elements in an array.
  - bubble.dcf : sorts array using mbubble sort algorithm.
  - maxmin.dcf : prints max and min element of an array.
  - netmax.dcf : prints the second largest element in an array.
  - sumn.dcf : print sum of first n elements.
