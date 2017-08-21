#ifndef CONDEXPR
#define CONDEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_LogOrExpr.h"
#include "class_Expr.h"
#include "class_AssignExpr.h"

using std::string;


class CondExpr : public Expression
{
public:
	CondExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~CondExpr() {};
};

#endif