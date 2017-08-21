#include "../class_LblStat.h"


//constructor
LblStat::LblStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	CondExpr* ce = NULL;
	Stat* st = NULL;

	if (stat_in != "") {
		if (regex_match(stat_in, m, gc->lbl_case)) {		//if "case" statement
			ce = new CondExpr(gc, ids, m[1].str());
			st = new Stat(gc, ids, m[2].str(), tabs + 1);

			stat = makeIndent(tabs) + "case " + ce->getExpr() + ": " + st->getStat();
			delete ce;
		}
		else {												//if "default" statement
			regex_match(stat_in, m, gc->lbl_def);
			st = new Stat(gc, ids, m[1].str(), tabs + 1);

			stat = makeIndent(tabs) + "default: " + st->getStat();
		}
		delete st;
	}
}