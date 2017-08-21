#include "../class_IfStat.h"


// parse condition
string IfStat::parseCondition(string& cond_in)
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
IfStat::IfStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	string indent = makeIndent(tabs);
	string condition = "";
	Stat* ifstat = NULL;
	Stat* elsestat = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->ifelse_stat);
		
		//parse "if" part
		condition = parseCondition(m[1].str());
		ifstat = new Stat(gc, ids, m[2].str(), tabs+1);
		this->stat = indent + "if " + condition + "\n" + ifstat->getStat();

		//parse "else" part if "else statement" present
		if (m[3].str() != "") {	
			elsestat = new Stat(gc, ids, m[3].str(), tabs+1);
			this->stat += (indent + "else\n" + elsestat->getStat());
			delete elsestat;
		} 
		
		//add "end" part
		this->stat += (indent + "end\n");
	}
}