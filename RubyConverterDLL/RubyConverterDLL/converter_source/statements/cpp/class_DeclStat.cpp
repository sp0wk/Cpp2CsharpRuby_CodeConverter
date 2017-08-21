#include "../class_DeclStat.h"


//constructor
DeclStat::DeclStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	Decl* decl = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->decl_stat);

		if (m[1].str() != "") {
			decl = new Decl(gc, ids, m[1].str());

			stat = makeIndent(tabs) + decl->getDecl() + "\n";
			delete decl;
		}
	}
}