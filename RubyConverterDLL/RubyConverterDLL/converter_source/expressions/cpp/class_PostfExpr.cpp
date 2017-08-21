#include "../class_PostfExpr.h"


// determine postfix operator and set oper_expr
int PostfExpr::determine_oper(string& op_in)
{
	smatch m;
	
	if (op_in == "++") return 1;
	else if (op_in == "--") return 2;
	else if (regex_match(op_in, m, gc->postfix_sqpars)) {				 
		Expr* expr_in_sqpars = new Expr(gc, ids, m[1].str());			//create parser for expression in square parentheses
		this->oper_expr = "[" + expr_in_sqpars->getExpr() + "]";

		delete expr_in_sqpars;

		return 3;	
	}
	else if (regex_match(op_in, m, gc->postfix_func)) {
		//test for empty pars
		if (m[1].str() != "") {
			InitList* il = new InitList(gc, ids, m[1].str());			//parse expr in parentheses
			this->oper_expr = "(" + il->getInit() + ")";

			delete il;
		}
		else {
			this->oper_expr = "()";
		}

		return 4;
	}
	else 
		return 0;
}


// constructor
PostfExpr::PostfExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";
	this->oper_expr = "";

	string part1 = "";
	string part2 = "";
	PostfExpr* pf = NULL;
	PostfExpr* class_member = NULL;

	string pair = "";

	smatch m, acm_m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->postfix_expr_full)) {				// if pf_operator present or access class member
			part1 = m[1].str();
			part2 = m[2].str();

			pf = new PostfExpr(gc, ids, part1);							// create new postfix parser fo first part

			if (regex_match(part2, acm_m, gc->postfix_dot_arrow)) {		// if expression is class member access
				class_member = new PostfExpr(gc, ids, acm_m[1].str());
				expr = pf->getExpr() + "." + class_member->getExpr();
				delete class_member;			
			}
			else {	//set ruby expr depending on operator
				switch (determine_oper(part2)) {
					case 1: {//++
								pair = ids->getPairId(pf->getExpr());
								if (pair != "")
									expr = "((" + pf->getExpr() + " = (" + pair + ".val+=1)-1)";
								else
									expr = "((" + pf->getExpr() + "+=1)-1)";		// ((x+=1)-1)
								break;
					}
					case 2: {//--
								pair = ids->getPairId(pf->getExpr());
								if (pair != "")
									expr = "((" + pf->getExpr() + " = (" + pair + ".val-=1)+1)";
								else
									expr = "((" + pf->getExpr() + "-=1)+1)";		// ((x-=1)+1)
								break;
					}
					case 3: {//[]
								expr = pf->getExpr() + this->oper_expr;
								break;
					}
					case 4: {//()
								expr = pf->getExpr() + this->oper_expr;
								break;
					}
					default: expr = pf->getExpr();
				}
			}

			delete pf;
		}
		else {	// just primary expr
			PrimaryExpr* pe = new PrimaryExpr(gc, ids, ex_in);		//create parser for primary expression
			expr = pe->getExpr();

			delete pe;
		}
	}
}