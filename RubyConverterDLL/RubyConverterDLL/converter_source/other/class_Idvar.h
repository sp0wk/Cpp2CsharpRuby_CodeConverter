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
	list< pair<string, string> > pointers;
	list< pair<string, string> > references;
	list<string> constants;	

public:
	//ctors and dtor
	Idvar(GrammarCompiler* gc);
	~Idvar() {};

	//methods
	void addPtr(string& ptr_in, string var_in = "");	//add new pointer to list
	void addRef(string& ref_in, string& var_in);		//add new ref to list
	void addConst(string& c_in);						//add new constant to list
	string* getPtr(string& ptr_in);						//return pair for found pointer
	string getPairId(string& var_in);					//return pointer or ref name for found variable
	string upcase(string c_in);							//return upcased string
	string getId(string& id_in);						//return changed id
};

#endif