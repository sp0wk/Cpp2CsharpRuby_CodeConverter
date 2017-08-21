#include "../class_RelatExpr.h"


//constructor
RelatExpr::RelatExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	ShiftExpr* se = NULL;				//left part
	RelatExpr* re = NULL;				//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->relat_expr_full)) {

			se = new ShiftExpr(gc, ids, m[1].str());						//create parser for left expression

			re = new RelatExpr(gc, ids, m[3].str());						//create parser for right expression

			expr = se->getExpr() + " " + m[2].str() + " " + re->getExpr();				//left_expr + operator + right_expr
			delete re;
		}
		else {
			se = new ShiftExpr(gc, ids, ex_in);
			expr = se->getExpr();				//left_expr
		}

		delete se;
	}
}