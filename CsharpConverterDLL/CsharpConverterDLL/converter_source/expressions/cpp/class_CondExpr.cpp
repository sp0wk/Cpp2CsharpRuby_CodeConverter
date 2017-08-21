#include "../class_CondExpr.h"


//constructor
CondExpr::CondExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	LogOrExpr* lo = NULL;						//left part
	Expr* exp = NULL;							//right part 1
	AssignExpr* ase = NULL;						//right part 2

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->cond_expr_full)) {

			lo = new LogOrExpr(gc, ids, m[1].str());					//create parser for left expression
			exp = new Expr(gc, ids, m[2].str());						//create parser for true expression (1)
			ase = new AssignExpr(gc, ids, m[3].str());					//create parser for false expression (2)

			expr = lo->getExpr() + " ? " + exp->getExpr() + " : " + ase->getExpr();				//left_expr ? right_expr_1 : right_expr_2
			delete exp;
			delete ase;
		}
		else {
			lo = new LogOrExpr(gc, ids, ex_in);
			expr = lo->getExpr();				// only left_expr
		}

		delete lo;
	}
}