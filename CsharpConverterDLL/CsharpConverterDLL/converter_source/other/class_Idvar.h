#ifndef IDVAR
#define IDVAR

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include <list>
#include <string>


using std::string;
using std::list;
using std::pair;


class Idvar : public Parser
{
private:
	list<pair<string, string>> vars;

public:
	//ctors and dtor
	Idvar(GrammarCompiler* gc);
	~Idvar() {};

	//methods
	void addVar(string& type_in, string var_in);		//add var to list
	string getVarType(string& var_in);					//return data type of a variable
	string getId(string& id_in);						//return id
};

#endif