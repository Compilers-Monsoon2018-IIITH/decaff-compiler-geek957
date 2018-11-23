#include "ast.h"
#include <bits/stdc++.h>
#include <string.h> // strdup
#include <stdio.h> // printf
#include <stdarg.h>
#include <string.h>
#include <vector>
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/Interval.h"
#include <llvm/IR/CFG.h>
#include "llvm/IR/BasicBlock.h"
#include <llvm/IR/Function.h>
#include <utility>
#include <llvm/IR/Value.h>

using namespace llvm;
using namespace std;

Constructs::Constructs() {
    this->Builder = new IRBuilder<>(Context);
    this->loops = new std::stack<loopInfo*>();
    errors = 0;
    this->TheModule = new Module("Decaf compiler", Context);
    this->TheFPM = new llvm::legacy::FunctionPassManager(TheModule);
    // TheFPM->add(createInstructionCombiningPass());
    // // Reassociate expressions.
    // TheFPM->add(createReassociatePass());
    // // Eliminate Common SubExpressions.
    // TheFPM->add(createGVNPass());
    // // Simplify the control flow graph (deleting unreachable blocks, etc).
    // TheFPM->add(createCFGSimplificationPass());
    TheFPM->doInitialization();
}

AllocaInst *Constructs::CreateEntryBlockAlloca(Function *TheFunction, std::string VarName, std::string type) {
    /* Get the builder for current context */
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(this->Context), 0, VarName);
    } else if (type == "boolean") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(this->Context), 0, VarName);
    }
    return alloca_instruction;
}


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
  this->compilerConstructs = new Constructs();
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

Value *Program::generateCode()
{
  Value *v;
  if(fields!=NULL)
  {
    cout<<"Entered Fields\n";
    v=fields->generateCode(this->compilerConstructs);
    if(v==nullptr)
    {
      // cerr<<"Invalid field Declarations"<<endl;
          return nullptr;
    }
  }
  if(methods!=NULL)
  {
    v=methods->generateCode(this->compilerConstructs);
    
    if(v==nullptr)
    {
      // reportError("Invalid method Declarations");
          return nullptr;
    }
  }
  return v;
}

void Program::generateCodeDump()
{
  cerr << "Generating LLVM IR Code\n";
    this->compilerConstructs->TheModule->print(llvm::outs(), nullptr);
}

void Field_declarations::Push_back(Field_declaration *field_declaration)
{
  declaration_list.push_back(field_declaration);
}

Value *Field_declarations::generateCode(Constructs *compilerConstructs)
{
  cout<<"Entered field_declarations\n";
  for(auto &i:declaration_list)
  {
    cout<<"Iterating field_declarations\n";
    i->generateCode(compilerConstructs);
  }
  Value *v=ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
  return v;
}




Field_declaration::Field_declaration(string dataType, Var_declarations *var_declarations)
{
  this->dataType = dataType;
  this->var_list = var_declarations->getVarsList();
}

