#ifndef SHIFTEXPR
#define SHIFTEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_AddExpr.h"

using std::string;


class ShiftExpr : public Expression
{
public:
	ShiftExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~ShiftExpr() {};
};

#endif