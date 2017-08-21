#ifndef PROGCODE
#define PROGCODE

#include <string>
#include "class_GrammarCompiler.h"
#include "declarations/class_FuncDef.h"

using std::string;


class ProgramCode : public Parser
{
private:
	string ruby_code;

public:
	ProgramCode(GrammarCompiler* gc, string& cppcode_in);
	~ProgramCode() {};

	string getRubyCode() { return ruby_code; };
};

#endif