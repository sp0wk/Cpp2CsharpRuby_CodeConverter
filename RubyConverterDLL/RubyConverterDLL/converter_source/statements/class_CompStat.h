#ifndef COMPSTAT
#define COMPSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Stat.h"

using std::string;


class CompStat : public Statement
{
public:
	CompStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~CompStat() {};
};

#endif