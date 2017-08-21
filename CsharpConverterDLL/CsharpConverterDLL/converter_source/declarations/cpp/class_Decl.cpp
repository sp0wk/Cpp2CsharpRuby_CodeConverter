#include "../class_Decl.h"


//ctor
Decl::Decl(GrammarCompiler* gc, Idvar* ids, string& decl_in)
{
	this->gc = gc;
	this->ids = ids;
	
	smatch m;
	//parse declaration
	regex_match(decl_in, m, gc->declaration);

	//set class members
	this->d_const = m[1].str();
	this->d_type = new TType(gc, m[2].str());

	//parse declarator list and set csharp declaration
	this->decl_expr = parseDeclList(m[3].str());
}


//parse single decl_init
string Decl::singleDecl(string& sd_in)
{
	string cv = "";							//const qualifier
	string vartype = d_type->getType();		//variable type
	string ptr_ref = "";					//pointer or ref
	string id = "";							//variable name
	string arpart = "";						//array part of initialization
	string arraytype = "";					//array type (C#)
	string init = "";						//csharp init string
	ArrayPart* ap = NULL;					//parser for array part
	Initializer* initializer = NULL;		//parser for initialization
	string initexpr = "";					//initializer expression

	smatch dm;
	//set const qualifier
	if (d_const != "") cv = "const ";

	//parse declaration
	regex_match(sd_in, dm, gc->decl_init_full);
	{
		ptr_ref =	dm[1].str();
		id =		dm[2].str();
		arpart =	dm[3].str();
		init =		dm[4].str();
		
		initializer = new Initializer(gc, ids, init);	//parse init expression
		initexpr = initializer->getInit();
		
		//set initialization
		
		if (init != "") {									//if there is initializer
			if (regex_match(ptr_ref, gc->t_ptr) && arpart != "") {	// if var is an array of pointers
				ap = new ArrayPart(gc, ids, arpart);

				arraytype = ap->getCsharpArrayType();
				init = " = " + initexpr + "	/* ARRAY OF POINTERS */";

				delete ap;
			}
			else if (arpart != "") {						// if var is an array
				ap = new ArrayPart(gc, ids, arpart);

				arraytype = ap->getCsharpArrayType();
				init = " = " + initexpr;

				delete ap;
			}
			else if (regex_match(ptr_ref, gc->t_ptr)) {				//if var is a pointer
				if (ptr_ref == "*" && regex_match(initializer->getPreInit(), gc->new_array)) {		//pointer to array
					arraytype = "[]";
					init = " = " + initexpr + "	/* POINTER TO ARRAY */";
				}
				else {
					init = " = " + initexpr + "	/* UNSAFE POINTER */";		// pointer to simple type
				}
			}
			else if (regex_match(ptr_ref, gc->t_ref)) {			//if var is a reference
				init = " = " + initexpr + "	/* REFERENCE TO VALUE */";
			}
			else if (d_type->isUserType()) {					//if var is of user type
				init = " = new " + vartype + "(" + initexpr + ")";
			}
			else {												//simple type
				if (ids) ids->addVar(vartype, id);		//add var to var list
				init = initexpr;
			}
		}
		else {						//declaration without initialization
			if (regex_match(ptr_ref, gc->t_ptr) && arpart != "") {	// if var is an array of pointers
				ap = new ArrayPart(gc, ids, arpart);

				arraytype = ap->getCsharpArrayType();
				init = "/* ARRAY OF POINTERS */";

				delete ap;
			}
			else if (arpart != "") {							// if var is an array
				ap = new ArrayPart(gc, ids, arpart);
				arraytype = ap->getCsharpArrayType();
				init = " = new " + vartype + ap->getArrayPart();
				delete ap;
			}
			else if (regex_match(ptr_ref, gc->t_ptr)) {			//if var is a pointer
				init = "/* UNSAFE POINTER */";
			}
			else if (regex_match(ptr_ref, gc->t_ref)) {			//if var is a reference
				init = "/* REFERENCE TO VALUE */";
			}
			else if (d_type->isUserType()) {					//if var is of user type
				init = " = new " + vartype + "()";
			}
			else {												//simple type
				if (ids) ids->addVar(vartype, id); //add var to var list
				init = "";
			}
		}

		delete initializer;
	}
	

	return cv + vartype + arraytype + " " + id + init;
}



//parse declarator list
string Decl::parseDeclList(string& d_in)
{
	string result = "";
	smatch m;

	if (d_in != "") {
		if (regex_match(d_in, m, gc->decl_list_full)) {			//if more than 1 declarator

			//parse first decl
			result = singleDecl(m[1].str());

			//parse second part (if exists)
			result += "; " + parseDeclList(m[2].str());		//recursively called for second part
		}
		else {		//single declarator
			result = singleDecl(d_in);
		}
	}
	 
	return	result;
}



