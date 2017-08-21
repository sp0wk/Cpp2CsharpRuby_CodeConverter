#include "../class_AssignExpr.h"


//constructor
AssignExpr::AssignExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in)
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	string lvalue = "";
	string rvalue = "";
	LogOrExpr* lo = NULL;				//lvalue
	InitClause* ic = NULL;				//rvalue
	CondExpr* ce = NULL;				//not assignment

	string* ptr_pair = NULL;			//pointer variable pair
	string pair = "";					//var name pair for pointer or reference

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->assign_expr_full)) {			// lvalue assign_operator rvalue

			lvalue = m[1].str();
			rvalue = m[3].str();
			lo = new LogOrExpr(gc, ids, lvalue);
			ic = new InitClause(gc, ids, rvalue);

			//ptr assign test
			ptr_pair = ids->getPtr(lvalue);

			if (ptr_pair != NULL) {	//if lvalue is pointer
				if (regex_match(rvalue, gc->unary_getaddr)) {	//if rvalue is &variable
					*ptr_pair = ic->getInit();					//link ptr and var in ids

					expr = lo->getExpr() + " " + m[2].str() + " Ptr.new(:" + ic->getInit() + ", binding)";
				}
				else {
					*ptr_pair = "";					//unlink pointer and previous variable

					expr = lo->getExpr() + " " + m[2].str() + " " + ic->getInit();
				}
			}
			else {	//test for re-assignment of connected to pointer/reference variable
				pair = ids->getPairId(lvalue);
				if (pair != "") {
					expr = lo->getExpr() + " = (" + pair + ".val " + m[2].str() + " " + ic->getInit() + ")";
				}
				else {	//simple assignment
					expr = lo->getExpr() + " " + m[2].str() + " " + ic->getInit();
				}
			}

			delete lo;
			delete ic;
		}
		else {		// conditional expression
			ce = new CondExpr(gc, ids, ex_in);

			expr = ce->getExpr();
			delete ce;
		}
	}
}