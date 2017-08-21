#ifndef PARSER
#define PARSER

#include "class_GrammarCompiler.h"
#include <string>

using std::string;


class Parser
{
protected:
	GrammarCompiler* gc;

public:
	Parser() {};
	Parser(GrammarCompiler* gc) : gc(gc) {};
	virtual ~Parser() {};

	virtual string getRubyCode() { return ""; }
};

#endif