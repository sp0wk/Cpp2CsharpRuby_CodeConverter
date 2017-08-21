#ifndef DECLARATION
#define DECLARATION

#include "converter_source/class_Parser.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"


class Declaration : public Parser
{
protected:
	Idvar* ids;
	string decl_expr;

public:
	Declaration() {};
	Declaration(GrammarCompiler* gc, Idvar* ids) { this->gc = gc; this->ids = ids;}
	virtual ~Declaration() {};

	string getDecl() { return this->decl_expr; }
	string getCsharpCode() { return this->decl_expr; }
};

#endif