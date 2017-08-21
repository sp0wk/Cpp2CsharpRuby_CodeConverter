#include "../class_DowhileStat.h"


//constructor
DowhileStat::DowhileStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	string indent = makeIndent(tabs);
	Expr* condition = NULL;
	Stat* st = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->dowhile_stat);
		
		st = new Stat(gc, ids, m[1].str(), tabs+1);
		condition = new Expr(gc, ids, m[2].str());

		this->stat = indent + "do\n" + 
							st->getStat() +
					 indent + "while (" + condition->getExpr() + ");\n";
		delete st;
		delete condition;
	}
}