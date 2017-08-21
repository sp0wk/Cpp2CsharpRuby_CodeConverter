#ifndef JUMPSTAT
#define JUMPSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "converter_source/expressions/class_Expr.h"


using std::string;


class JumpStat : public Statement
{
public:
	JumpStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~JumpStat() {};
};

#endif