#ifndef EXPR
#define EXPR

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Expression.h"
#include "class_AssignExpr.h"


class Expr : public Expression
{
public:
	Expr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~Expr() {};	
};

#endif