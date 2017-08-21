#ifndef DOWHILESTAT
#define DOWHILESTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Stat.h"
#include "converter_source/expressions/class_Expr.h"

using std::string;


class DowhileStat : public Statement
{
public:
	DowhileStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~DowhileStat() {};
};

#endif