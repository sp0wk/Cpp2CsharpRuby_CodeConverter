#ifndef INITLIST
#define INITLIST

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Initialization.h"
#include "class_InitClause.h"


class InitList : public Initialization
{
public:
	InitList(GrammarCompiler* gc, Idvar* ids, string& init_in);
	~InitList() {};	
};

#endif