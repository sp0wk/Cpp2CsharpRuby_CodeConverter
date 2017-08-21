#ifndef MULTIPEXPR
#define MULTIPEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_UnaryExpr.h"

using std::string;


class MultipExpr : public Expression
{
public:
	MultipExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~MultipExpr() {};
};

#endif