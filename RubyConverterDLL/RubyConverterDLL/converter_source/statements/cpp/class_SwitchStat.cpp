#include "../class_SwitchStat.h"


// parse condition
string SwitchStat::parseSwitchCondition(string& cond_in)
{
	string result = "";
	Expr* expr = NULL;
	Decl* decl = NULL;

	if (regex_match(cond_in, gc->expression)) {		//if condition is expression
		expr = new Expr(gc, ids, cond_in);

		if (expr->getExpr() == "0" || expr->getExpr() == "\"\"")		//check for ruby "false" value
			result = "false";
		else
			result = expr->getExpr();

		delete expr;
	}
	else {		// condition is simple declaration
		decl = new Decl(gc, ids, cond_in);
		result = decl->getDecl();
		delete decl;
	}
	return result;
}


//constructor
SwitchStat::SwitchStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
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
		regex_match(stat_in, m, gc->switch_stat);
		
		condition = parseSwitchCondition(m[1].str());
		st = new Stat(gc, ids, m[2].str(), tabs+1);

		this->stat = indent + "loop do case " + condition + "\n" + 
										st->getStat() + 
									indent + "end; break; end\n";
		delete st;
	}
}