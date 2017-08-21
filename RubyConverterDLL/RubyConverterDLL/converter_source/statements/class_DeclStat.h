#ifndef DECLSTAT
#define DECLSTAT

#include <string>
#include "class_Statement.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "converter_source/declarations/class_Decl.h"


using std::string;


class DeclStat : public Statement
{
public:
	DeclStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs);
	~DeclStat() {};
};

#endif