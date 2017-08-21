#ifndef PRIMEXPR
#define PRIMEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Expr.h"

using std::string;


class PrimaryExpr : public Expression
{
public:
	PrimaryExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~PrimaryExpr() {};
};

#endif