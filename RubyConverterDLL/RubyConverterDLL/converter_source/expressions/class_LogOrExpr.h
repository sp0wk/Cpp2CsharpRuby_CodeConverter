#ifndef LOGOREXPR
#define LOGOREXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_LogAndExpr.h"

using std::string;


class LogOrExpr : public Expression
{
public:
	LogOrExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~LogOrExpr() {};
};

#endif