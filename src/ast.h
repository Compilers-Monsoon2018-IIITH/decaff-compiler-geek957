#include<bits/stdc++.h>
using namespace std;


class AST;
class Program;
class Visitor
{
	public:
		virtual int visit(AST *vis){}
		virtual int visit(Program *vis){}
		// virtual int visit(statlist *sta){}
		// virtual int visit(stat *sta){}
		// virtual int visit(bl *sta){}
		// virtual int visit(expr *sta){}
		// virtual int visit(binexp *sta){}
		// virtual int visit(unexp *sta){}
		// virtual int visit(loc *sta){}
		// virtual int visit(nu *sta){}
		// virtual int visit(ab *sta){}
		// virtual int visit(lf *sta){}
		// virtual int visit(fors *sta){}
		// virtual int visit(gotos *sta){}
		// virtual int visit(lab *sta){}
		// virtual int visit(ifs *sta){}
		// virtual int visit(whiles *sta){}
		// virtual int visit(print *sta){}
		// virtual int visit(read *sta){}
		// virtual int visit(ass *sta){}
};

class AST
{
	public:
  	AST();
  	virtual int accept(Visitor *v);

};

class Program:public AST
{	public:
  	///declarlist *de;
  	// statlist *se;
  	Program();
 //  	Program(class fieldDeclarations *fields, class methodDeclarations *methods) {
	//     this->methods = methods;
	//     this->fields = fields;
	//     // this->compilerConstructs = new Constructs();
	// }
  	// Astprogram(){}
  	// Astprogram(class statlist *s)
  	// {
  	// //  this->de=d;
   //  	this->se=s;

  	// }
  	virtual int accept(Visitor *v);
};


class DFS:public Visitor
{
public:
    // vector<statlist *>sa;
    // interpret(vector<statlist *>s){
    //   this->sa=s;
    // }
    int visit(Program *vis);
};