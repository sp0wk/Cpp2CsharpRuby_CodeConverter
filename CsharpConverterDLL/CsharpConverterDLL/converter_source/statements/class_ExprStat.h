#ifndef EXPRSTAT
#define EXPRSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "converter_source/expressions/class_Expr.h"

using std::string;


class ExprStat : public Statement
{
public:
	ExprStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~ExprStat() {};
};

#endif