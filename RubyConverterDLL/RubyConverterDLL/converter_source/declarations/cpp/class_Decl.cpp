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

	//parse declarator list and set ruby declaration
	this->decl_expr = parseDeclList(m[3].str());
}


//parse single decl_init
string Decl::singleDecl(string& sd_in)
{
	string ptr_ref = "";					//pointer or ref
	string id = "";							//variable name
	string arpart = "";						//array part of initialization
	string init = "";						//ruby init string
	ArrayPart* ap = NULL;					//parser for array part
	Initializer* initializer = NULL;		//parser for initialization
	UnaryExpr* ue = NULL;					//parser for &var

	smatch dm;

	regex_match(sd_in, dm, gc->decl_init_full);
	{
		ptr_ref =	dm[1].str();
		id =		dm[2].str();
		arpart =	dm[3].str();
		init =		dm[4].str();
		
		initializer = new Initializer(gc, ids, init);	//parse init expression

	//set identifier (and add it to id list if needed)

		if (this->d_const != "") {							//if there is qualifier const
			ids->addConst(id);								//add id to const list
			id = ids->upcase(id);							//return upcased id
		}

		if (regex_match(ptr_ref, gc->t_ptr)) {				//if var is pointer
			if (regex_match(initializer->getPreInit(), gc->unary_getaddr)) {	//test for pointer init with "&var"
				ue = new UnaryExpr(gc, ids, initializer->getPreInit());
				ids->addPtr(id, ue->getExpr());
				delete ue;
			}
			else {
				ids->addPtr(id);		//add only pointer to list
			}
		}

		if (regex_match(ptr_ref, gc->t_ref)) {				//if variable is a reference
			ids->addRef(id, initializer->getPreInit());		//add id and var to reference list
		}

	//set initialization
		
		if (init != "") {									//if there is initializer
			if (regex_match(ptr_ref, gc->t_ptr)) {				//if var is a pointer
				if (regex_match(initializer->getPreInit(), gc->unary_getaddr))
					init = "Ptr.new(:" + initializer->getInit() + ", binding)";
				else
					init = initializer->getInit();
			}
			else if (regex_match(ptr_ref, gc->t_ref)) {			//if var is a reference
				init = "Ref.new(:" + initializer->getInit() + ", binding)";
			}
			else {
				if (d_type->getType() == 5) {					//if var is of user type
					init = d_type->getTypeInit() + "(" + initializer->getInit() + ")";
				}
				else {
					init = initializer->getInit();
				}
			}
		}
		else {												//declaration without initialization
			if (arpart != "") {								//if array part exists
				ap = new ArrayPart(gc, ids, arpart);
				init = ap->getArrayInit();
				delete ap;
			}
			else {											//there is no array part
				if (regex_match(ptr_ref, gc->t_ptr)) {		//if pointer
					init = "Ptr.new()";					
				}
				else if (regex_match(ptr_ref, gc->t_ref)) {	//if reference
					init = "Ref.new()";
				}
				else {
					init = this->d_type->getTypeInit();		//get initialization for specific type
				}
			}
		}
	}
	delete initializer;

	return id + " = " + init;
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



