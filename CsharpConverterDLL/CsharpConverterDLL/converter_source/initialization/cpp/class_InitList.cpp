#include "../class_InitList.h"


InitList::InitList(GrammarCompiler* gc, Idvar* ids, string& init_in)
{
	this->gc = gc;
	this->ids = ids;
	this->init_expr = "";
	
	InitClause* ic;			//first expr
	InitList* il2;			//second expr

	smatch m;
	if (init_in != "") {
		if (regex_match(init_in, m, gc->init_list_full)) {			//if init_clause, init_clause, ...
			ic = new InitClause(gc, ids, m[1].str());				// parser for first init_clause
			il2 = new InitList(gc, ids, m[2].str());				// parser for second part

			init_expr = ic->getInit() + ", " + il2->getInit();
			delete il2;
		}
		else {	//just init_clause
			ic = new InitClause(gc, ids, init_in);
			init_expr = ic->getInit();
		}

		delete ic;
	}
}