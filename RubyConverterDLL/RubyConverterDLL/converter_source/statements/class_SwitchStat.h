#ifndef SWITCHSTAT
#define SWITCHSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Stat.h"
#include "converter_source/declarations/class_Decl.h"
#include "converter_source/expressions/class_Expr.h"

using std::string;


class SwitchStat : public Statement
{
public:
	SwitchStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~SwitchStat() {};

	string parseSwitchCondition(string& cond_in);
};

#endif