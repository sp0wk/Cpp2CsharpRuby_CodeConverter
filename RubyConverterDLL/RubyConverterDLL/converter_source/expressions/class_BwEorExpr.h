#ifndef BWEOREXPR
#define BWEOREXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_BwAndExpr.h"

using std::string;


class BwEorExpr : public Expression
{
public:
	BwEorExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~BwEorExpr() {};
};

#endif