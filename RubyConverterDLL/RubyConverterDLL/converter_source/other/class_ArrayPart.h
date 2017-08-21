#ifndef ARRPART
#define ARRPART

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include "class_Idvar.h"
#include "converter_source/expressions/class_CondExpr.h"
#include <vector>
#include <string>

using std::string;
using std::vector;


class ArrayPart : public Parser
{
private:
	Idvar* ids;
	vector<string> sizes;

public:
	//ctors and dtor
	ArrayPart(GrammarCompiler* gc, Idvar* ids, string& arr_in);
	~ArrayPart() {};

	//methods
	int getArrayType();				//return array type (1d, 2d, 3d)
	string getArrayInit();			//return initialization for array part
	string operator[] (int i);		//return size in "[]"(i)
};


#endif