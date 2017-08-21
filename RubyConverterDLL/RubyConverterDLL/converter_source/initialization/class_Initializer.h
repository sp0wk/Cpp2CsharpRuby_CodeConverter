#ifndef INITIALIZER
#define INITIALIZER

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Initialization.h"
#include "class_InitClause.h"
#include "class_InitList.h"


class Initializer : public Initialization
{
private:
	string pre_init;

public:
	Initializer(GrammarCompiler* gc, Idvar* ids, string& init_in);
	~Initializer() {};	

	string getPreInit() { return pre_init; };
};

#endif