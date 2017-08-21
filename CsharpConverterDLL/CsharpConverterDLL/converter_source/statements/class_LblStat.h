#ifndef LBLSTAT
#define LBLSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "converter_source/expressions/class_CondExpr.h"
#include "class_Stat.h"

using std::string;


class LblStat : public Statement
{
public:
	LblStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~LblStat() {};
};

#endif