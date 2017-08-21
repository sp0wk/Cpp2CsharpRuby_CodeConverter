#ifndef RELATEXPR
#define RELATEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_ShiftExpr.h"

using std::string;


class RelatExpr : public Expression
{
public:
	RelatExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~RelatExpr() {};
};

#endif