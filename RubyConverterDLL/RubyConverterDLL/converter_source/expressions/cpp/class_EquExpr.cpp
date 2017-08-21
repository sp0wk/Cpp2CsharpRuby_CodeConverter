#include "../class_EquExpr.h"


//constructor
EquExpr::EquExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	RelatExpr* re = NULL;				//left part
	EquExpr* ee = NULL;					//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->equ_expr_full)) {

			re = new RelatExpr(gc, ids, m[1].str());							//create parser for left expression

			ee = new EquExpr(gc, ids, m[3].str());								//create parser for right expression

			expr = re->getExpr() + " " + m[2].str() + " " + ee->getExpr();		//left_expr + operator + right_expr
			delete ee;
		}
		else {
			re = new RelatExpr(gc, ids, ex_in);
			expr = re->getExpr();				//only left_expr
		}

		delete re;
	}
}