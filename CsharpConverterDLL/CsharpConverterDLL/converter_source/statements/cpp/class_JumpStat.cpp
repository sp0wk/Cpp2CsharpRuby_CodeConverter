#include "../class_JumpStat.h"



//constructor
JumpStat::JumpStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	string indent = makeIndent(tabs);
	Expr* expr = NULL;

	if (stat_in != "") {
		if (regex_match(stat_in, m, gc->jump_return)) {			//return
			if (m[1].str() != "") {
				expr = new Expr(gc, ids, m[1].str());
				stat = indent + "return " + expr->getExpr() + ";\n";
				delete expr;
			}
			else {
				stat = indent + "return;\n";
			}
		}
		else if (regex_match(stat_in, gc->jump_continue)) {		//continue
			stat = indent + "continue;\n";
		}
		else if (regex_match(stat_in, gc->jump_break)) {		//break
			stat = indent + "break;\n";
		}
	}
}