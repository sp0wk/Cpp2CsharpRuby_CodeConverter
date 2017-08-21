#ifndef TTYPE
#define TTYPE

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include <string>

using std::string;


class TType : public Parser
{
private:	
	string type;		//C# type
	bool usertype;

public:
	//ctors and dtor
	TType();
	TType(GrammarCompiler* gc, string& type_in);
	~TType() {};

	//methods
	string getType() { return this->type; }
	bool isUserType() { return usertype; }
};

#endif