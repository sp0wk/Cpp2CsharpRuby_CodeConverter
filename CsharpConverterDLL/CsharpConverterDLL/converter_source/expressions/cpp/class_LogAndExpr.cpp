#include "../class_LogAndExpr.h"


//constructor
LogAndExpr::LogAndExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	BwIorExpr* bwiore = NULL;					//left part
	LogAndExpr* la = NULL;						//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->log_and_expr_full)) {

			bwiore = new BwIorExpr(gc, ids, m[1].str());						//create parser for left expression

			la = new LogAndExpr(gc, ids, m[3].str());							//create parser for right expression

			expr = "Convert.ToBoolean("+ bwiore->getExpr()+") " + m[2].str() + " Convert.ToBoolean("+la->getExpr() +")";		//left_expr + operator + right_expr
			delete la;
		}
		else {
			bwiore = new BwIorExpr(gc, ids, ex_in);
			expr = bwiore->getExpr();				//left_expr
		}

		delete bwiore;
	}
}