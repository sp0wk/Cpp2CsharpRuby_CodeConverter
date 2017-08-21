#ifndef LOGANDEXPR
#define LOGANDEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_BwIorExpr.h"

using std::string;


class LogAndExpr : public Expression
{
public:
	LogAndExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~LogAndExpr() {};
};

#endif