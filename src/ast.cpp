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



Block::Block(Field_method_declarations *field_method_declarations, Statements *statements)
{
  this->field_method_declarations = field_method_declarations;
  this->statements = statements;
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


// Statements
void Statements::Push_back(Statement * statement)
{
  this->statement_list.push_back(statement);
}

// Statement


// Assignment
Assignment::Assignment(Location *location, Assign_op *assign_op, Expr *expr)
{
  this->location = location;
  this->assign_op = assign_op;
  this->expr = expr;
}


//Function_call


//If_else
If_else::If_else(Expr *expr, Block *block1, Block *block2)
{
  this->expr = expr;
  cout<<expr->lit_type<<endl;
  if(expr->lit_type!=1)
  {
    cout<<"If condition should be boolen"<<endl;
    exit(0);
  }
  this->block1 = block1;
  this->block2 = block2;
}


//For
Forr::Forr(string var_name, Expr *expr1, Expr *expr2, Block *block)
{
  this->var_name = var_name;
  this->expr1 = expr1;
  this->expr2 = expr2;
  this->block = block;
}


//Return
Return::Return(Expr *expr)
{
  this->expr = expr;
}

//Break

//Continue

//Assign_op
Assign_op::Assign_op(string operation)
{
  this->operation = operation;
}

// Method_call
Method_call::Method_call(string name, Exprs *exprs)
{
  this->name = name;
  this->exprs = exprs;
  this->expr_type = 1;
  this->lit_type = 0;
}

//Call_out
Call_out::Call_out(string print_var, Call_out_args *call_out_args)
{
  this->print_var = print_var;
  this->call_out_args = call_out_args;
}

// Call_out_args
void Call_out_args::Push_back(Call_out_arg *call_out_arg)
{
  Call_out_arg_declaration_list.push_back(call_out_arg);
}


// Call_out_arg
Call_out_arg::Call_out_arg(class Expr *expr)
{
  this->expr = expr; 
}
Call_out_arg::Call_out_arg(string Literal)
{
  this->Literal = Literal; 
}

//Location
Location::Location(string name)
{
  this->name = name;
  this->lit_type = 0;
  this->expr_type = 0; 
}
Location::Location(string name, Expr *expr)
{
  this->name = name;
  this->expr = expr;
}


//Exprs
void Exprs::Push_back(Expr *expr)
{
  this->Expr_declaration_list.push_back(expr);
}

// Expr

//Literal

// Binary_expr
Binary_expr::Binary_expr(Expr *expr1, string operation, Expr *expr2)
{
  this->expr1 = expr1;
  this->operation = operation;
  this->expr2 = expr2;
  this->expr_type = 3;
  cout<<"Binary "<<expr1->lit_type<<" "<<expr2->lit_type<<" "<<operation<<endl;
  string a =operation;
  if(((a=="+" or a=="-") or (a=="*" or (a=="/" or a=="%"))))
  {
    if(!(expr1->lit_type==0 && expr2->lit_type==0))
    {
      cout<<"Arithemetic expression should have type ints on two sides\n";
      exit(0);
    }
    cout<<"Arithemetic Expression "<<operation<<endl;
    this->lit_type = 0;
  }
  else if(((a=="<" or a==">") or (a=="<=" or a==">=")))
  {
    if(!(expr1->lit_type==0 && expr2->lit_type==0))
    {
      cout<<"Relation expression should have type ints on two sides\n";
      exit(0);
    }
    cout<<"Relation operation\n";
    this->lit_type = 1;
  }
  cout<<"Binary expression "<<this->lit_type<<endl;
}

//Unary_expr
Unary_expr::Unary_expr(string operation, Expr *expr)
{
  this->expr = expr;
  this->operation = operation;
  this->expr_type = 4;
  // cout<<"unary expression "<<operation<<endl;
  if(operation== "!" and expr->lit_type!=1)
  {
    cout<<"Unary expression variable should be boolean for !\n";
    exit(0);
  }
  else if(operation=="!")
    this->lit_type = 1;
  if(operation== "-" and expr->lit_type!=0)
  {
    cout<<"Unary expression variable should be int for -\n";
    exit(0);
  }
  else if(operation=="-")
    this->lit_type = 0;
  // cout<<"unary_lit_type "<<this->lit_type<<endl;
}

//Bracket_expr
Bracket_expr::Bracket_expr(Expr *expr)
{
  this->expr = expr;
  this->expr_type = 5;
  this->lit_type = expr->lit_type;
}

//Integer_literal
Integer_literal::Integer_literal(int var)
{
  this->var = var;
  this->lit_type = 0;
  this->expr_type = 2;
  cout<<"Int_literal "<<this->lit_type<<endl;
}

//Char_literal
Char_literal::Char_literal(string var)
{
  this->var = var;
  this->lit_type = 2;
  this->expr_type = 2;
  cout<<"Bool_literal "<<this->lit_type<<endl;
}

//Bool_literal
Bool_literal::Bool_literal(string var)
{
  this->var = var;
  this->lit_type = 1;
  this->expr_type = 2;
  cout<<"Bool_literal "<<this->lit_type<<endl;
}


//
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