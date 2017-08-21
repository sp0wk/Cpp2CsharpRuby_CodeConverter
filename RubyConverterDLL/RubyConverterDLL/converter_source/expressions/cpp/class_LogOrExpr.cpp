#include "../class_LogOrExpr.h"


//constructor
LogOrExpr::LogOrExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	LogAndExpr* la = NULL;						//left part
	LogOrExpr* lo = NULL;						//right part

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->log_or_expr_full)) {

			la = new LogAndExpr(gc, ids, m[1].str());						//create parser for left expression

			lo = new LogOrExpr(gc, ids, m[3].str());						//create parser for right expression

			expr = "notfalse("+la->getExpr()+")" + " " + m[2].str() + " " + "notfalse("+lo->getExpr()+")";		//left_expr + operator + right_expr
			delete lo;
		}
		else {
			la = new LogAndExpr(gc, ids, ex_in);
			expr = la->getExpr();				//left_expr
		}

		delete la;
	}
}