#ifndef ASSIGNEXPR
#define ASSIGNEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_LogOrExpr.h"
#include "class_CondExpr.h"
#include "converter_source/initialization/class_InitClause.h"

using std::string;


class AssignExpr : public Expression
{
public:
	AssignExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~AssignExpr() {};
};

#endif