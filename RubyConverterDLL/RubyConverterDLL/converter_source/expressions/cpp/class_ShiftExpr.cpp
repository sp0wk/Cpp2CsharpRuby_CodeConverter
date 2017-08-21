#include "../class_ShiftExpr.h"


//constructor
ShiftExpr::ShiftExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	AddExpr* ae = NULL;				//left part
	ShiftExpr* se = NULL;			//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->shift_expr_full)) {
			ae = new AddExpr(gc, ids, m[1].str());								//create parser for left expression
			se = new ShiftExpr(gc, ids, m[3].str());							//create parser for right expression
			expr = ae->getExpr() + " " + m[2].str() + " " + se->getExpr();		//left_expr + operator + right_expr
			delete se;
		}
		else {
			ae = new AddExpr(gc, ids, ex_in);
			expr = ae->getExpr();
		}

		delete ae;
	}
}