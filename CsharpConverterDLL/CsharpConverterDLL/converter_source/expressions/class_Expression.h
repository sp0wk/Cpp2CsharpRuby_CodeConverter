#ifndef EXPRESSION
#define EXPRESSION

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"


class Expression : public Parser
{
protected:
	Idvar* ids;
	string expr;

public:
	Expression() {};
	Expression(GrammarCompiler* gc, Idvar* ids) { this->gc = gc; this->ids = ids;}
	virtual ~Expression() {};

	string getExpr() { return this->expr; }
	string getCsharpCode() { return this->expr; }
};

#endif