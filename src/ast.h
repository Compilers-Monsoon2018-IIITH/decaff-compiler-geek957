#include<bits/stdc++.h>
using namespace std;


class AST;
class Program;
class Field_declarations;
class Field_declaration;
class Var_declarations;
class Var_declaration;
class Method_declarations;
class Method_declaration;
class Method_args_declarations;
class Method_args_declaration;
class Block;
class Field_method_declarations;
class Field_method_declaration;
class Var_method_declarations;
class Var_method_declaration;

enum variableType{
    Array = 1, Normal = 2
};
class Visitor
{
	public:
		virtual int visit(AST *vis){}
		virtual int visit(Program *vis){}
		virtual int visit(Field_declarations *vis){}
    virtual int visit(Field_declaration *vis){}
    // virtual int visit(Var_declarations *vis){}
    virtual int visit(Var_declaration *vis){}
    virtual int visit(Method_declarations *vis){}
    virtual int visit(Method_declaration *vis){}
    virtual int visit(Method_args_declarations *vis){}
    virtual int visit(Method_args_declaration *vis){}
    virtual int visit(Block *vis){}
    virtual int visit(Field_method_declarations *vis){}
    virtual int visit(Field_method_declaration *vis){}
    // virtual int visit(Var_method_declarations *vis){}
    virtual int visit(Var_method_declaration *vis){}
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
  		class Field_declarations *fields;
      class Method_declarations *methods;
  		Program(class Field_declarations *, class Method_declarations *);

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
  	virtual int accept(Visitor *v){v->visit(this);}
};

class Field_declarations:public AST
{
	public:
		vector<class Field_declaration *> declaration_list;
		Field_declarations() = default;
		void Push_back(class Field_declaration *);
	virtual int accept(Visitor *v){v->visit(this);}
};


class Field_declaration:public AST
{
	public:
		string dataType;
		// class Type *typ;
		vector<Var_declaration *> var_list;
		// class Var_declarations *vars;
		Field_declaration(string, Var_declarations *);
	virtual int accept(Visitor *v){v->visit(this);}
};

class Var_declarations:public AST
{
	public:
		vector<Var_declaration *> var_declaration_list;
		Var_declarations() = default;
		void Push_back(Var_declaration *);
		vector<Var_declaration *> getVarsList();
	virtual int accept(Visitor *v){v->visit(this);}
};

class Var_declaration:public AST
{
	public:		
		variableType declType;
		unsigned int length;
		string name;
		Var_declaration(string, unsigned int);
  	explicit Var_declaration(string);
  	bool isArray() { return (declType == variableType::Array); }
  	unsigned int getLength() {return length;}
	virtual int accept(Visitor *v){v->visit(this);}
};	

class Method_declarations:public AST
{
  public:
    vector<class Method_declaration *> method_declaration_list;
    Method_declarations() = default;
    void Push_back(class Method_declaration *);
  virtual int accept(Visitor *v){v->visit(this);}
};

class Method_declaration:public AST
{
  public:
    string method_type;
    string name;
    class Method_args_declarations *method_args_declarations;
    class Block *block;
    Method_declaration(string, string, Method_args_declarations *, Block *);
  virtual int accept(Visitor *v){v->visit(this);}
};

class Method_args_declarations:public AST
{
  public:
    vector<class Method_args_declaration *> method_args_declaration_list;
    Method_args_declarations() = default;
    void Push_back(class Method_args_declaration *);
  virtual int accept(Visitor *v){v->visit(this);}
};

class Method_args_declaration:public AST
{
  public:
    string arg_type;
    string name;
    Method_args_declaration(string,string);
  virtual int accept(Visitor *v){v->visit(this);}
};

class Block:public AST
{
  public:
    class Field_method_declarations *field_method_declarations;
    Block(Field_method_declarations *);
  virtual int accept(Visitor *v){v->visit(this);}
};

class Field_method_declarations:public AST
{
  public:
    vector<class Field_method_declaration *> declaration_list;
    Field_method_declarations() = default;
    void Push_back(class Field_method_declaration *);
  virtual int accept(Visitor *v){v->visit(this);} 
};

