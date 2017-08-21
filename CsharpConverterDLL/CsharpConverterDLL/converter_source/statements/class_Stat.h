#ifndef STAT
#define STAT

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Statement.h"
#include "class_CompStat.h"
#include "class_DeclStat.h"
#include "class_DowhileStat.h"
#include "class_ExprStat.h"
#include "class_ForStat.h"
#include "class_IfStat.h"
#include "class_JumpStat.h"
#include "class_LblStat.h"
#include "class_SwitchStat.h"
#include "class_WhileStat.h"
#include "class_ConsoleIOStat.h"


class Stat : public Statement
{
public:
	Stat(GrammarCompiler* gc, Idvar* ids, string& ex_in, int tabs = 0);
	~Stat() {};	
};

#endif