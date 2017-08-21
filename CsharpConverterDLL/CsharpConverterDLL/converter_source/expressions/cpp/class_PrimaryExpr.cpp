#include "../class_PrimaryExpr.h"


PrimaryExpr::PrimaryExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	Expr* expr_in_pars = NULL;

	smatch m;
	if (ex_in != "") {
		if (ex_in == "this") {
			this->expr = "this";
		}
		else if (regex_match(ex_in, gc->idvar))	{			//expression is identifier
			if (ids) {
				this->expr = ids->getId(ex_in);					//set expr id from varlist
			}
			else {
				this->expr = ex_in;
			}
		}
		else if (regex_match(ex_in, gc->literal)) {			//expression is literal
			this->expr = ex_in;								//set expr as literal
		}
		else {	// expression is "( expression )"
			if (regex_match(ex_in, m, gc->primary_expr_pars)) {
				expr_in_pars = new Expr(gc, ids, m[1].str());					// parse expression in parentheses
				this->expr = "(" + expr_in_pars->getExpr() + ")";				// return expression in parentheses
				delete expr_in_pars;
			}
		}
	}
}