#include "ast.h"


// class AST
// {
//   public:
AST::AST(){}
int  AST::accept(Visitor *v){v->visit(this);}

// };

// class Program:public AST
// {	public:
  	///declarlist *de;
  	// statlist *se;
Program::Program(Field_declarations *fields_declarations)
{
  this->fields = fields_declarations;
}
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
// };


// class DFS:public Visitor
// {
// public:
    // vector<statlist *>sa;
    // interpret(vector<statlist *>s){
    //   this->sa=s;
    // }
void Field_declarations::Push_back(Field_declaration *field_declaration)
{
  declaration_list.push_back(field_declaration);
}




Field_declaration::Field_declaration(string dataType, Var_declarations *var_declarations)
{
  this->dataType = dataType;
  this->var_list = var_declarations->getVarsList();
}



void Var_declarations::Push_back(Var_declaration *var) {
    var_declaration_list.push_back(var);
}
vector<Var_declaration *> Var_declarations::getVarsList() {
    return var_declaration_list;
}




Var_declaration::Var_declaration(string name, unsigned int array_size) {
    this->declType = variableType::Array;
    this->name = name;
    this->length = array_size;
}
Var_declaration::Var_declaration(string name) {
    this->declType = variableType::Normal;
    this->name = name;
}






// int DFS::visit(Program *vis){
// 	cout<<"class Program found"<<endl;
// 	// vis->accept();
// }
// int DFS::visit(Program *vis)
// {
//   cout<<"class Program found"<<endl;
//   // vis->accept();
// }
// };