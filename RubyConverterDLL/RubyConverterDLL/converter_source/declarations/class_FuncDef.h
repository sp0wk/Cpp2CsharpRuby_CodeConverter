#ifndef FUNCDEF
#define FUNCDEF

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Declaration.h"
#include "converter_source/initialization/class_InitClause.h"
#include "converter_source/statements/class_CompStat.h"



class FuncDef : public Declaration
{
private:
	string f_name;
	string f_par;
	CompStat* f_body;
	Idvar* f_vars;

public:
	FuncDef(GrammarCompiler* gc, string& fdef_in);
	~FuncDef() { delete f_body; };	

	string singlePar(string& par_in);		//parse single parameter
	string paramList(string& pl_in);		//parse parameter list
};

#endif