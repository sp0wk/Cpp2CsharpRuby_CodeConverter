#ifndef PROGCODE
#define PROGCODE

#include <string>
#include "class_GrammarCompiler.h"
#include "declarations/class_FuncDef.h"

using std::string;


class ProgramCode : public Parser
{
private:
	string csharp_code;

public:
	ProgramCode(GrammarCompiler* gc, string& cppcode_in);
	~ProgramCode() {};

	string getCsharpCode() { return csharp_code; };
};

#endif