#include "../class_UnaryExpr.h"


// determine unary operator
int UnaryExpr::determine_oper(string& op_in)
{
	if (op_in == "") return 0;
	else if (op_in == "++") return 1;
	else if (op_in == "--") return 2;
	else if (op_in == "*") return 3;
	else if (op_in == "&") return 4;
	else if (op_in == "!") return 5;
	else return 6;
}


// parse "new" expression
string UnaryExpr::new_expr(string& new_type, string& ptr, string& arr_part, string& new_init)
{
	string result = "";
	TType* type = new TType(gc, new_type);
	ArrayPart* ap = NULL;
	Initializer* init = NULL;
	smatch addr;


	if (arr_part != "") {											// example:	 new int[2] { 1, 2 }
		ap = new ArrayPart(gc, ids, arr_part);
		init = new Initializer(gc, ids, new_init);
		result = "new " + type->getType() + ap->getArrayPart() + init->getInit();
		delete ap;
		delete init;
	}
	else if (ptr != "") {											// example:  new int*
		init = new Initializer(gc, ids, new_init);

		result = "new " + type->getType() + "(" + init->getInit() + ")  /* UNSAFE POINTER */";

		delete init;
	}
	else if (type->isUserType()) {								// example: new SomeClass
		init = new Initializer(gc, ids, new_init);

		result = "new " + type->getType() + "(" + init->getInit() + ")";

		delete init;
	}
	else {															// example: new int(30)
		if (new_init != "") {
			init = new Initializer(gc, ids, new_init);

			result = init->getInit() + "	/* DEDUCED FROM POINTER */";

			delete init;
		}
		else {
			result = "null	/* UNSAFE POINTER */";
		}
	}
	
	delete type;

	return result;
}


// constructor
UnaryExpr::UnaryExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in) 
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->unary_expr_full)) {				// unary_operator + expression
			//parse expression
			UnaryExpr* ue = new UnaryExpr(gc, ids, m[2].str());

			//set expr depending on operator
			switch (determine_oper(m[1].str())) {
				case 1: {//++ 
					expr = "++" + ue->getExpr();	
					break;
				}
				case 2: {//--
					expr = "--" + ue->getExpr();
					break;
				}
				case 3: {//*
					expr = ue->getExpr() + "/* DEREFERENCED POINTER */";			// dereference a pointer
					break;
				}
				case 4: {//&
					expr = ue->getExpr() + "/* ADDRESS-OF */";						// var without address
					break;
				}
				case 5: {//!
					expr = "!(Convert.ToBoolean(" + ue->getExpr() + "))";			// reverse operator (+ testing for 0)
					break;
				}
				case 6: {//+,-,~
					expr = m[1].str() + ue->getExpr();								// unary operator + , - or ~    + expression
					break;
				}
				default: expr = ue->getExpr();
			}
			delete ue;
		}
		else if (regex_match(ex_in, m, gc->new_expr)) {					// "new" expression
			expr = this->new_expr(m[1].str(), m[2].str(), m[3].str(), m[4].str());
		}
		else if (regex_match(ex_in, m, gc->del_expr)) {					// "delete" expression
			expr = "/* " + ex_in + " */";		//ignore delete expression
		}
		else {															// postfix expr
			PostfExpr* pe = new PostfExpr(gc, ids, ex_in);
			expr = pe->getExpr();
			delete pe;
		}
	}
}