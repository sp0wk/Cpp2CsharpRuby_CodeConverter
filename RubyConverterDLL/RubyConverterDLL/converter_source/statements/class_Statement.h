#ifndef STATEMENT
#define STATEMENT

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"


class Statement : public Parser
{
protected:
	Idvar* ids;
	string stat;
	int tabs;

	string makeIndent(int tabs) {
		string indent = "";
		for (int i = 0; i < tabs; i++)
			indent += "\t";

		return indent;
	}

public:
	Statement() {};
	Statement(GrammarCompiler* gc, Idvar* ids, int tabs = 0) { this->gc = gc; this->ids = ids; this->tabs = tabs; }
	virtual ~Statement() {};

	string getStat() { return this->stat; }
	string getRubyCode() { return this->stat; }
};

#endif