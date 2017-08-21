#ifndef CONIOSTAT
#define CONIOSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "converter_source/expressions/class_AddExpr.h"

using std::string;


class ConsoleIOStat : public Statement
{
public:
	ConsoleIOStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~ConsoleIOStat() {};

	//methods
	string parseCIN(string& cins);
	string parseCOUT(string& couts);
};

#endif