Value *Field_declaration::generateCode(Constructs *compilerConstructs)
{
  cout<<"Entered Field_declaration\n";
  llvm::Type *ty = nullptr;
  cout<<"datatype "<<dataType<<endl;
  if(dataType=="int")
  {
    cout<<"entered Int\n";
    ty = Type::getInt32Ty(compilerConstructs->Context);
    cout<<"Exited Int\n";
  }
  else if(dataType=="boolean")
  {
    cout<<"entered boolean\n";
    // cout<<compilerConstructs->Context<<endl;
    ty = Type::getInt1Ty(compilerConstructs->Context);
    cout<<"Exited boolean\n";
  }
  cout<<"Done with checking type\n";

  for(auto var: var_list)
  {
    cout<<"entered var_list loop\n";
    if(var->isArray())
    {
      ArrayType *arrType = ArrayType::get(ty, var->getLength());
      GlobalVariable *gv = new GlobalVariable(*(compilerConstructs->TheModule), arrType, false,
                                                    GlobalValue::ExternalLinkage, nullptr,
                                                    var->getname());
            gv->setInitializer(ConstantAggregateZero::get(arrType));
    }
    else 
    {
            GlobalVariable *gv = new GlobalVariable(*(compilerConstructs->TheModule), ty, false,
                                                    GlobalValue::ExternalLinkage, nullptr,
                                                    var->getname());
            gv->setInitializer(Constant::getNullValue(ty));
        }
  }
  Value *v = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    return v;

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

Value *Method_declarations::generateCode(Constructs *compilerConstructs)
{
  Value *V = ConstantInt::get(compilerConstructs->Context, APInt(32, 0));
  for(auto &i:method_declaration_list)
  {
    V=i->generateCode(compilerConstructs);
    if(V==nullptr)
      return V;
  }
  return V;
}


Method_declaration::Method_declaration(string method_type, string name, Method_args_declarations *method_args_declarations, Block *block)
{
  this->method_type = method_type;
  this->name = name;
  this->method_args_declarations = method_args_declarations;
  this->block = block;
}

Function* Method_declaration::generateCode(Constructs *compilerConstructs)
{
    std::vector<std::string> argNames;
    std::vector<std::string> argTypes;
    std::vector<class Method_args_declaration *> args;
    if(method_args_declarations!=NULL)
    {
      args = method_args_declarations->getArgList();
    }

    std::vector<Type *> arguments;
    auto arg_size = args.size();
    for (auto &arg : args) {
        std::string arg_type = arg->getType();
        std::string arg_name = arg->getName();
        if (arg_type == "int") 
        {
            arguments.push_back(Type::getInt32Ty(compilerConstructs->Context));
        } else if (arg_type == "boolean") 
        {
            arguments.push_back(Type::getInt1Ty(compilerConstructs->Context));
        } 
        // else {
        //     compilerConstructs->errors++;
        //     cerr<<"Arguments can only be int or boolean"<<endl;
        //     return nullptr;
        // }
        argTypes.emplace_back(arg_type);
        argNames.emplace_back(arg_name);
    }

    Type *returnType;
    /* Get the return Type */
    if (method_type == "int") {
        returnType = Type::getInt32Ty(compilerConstructs->Context);
    } else if (method_type == "boolean") {
        returnType = Type::getInt1Ty(compilerConstructs->Context);
    } else if (method_type == "void") {
        returnType = Type::getVoidTy(compilerConstructs->Context);
    } else {
        compilerConstructs->errors++;
        cerr<<"Invalid Return Type for " + name + ". Return Type can only be int or boolean or bool"<<endl;
        return nullptr;
    }

    FunctionType *FT = llvm::FunctionType::get(returnType, arguments, false);
    Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, name, compilerConstructs->TheModule);

    unsigned Idx = 0;
    for (Function::arg_iterator AI = F->arg_begin(); Idx != arg_size; ++AI, ++Idx) {
        AI->setName(argNames[Idx]);
    }

    /* Create a New block for this Function */
    BasicBlock *BB = BasicBlock::Create(compilerConstructs->Context, "entry", F);
    compilerConstructs->Builder->SetInsertPoint(BB);
    Idx = 0;

    /* Allocate memory for the arguments passed */
    for (auto &Arg : F->args()) {
        AllocaInst *Alloca = compilerConstructs->CreateEntryBlockAlloca(F, argNames[Idx], argTypes[Idx]);
        compilerConstructs->Builder->CreateStore(&Arg, Alloca);
        compilerConstructs->NamedValues[argNames[Idx]] = Alloca;
        Idx++;
    }

    Value *RetVal = block->generateCode(compilerConstructs);
    if (RetVal) {
        /* make this the return value */
        if (method_type != "void")
            compilerConstructs->Builder->CreateRet(RetVal);
        else
            compilerConstructs->Builder->CreateRetVoid();
        /// Iterate through each basic block in this function and remove any dead code
        // for (auto &basicBlock : *F) {
        //     BasicBlock *block = &basicBlock;
        //     removeDeadCode(block);
        // }
        /* Verify the function */
        verifyFunction(*F);
        compilerConstructs->TheFPM->run(*F);
        return F;
    }

    /* In case of errors remove the function */
    F->eraseFromParent();
    return nullptr;


}




void Method_args_declarations::Push_back(Method_args_declaration *method_args_declaration)
{
  this->method_args_declaration_list.push_back(method_args_declaration);
}

vector<class Method_args_declaration *> Method_args_declarations::getArgList() {
    return method_args_declaration_list;
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

Value* Block::generateCode(Constructs *compilerConstructs)
{
  Value *V;
    std::map<std::string, llvm::AllocaInst *> Old_vals;
    if(field_method_declarations!=NULL)
    {
      V = field_method_declarations->generateCode(Old_vals, compilerConstructs);
      if (V == nullptr) {
          return V;
      }
  }
  if(statements!=NULL)
  {
      // V=statements->generateCode(compilerConstructs);
      for (auto it = Old_vals.begin(); it != Old_vals.end(); it++) {
          compilerConstructs->NamedValues[it->first] = Old_vals[it->first];
      }
  }
    return V;


}



void Field_method_declarations::Push_back(Field_method_declaration *field_method_declaration)
{
  declaration_list.push_back(field_method_declaration);
}

Value* Field_method_declarations::generateCode(map<string, AllocaInst *> &oldValues, Constructs *compilerConstructs)
{
  Value *v = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    for (auto &decl : declaration_list) {
        /// Generate the code for each declaration
        v = decl->generateCode(oldValues, compilerConstructs);
        if (v == nullptr) {
            return v;
        }
    }
    return v;
}



Field_method_declaration::Field_method_declaration(string dataType, Var_method_declarations *var_method_declarations)
{
  this->dataType = dataType;
  this->var_list = var_method_declarations->getVarsList();
}

Value* Field_method_declaration::generateCode(map<string, llvm::AllocaInst *> &Old_vals, Constructs *compilerConstructs)
{
  llvm::Function *TheFunction = compilerConstructs->Builder->GetInsertBlock()->getParent();
    for (const auto &var : var_list) {
        string varName = var->getName();
        llvm::Value *initval = nullptr;
        llvm::AllocaInst *Alloca = nullptr;
        if (dataType == "int") {
            initval = ConstantInt::get(compilerConstructs->Context, APInt(32, 0));
            Alloca = compilerConstructs->CreateEntryBlockAlloca(TheFunction, varName, "int");
        } else if (dataType == "boolean") {
            initval = ConstantInt::get(compilerConstructs->Context, APInt(1, 0));
            Alloca = compilerConstructs->CreateEntryBlockAlloca(TheFunction, varName, "boolean");
        }
        compilerConstructs->Builder->CreateStore(initval, Alloca);
        /* Store the old value to old_vals and new value to named values */
        Old_vals[varName] = compilerConstructs->NamedValues[varName];
        compilerConstructs->NamedValues[varName] = Alloca;
    }
    Value *v = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    return v;
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