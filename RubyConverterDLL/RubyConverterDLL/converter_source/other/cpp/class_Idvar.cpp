#include "../class_Idvar.h"


Idvar::Idvar(GrammarCompiler* gc)
{
	this->gc = gc;
}


string Idvar::upcase(string c_in)
{// return upcased string

	for (int i = 0; c_in[i] != '\0'; i++)
		c_in[i] = toupper(c_in[i]);

	return c_in;
}


void Idvar::addPtr(string& ptr_in, string var_in) 
{
	pair<string, string> newpair(ptr_in, var_in);
	this->pointers.push_front(newpair);
}


void Idvar::addRef(string& ref_in, string& var_in)
{
	pair<string, string> newpair(ref_in, var_in);
	this->references.push_front(newpair);
}


void Idvar::addConst(string& c_in)
{
	this->constants.push_front(c_in);
}


string* Idvar::getPtr(string& ptr_in)
{
	list< pair<string, string> >::iterator iter = std::find_if(pointers.begin(), pointers.end(), [ptr_in] (pair<string, string> const &m) { return m.first == ptr_in; });
	if (iter != pointers.end())
		return &(*iter).second;
	else
		return NULL;
}


string Idvar::getPairId(string& var_in)
{
	// search for id
	list< pair<string, string> >::iterator iter = std::find_if (references.begin(), references.end(), [var_in] (pair<string, string> const &m) { return m.second == var_in; });

	if (iter != references.end())		// id found in references
		return (*iter).first;
	else {
		iter = std::find_if (pointers.begin(), pointers.end(), [var_in] (pair<string, string> const &m) { return m.second == var_in; });

		if (iter != pointers.end())		// id found in pointers
			return (*iter).first;
		else							// id not found	
			return "";
	}
}


string Idvar::getId(string& id_in)
{
	// search for id
	list< pair<string, string> >::iterator iter = std::find_if (references.begin(), references.end(), [id_in] (pair<string, string> const &m) { return m.first == id_in; });
	list<string>::iterator c_iter;

	if (iter != references.end())		// id found in references
		return (*iter).first + ".val";
	else {
		c_iter = std::find(constants.begin(), constants.end(), id_in);
		if (c_iter != constants.end()) {	// id found in constants
			smatch m;
			regex_search(*c_iter, m, gc->idvar);			// split namescope and const name
			return m[1].str() + upcase(m[2].str());
		}
		else 
			if (id_in == "NULL")
				return "nil";
			else if (id_in == "endl" || id_in == "std::endl")
				return "\"\\n\"";
			else
				return id_in;				// return original id
	}

}