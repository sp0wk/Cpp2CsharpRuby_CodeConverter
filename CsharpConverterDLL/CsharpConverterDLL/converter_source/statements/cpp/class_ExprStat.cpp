#include "../class_ExprStat.h"


//constructor
ExprStat::ExprStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	Expr* exp = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->expr_stat);

		if (m[1].str() != "") {
			exp = new Expr(gc, ids, m[1].str());

			stat = makeIndent(tabs) + exp->getExpr() + ";\n";
			delete exp;
		}
	}
}