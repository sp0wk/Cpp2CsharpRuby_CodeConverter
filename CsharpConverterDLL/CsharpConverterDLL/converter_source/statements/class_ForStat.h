#ifndef FORSTAT
#define FORSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Stat.h"
#include "converter_source/declarations/class_Decl.h"
#include "converter_source/expressions/class_Expr.h"

using std::string;


class ForStat : public Statement
{
public:
	ForStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~ForStat() {};

	string parseForInit(string& init_in);
	string parseCondition(string& cond_in);
};

#endif