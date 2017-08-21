#ifndef BWIOREXPR
#define BWIOREXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_BwEorExpr.h"

using std::string;


class BwIorExpr : public Expression
{
public:
	BwIorExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~BwIorExpr() {};
};

#endif