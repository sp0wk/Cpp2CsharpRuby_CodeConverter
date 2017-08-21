#include "../class_MultipExpr.h"


//constructor
MultipExpr::MultipExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	UnaryExpr* ue = NULL;		//left part
	MultipExpr* me = NULL;		//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->multipl_expr_full)) {

			ue = new UnaryExpr(gc, ids, m[1].str());					//create parser for left expression

			me = new MultipExpr(gc, ids, m[3].str());					//create parser for right expression

			expr = ue->getExpr() + " " + m[2].str() + " " + me->getExpr();			//left_expr + m_operator + right_expr
			delete me;
		}
		else {
			ue = new UnaryExpr(gc, ids, ex_in);
			expr = ue->getExpr();			//left_expr
		}

		delete ue;
	}
}