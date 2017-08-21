#include "../class_Initializer.h"


//ctor
Initializer::Initializer(GrammarCompiler* gc, Idvar* ids, string& init_in)
{
	InitClause* ic = NULL;
	InitList* il = NULL;
	this->init_expr = "";
	this->pre_init = "";

	smatch m;
	if (init_in != "") {
		if (regex_match(init_in, m, gc->equal_init)) {						// "= init_clause"
			this->pre_init = m[1].str();
			ic = new InitClause(gc, ids, m[1].str());

			init_expr = ic->getInit();
			delete ic;
		}
		else if (regex_match(init_in, m, gc->braced_init_list)) {			// "{...}"
			this->pre_init = m[1].str();
			il = new InitList(gc, ids, m[1].str());

			init_expr = "[ " + il->getInit() + " ]";
			delete il;
		}
		else if (regex_match(init_in, m, gc->init_expr_list)) {				// "( init_list )"
			this->pre_init = m[1].str();
			il = new InitList(gc, ids, m[1].str());

			init_expr = il->getInit();
			delete il;
		}
	}
}