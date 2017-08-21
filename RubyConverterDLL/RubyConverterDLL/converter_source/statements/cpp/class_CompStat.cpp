#include "../class_CompStat.h"


//constructor
CompStat::CompStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	string indent = makeIndent(tabs);
	string statements = "";
	Stat* st = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->comp_stat);
		statements = m[1].str();

		//parse statements between braces
		sregex_iterator end;
		for (sregex_iterator iter(cbegin(statements), cend(statements), gc->stat_space); iter != end; iter++) {
			st = new Stat(gc, ids, (*iter)[1].str(), tabs);

			stat += st->getStat();

			delete st;
			st = NULL;
		}
	}
}