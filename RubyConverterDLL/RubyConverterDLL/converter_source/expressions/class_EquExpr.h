#ifndef EQUEXPR
#define EQUEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_RelatExpr.h"

using std::string;


class EquExpr : public Expression
{
public:
	EquExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~EquExpr() {};
};

#endif