#include "../class_BwAndExpr.h"


//constructor
BwAndExpr::BwAndExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	EquExpr* ee = NULL;						//left part
	BwAndExpr* bwae = NULL;					//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->bw_and_expr_full)) {

			ee = new EquExpr(gc, ids, m[1].str());									//create parser for left expression

			bwae = new BwAndExpr(gc, ids, m[3].str());								//create parser for right expression

			expr = ee->getExpr() + " " + m[2].str() + " " + bwae->getExpr();		//left_expr + operator + right_expr
			delete bwae;
		}
		else {
			ee = new EquExpr(gc, ids, ex_in);
			expr = ee->getExpr();				//only left_expr
		}

		delete ee;
	}
}