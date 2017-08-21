#include "../class_FuncDef.h"



string FuncDef::singlePar(string& par_in)
{
	TType* ptype = NULL;
	string ref = "";						//C# pass by ref
	string vartype = "";					//par type
	string ptr_ref = "";					//par is pointer or ref
	string par_decl = "";					//par declaration
	string id = "";							//parameter name
	string arpart = "";						//array part of par
	string arraytype = "";					//array type (C#)

	smatch m, pm;

	regex_match(par_in, m, gc->declaration);
	ptype = new TType(gc, m[2].str());
	vartype = ptype->getType();
	par_decl = m[3].str();

	//parse parameter
	regex_match(par_decl, pm, gc->decl_init_full);
	{
		ptr_ref =	pm[1].str();
		id =		pm[2].str();
		arpart =	pm[3].str();
		
		//set parameter
		
		if (arpart != "") {								// if par is an array
			arraytype = "[]";
		}
		else if (regex_match(ptr_ref, gc->t_pointer) && (!ptype->isUserType())) {			//if par is a pointer or reference to simple type
			ref = "ref ";
		}
		else {												//simple type
			this->f_vars->addVar(vartype, id);	//add par to var list
		}
	}
	
	delete ptype;

	return ref + vartype + arraytype + " " + id;
}


string FuncDef::paramList(string& pl_in)
{
	string result = "";
	smatch m;

	if (pl_in != "") {
		if (regex_match(pl_in, m, gc->param_list_full)) {			//if more than 1 parameter
			//parse first decl
			result = singlePar(m[1].str());

			//parse second part (if exists)
			result += ", " + paramList(m[2].str());		//recursively called for second part
		}
		else {		//single declarator
			result = singlePar(pl_in);
		}
	}
	 
	return	result;
}


//ctor
FuncDef::FuncDef(GrammarCompiler* gc, string& fdef_in) 
{
	this->gc = gc;
	TType* f_rettype = NULL;
	string f_ret_ptrref = "";
	string f_name = "";
	string f_par = "";	
	CompStat* f_body = NULL;;
	this->f_vars = new Idvar(gc);
	
	smatch m, rt;
	
	//parse func definition
	regex_match(fdef_in, m, gc->func_def);
	string ret_val = m[1].str();
	
	//parse return type
	regex_match(ret_val, rt, gc->ret_val);
	string rt_type = rt[1].str();
	string rt_ptr = rt[2].str();
	
	f_rettype = new TType(gc, rt_type);
	if (regex_match(rt_ptr, gc->t_ptr)) {
		f_ret_ptrref = "[]";
	}


	f_name = m[2].str();
	f_par = "(" + paramList(m[3].str()) + ")";					//set csharp parameters
	f_body = new CompStat(gc, f_vars, m[4].str(), 1);			//parse method body

	//check func name for "main"
	if (f_name == "main" || f_name == "Main") {
		this->decl_expr = "// MAIN\nstatic " + f_rettype->getType() + f_ret_ptrref + " Main" + f_par + "\n" + f_body->getStat() + "\n\n";	
	}
	else {
		this->decl_expr = "public " + f_rettype->getType() + f_ret_ptrref + " " + f_name + f_par + "\n" + f_body->getStat() + "\n\n";		//assemble csharp method
	}

	delete f_body;
	delete f_rettype;
}