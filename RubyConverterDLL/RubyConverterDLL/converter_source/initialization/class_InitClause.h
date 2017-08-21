#ifndef INITCLAUSE
#define INITCLAUSE

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Initialization.h"
#include "converter_source/expressions/class_AssignExpr.h"
#include "class_InitList.h"


class InitClause : public Initialization
{
public:
	InitClause(GrammarCompiler* gc, Idvar* ids, string& init_in);
	~InitClause() {};	
};

#endif