#include "../class_InitClause.h"



//ctor
InitClause::InitClause(GrammarCompiler* gc, Idvar* ids, string& init_in)
{
	InitList* il = NULL;
	AssignExpr* ae = NULL;
	this->init_expr = "";

	smatch m;
	if (init_in != "") {
		if (regex_match(init_in, m, gc->braced_init_list)) {		// braced init list   -   {...}
			il = new InitList(gc, ids, m[1].str());
			init_expr = "{" + il->getInit() + "}";
			delete il;
		}
		else {														// assign expression
			ae = new AssignExpr(gc, ids, init_in);
			init_expr = ae->getExpr();
			delete ae;
		}
	}
}