#include "../class_FuncDef.h"



string FuncDef::singlePar(string& par_in)
{
	string id = "";
	string init = "";
	InitClause* ic = NULL;

	smatch m, m_id;
	regex_match(par_in, m, gc->single_decl);			//parse all expression
	id = m[3].str();
	init = m[4].str();

	//parse parameter id
	regex_match(id, m_id, gc->declarator);
	id = m_id[2].str();

	//parse init
	if (init != "") {
		ic = new InitClause(gc, NULL, init);			//create parser for init clause
		init = " = " + ic->getInit();
		delete ic;
	}

	return id + init;
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
	string f_name = "";
	string f_par = "";
	CompStat* f_body = NULL;;
	this->f_vars = new Idvar(gc);
	
	smatch m;
	//parse func definition
	regex_match(fdef_in, m, gc->func_def);
	f_name = m[1].str();
	f_par = m[2].str();
	

	//check func name for "main"
	if (f_name == "main" || f_name == "Main") {
		f_body = new CompStat(gc, f_vars, m[3].str(), 0);
		this->decl_expr = "\n\n# MAIN\n\n" + f_body->getStat();			//return only statements without indention
	}
	else {
		if (f_par != "")
			f_par = " (" + paramList(f_par) + ")";					//set ruby parameters

		f_body = new CompStat(gc, f_vars, m[3].str(), 1);			//parse function body

		this->decl_expr = "def " + f_name + f_par + "\n" + f_body->getStat() + "end\n\n\n";		//assemble ruby method
	}
}