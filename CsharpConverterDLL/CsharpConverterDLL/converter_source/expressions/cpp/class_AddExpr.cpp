#include "../class_AddExpr.h"


//constructor
AddExpr::AddExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	MultipExpr* me = NULL;		//left part
	AddExpr* ae = NULL;			//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->add_expr_full)) {

			me = new MultipExpr(gc, ids, m[1].str());					//create parser for left expression

			ae = new AddExpr(gc, ids, m[3].str());						//create parser for right expression

			expr = me->getExpr() + " " + m[2].str() + " " + ae->getExpr();			//left_expr + a_operator + right_expr
			delete ae;
		}
		else {
			me = new MultipExpr(gc, ids, ex_in);
			expr = me->getExpr();			//left_expr
		}

		delete me;
	}
}