class Field_method_declaration:public AST
{
  public:
    string dataType;
    vector<Var_method_declaration *> var_list;
    Field_method_declaration(string, Var_method_declarations *);
  virtual int accept(Visitor *v){v->visit(this);}
};

class Var_method_declarations:public AST
{
  public:
    vector<Var_method_declaration *> var_declaration_list;
    Var_method_declarations() = default;
    void Push_back(Var_method_declaration *);
    vector<Var_method_declaration *> getVarsList();
  virtual int accept(Visitor *v){v->visit(this);}
};

class Var_method_declaration:public AST
{
  public:   
    string name;
    Var_method_declaration(string);
  virtual int accept(Visitor *v){v->visit(this);}
};


// class Type:public AST
// {
// 	public:
// 		Type(string);
// 	virtual int accept(Visitor *v){v->visit(this);}
// }

// class Int_lit:public AST
// {
// 	public:
// 		Int_lit(int);
// 	virtual int accept(Visitor *v){v->visit(this);}
// }


class DFS:public Visitor
{
public:
    // vector<statlist *>sa;
    // interpret(vector<statlist *>s){
    //   this->sa=s;
    // }
    int visit(Program *vis)
    {
    	cout<<"entered Program\n";
    	if(vis->fields!=NULL)
    		vis->fields->accept(this);
      if(vis->methods!=NULL)
        vis->methods->accept(this);
    }
    int visit(Field_declarations *vis)
    {
    	cout<<"Entered Field_declarations\n";
    	for(int i=0;i<vis->declaration_list.size();i++)
    		vis->declaration_list[i]->accept(this);
    }
    int visit(Field_declaration *vis)
    {
    	cout<<"Entered Field_declaration\n";
    	cout<<"Variable Type "<<vis->dataType<<"\n";
    	for(int i=0;i<vis->var_list.size();i++)
    	{
    		vis->var_list[i]->accept(this);
    	}
    }
    // int visit(Var_declarations *vis)
    // {

    // }
    int visit(Var_declaration *vis)
    {
    	cout<<"Entered Printing Variables\n";
    	if(vis->declType==1)
    	{
    		cout<<"It's an array\n";
    		cout<<vis->name<<"\n";
    		cout<<vis->length<<"\n";
    	}
    	else
    	{
			cout<<"It's a Normal variable\n";
    		cout<<vis->name<<"\n";
    	}
    }

    int visit(Method_declarations *vis)
    {
      cout<<"Entered Method Declarations\n";
      for(int i=0;i<vis->method_declaration_list.size();i++)
      {
        vis->method_declaration_list[i]->accept(this);
      }
    }

    int visit(Method_declaration *vis)
    {
      cout<<"Entered Method Declaration\n";
      cout<<"method type "<<vis->method_type<<" method name "<<vis->name<<"\n";
      if(vis->method_args_declarations!=NULL)
      {
        vis->method_args_declarations->accept(this);
      }
      vis->block->accept(this);
    }

    int visit(Method_args_declarations *vis)
    {
      cout<<"Entered Arguments of method\n";
      for(int i=0;i<vis->method_args_declaration_list.size();i++)
      {
        vis->method_args_declaration_list[i]->accept(this);
      }
    }

    int visit(Method_args_declaration *vis)
    {
      cout<<"Argument type "<<vis->arg_type<<" argument name "<<vis->name<<endl;
    }

    int visit(Block *vis)
    {
      cout<<"Enterend Block\n";
      if(vis->field_method_declarations!=NULL)
        vis->field_method_declarations->accept(this);
    }

    int visit(Field_method_declarations *vis)
    {
      cout<<"Entered Field_method_declarations\n";
      for(int i=0;i<vis->declaration_list.size();i++)
        vis->declaration_list[i]->accept(this);
    }

    int visit(Field_method_declaration *vis)
    {
      cout<<"Entered Field_method_declaration\n";
      cout<<"Variable Type "<<vis->dataType<<"\n";
      for(int i=0;i<vis->var_list.size();i++)
      {
        vis->var_list[i]->accept(this);
      }
    }
    // int visit(Var_declarations *vis)
    // {

    // }
    int visit(Var_method_declaration *vis)
    {
      cout<<"Entered Printing Variables\n";
      cout<<vis->name<<"\n";
    }
};