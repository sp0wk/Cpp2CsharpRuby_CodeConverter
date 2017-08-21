#include "../class_BwIorExpr.h"


//constructor
BwIorExpr::BwIorExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	BwEorExpr* bweore = NULL;					//left part
	BwIorExpr* bwiore = NULL;					//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->bw_ior_expr_full)) {

			bweore = new BwEorExpr(gc, ids, m[1].str());								//create parser for left expression

			bwiore = new BwIorExpr(gc, ids, m[3].str());								//create parser for right expression

			expr = bweore->getExpr() + " " + m[2].str() + " " + bwiore->getExpr();		//left_expr + operator + right_expr
			delete bwiore;
		}
		else {
			bweore = new BwEorExpr(gc, ids, ex_in);
			expr = bweore->getExpr();				//only left_expr
		}

		delete bweore;
	}
}