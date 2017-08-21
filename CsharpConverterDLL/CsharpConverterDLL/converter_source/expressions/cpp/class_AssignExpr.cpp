#include "../class_AssignExpr.h"


//constructor
AssignExpr::AssignExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	string lvalue = "";
	string rvalue = "";
	LogOrExpr* lo = NULL;				//lvalue
	InitClause* ic = NULL;				//rvalue
	CondExpr* ce = NULL;				//not assignment

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->assign_expr_full)) {			// lvalue assign_operator rvalue

			lvalue = m[1].str();
			rvalue = m[3].str();
			lo = new LogOrExpr(gc, ids, lvalue);
			ic = new InitClause(gc, ids, rvalue);

			expr = lo->getExpr() + " " + m[2].str() + " " + ic->getInit();
			
			delete lo;
			delete ic;
		}
		else {		// conditional expression
			ce = new CondExpr(gc, ids, ex_in);

			expr = ce->getExpr();
			delete ce;
		}
	}
}