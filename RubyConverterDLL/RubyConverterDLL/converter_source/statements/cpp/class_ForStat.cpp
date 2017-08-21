#include "../class_ForStat.h"



//parse for initialization statement
string ForStat::parseForInit(string& init_in)
{
	string result = "";
	DeclStat* decl = NULL;
	ExprStat* expr = NULL;

	if (regex_match(init_in, gc->decl_stat)) {		//if init stat is declaration statement
		decl = new DeclStat(gc, ids, init_in, this->tabs);
		result = decl->getStat();
		delete decl;
	}
	else {		// init stat is expression statement
		expr = new ExprStat(gc, ids, init_in, this->tabs);
		result = expr->getStat();
		delete expr;
	}
	return result;
}



// parse "for" condition
string ForStat::parseCondition(string& cond_in)
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
ForStat::ForStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	smatch m;
	string indent = makeIndent(tabs);
	string forinit = "";
	string condition = "";
	string forexpr = "";
	Expr* expr = NULL;
	Stat* st = NULL;

	if (stat_in != "") {
		regex_match(stat_in, m, gc->for_stat);
		
		//init part
		forinit = parseForInit(m[1].str());

		//condition part
		if (m[2].str() != "") 
			condition = parseCondition(m[2].str());
		else
			condition = "true";

		//expression part
		if (m[3].str() != "") {
			expr = new Expr(gc, ids, m[3].str());
			forexpr = expr->getExpr();
			delete expr;
		}

		//statement part
		st = new Stat(gc, ids, m[4].str(), tabs+1);

		this->stat = forinit +
					indent + "while " + condition + "\n" + 
						st->getStat() + "\n" +
						makeIndent(tabs+1) + forexpr + "\n" +
					indent + "end\n";
		delete st;
	}
}