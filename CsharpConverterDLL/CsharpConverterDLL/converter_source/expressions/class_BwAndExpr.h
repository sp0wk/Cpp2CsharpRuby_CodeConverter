#ifndef BWANDEXPR
#define BWANDEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_EquExpr.h"

using std::string;


class BwAndExpr : public Expression
{
public:
	BwAndExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~BwAndExpr() {};
};

#endif