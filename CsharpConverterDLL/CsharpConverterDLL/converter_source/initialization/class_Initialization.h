#ifndef INITIALIZATION
#define INITIALIZATION

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"


class Initialization : public Parser
{
protected:
	Idvar* ids;
	string init_expr;

public:
	Initialization() {};
	Initialization(GrammarCompiler* gc, Idvar* ids) { this->gc = gc; this->ids = ids;}
	virtual ~Initialization() {};

	string getInit() { return this->init_expr; }
	string getCsharpCode() { return this->init_expr; }
};

#endif