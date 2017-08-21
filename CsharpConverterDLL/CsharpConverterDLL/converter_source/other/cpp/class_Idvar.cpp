#include "../class_Idvar.h"


Idvar::Idvar(GrammarCompiler* gc)
{
	this->gc = gc;
}


void Idvar::addVar(string& type_in, string var_in) 
{
	pair<string, string> newvar(type_in, var_in);
	this->vars.push_front(newvar);
}


string Idvar::getVarType(string& var_in)
{
	// search for id
	list<pair<string, string>>::iterator iter = std::find_if (vars.begin(), vars.end(), [var_in] (pair<string, string> const &m) { return m.second == var_in; });

	if (iter != vars.end())	
		return (*iter).first;
	else {
		return "";
	}
}


string Idvar::getId(string& id_in)
{
	if (id_in == "NULL")
		return "null";
	else if (id_in == "endl" || id_in == "std::endl")
		return "\"\\n\"";
	else
		return id_in;				// return original id
}