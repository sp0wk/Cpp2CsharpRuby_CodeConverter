#include "../class_WhileStat.h"


// parse condition
string WhileStat::parseCondition(string& cond_in)
{
	string result = "";
	Expr* expr = NULL;
	Decl* decl = NULL;

	if (regex_match(cond_in, gc->expression)) {		//if condition is expression
		expr = new Expr(gc, ids, cond_in);
		result = expr->getExpr();
		delete expr;
	}
	else {		// condition is simple declaration
		decl = new Decl(gc, ids, cond_in);
		result = decl->getDecl();
		delete decl;
	}
	return "notfalse(" + result + ")";
}


//constructor
WhileStat::WhileStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	string indent = makeIndent(tabs);
	string condition = "";
	Stat* st = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->while_stat);
		
		condition = parseCondition(m[1].str());
		st = new Stat(gc, ids, m[2].str(), tabs+1);

		this->stat = indent + "while " + condition + "\n" + 
									st->getStat() + 
								indent + "end\n";
		delete st;
	}
}