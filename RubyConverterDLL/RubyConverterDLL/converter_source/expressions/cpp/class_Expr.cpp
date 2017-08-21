#include "../class_Expr.h"


Expr::Expr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";
	
	AssignExpr* ae;		//first expr
	Expr* ex2;			//second expr

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->expression_full)) {		//if expreesion, expression, ...
			ae = new AssignExpr(gc, ids, m[1].str());			// parser for first expression
			ex2 = new Expr(gc, ids, m[2].str());				// parser for second part

			expr = ae->getExpr() + ", " + ex2->getExpr();
			delete ex2;
		}
		else {	//just assignment expression
			ae = new AssignExpr(gc, ids, ex_in);
			expr = ae->getExpr();
		}

		delete ae;
	}
}