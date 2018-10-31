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
Program::Program(Field_declarations *field_declarations, Method_declarations *method_declarations)
{
  this->fields = field_declarations;
  this->methods = method_declarations;
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



void Method_declarations::Push_back(Method_declaration *method_declaration)
{
  method_declaration_list.push_back(method_declaration);
}


Method_declaration::Method_declaration(string method_type, string name, Method_args_declarations *method_args_declarations, Block *block)
{
  this->method_type = method_type;
  this->name = name;
  this->method_args_declarations = method_args_declarations;
  this->block = block;
}




void Method_args_declarations::Push_back(Method_args_declaration *method_args_declaration)
{
  this->method_args_declaration_list.push_back(method_args_declaration);
}




Method_args_declaration::Method_args_declaration(string arg_type, string name)
{
  this->arg_type = arg_type;
  this->name = name;
}



Block::Block(Field_method_declarations *field_method_declarations)
{
  this->field_method_declarations = field_method_declarations;
}




void Field_method_declarations::Push_back(Field_method_declaration *field_method_declaration)
{
  declaration_list.push_back(field_method_declaration);
}




Field_method_declaration::Field_method_declaration(string dataType, Var_method_declarations *var_method_declarations)
{
  this->dataType = dataType;
  this->var_list = var_method_declarations->getVarsList();
}



void Var_method_declarations::Push_back(Var_method_declaration *var_method_declaration) {
    var_declaration_list.push_back(var_method_declaration);
}
vector<Var_method_declaration *> Var_method_declarations::getVarsList() {
    return var_declaration_list;
}




Var_method_declaration::Var_method_declaration(string name) {
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