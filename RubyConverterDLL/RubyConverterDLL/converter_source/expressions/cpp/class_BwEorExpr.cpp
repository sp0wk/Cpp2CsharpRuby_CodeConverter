#include "../class_BwEorExpr.h"


//constructor
BwEorExpr::BwEorExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	BwAndExpr* bwae = NULL;						//left part
	BwEorExpr* bweore = NULL;					//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->bw_eor_expr_full)) {

			bwae = new BwAndExpr(gc, ids, m[1].str());									//create parser for left expression

			bweore = new BwEorExpr(gc, ids, m[3].str());								//create parser for right expression

			expr = bwae->getExpr() + " " + m[2].str() + " " + bweore->getExpr();		//left_expr + operator + right_expr
			delete bweore;

		}
		else {
			bwae = new BwAndExpr(gc, ids, ex_in);
			expr = bwae->getExpr();					//only left_expr
		}

		delete bwae;
	}
}