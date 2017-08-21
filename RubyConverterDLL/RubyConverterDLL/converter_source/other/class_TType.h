#ifndef TTYPE
#define TTYPE

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include <string>

using std::string;


class TType : public Parser
{
private:	
	int type;			// 0 - void, 1 - int, 2 - float, 3 - bool, 4 - chars, 5 - usertype
	string usertype;	//user type name

public:
	//ctors and dtor
	TType();
	TType(GrammarCompiler* gc, string& type_in);
	~TType() {};

	//methods
	int getType();				//return type
	string getTypeInit();		//return ruby init for specific type
};

#endif