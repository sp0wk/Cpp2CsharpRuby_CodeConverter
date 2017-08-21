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
	TType* newtype = new TType(gc, new_type);
	ArrayPart* ap = NULL;
	string arrpart = "";
	Initializer* init = NULL;
	smatch addr;


	if (ptr != "" && arr_part != "") {								// example:	 new int*[10]	- create empty array
		if (new_init != "") {
			init = new Initializer(gc, ids, new_init);
			result = "Array.[](" + init->getInit() + ")";
			delete init;
		}
		else {
			result = "Array.new()";
		}
	}
	else if (arr_part != "") {										// example:  new int[10]   - create new array	
		if (new_init != "") {
			init = new Initializer(gc, ids, new_init);
			result = "Array.[](" + init->getInit() + ")";
			delete init;
		}
		else {
			ap = new ArrayPart(gc, ids, arr_part);
			arrpart = (*ap)[0];
			delete ap;
			result = "Array.new(" + arrpart + ")";
		}
	}
	else if (ptr != "") {											// example:  new int*
		if (new_init != "") {
			init = new Initializer(gc, ids, new_init);

			if (regex_match(init->getPreInit(), addr, gc->unary_getaddr)) {	//new pointer to variable
				result = "Ptr.new(:" + init->getInit() + ", binding)";
			}
			else {
				result = init->getInit();							//assign new pointer to pointer
			}

			delete init;
		}
		else {
			result = "Ptr.new()";
		}
	}
	else if (newtype->getType() == 5) {								// example: new SomeClass
		if (new_init != "") {
			init = new Initializer(gc, ids, new_init);

			result = newtype->getTypeInit() + "("+ init->getInit() +")";		//result = SomeClass.new(...)

			delete init;
		}
		else {
			result = newtype->getTypeInit();
		}
	}
	else {															// example: new char
		if (new_init != "") {
			init = new Initializer(gc, ids, new_init);

			result = init->getInit();

			delete init;
		}
		else {
			result = "Ptr.new()";
		}
	}
	
	delete newtype;

	return result;
}


// constructor
UnaryExpr::UnaryExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in) 
{
	this->gc = gc;
	this->ids = ids;
	this->expr = "";

	string pair = "";

	smatch m;
	if (ex_in != "") {
		if (regex_match(ex_in, m, gc->unary_expr_full)) {				// unary_operator + expression
			//parse expression
			UnaryExpr* ue = new UnaryExpr(gc, ids, m[2].str());

			//set expr depending on operator
			switch (determine_oper(m[1].str())) {
				case 1: {//++ 
							pair = ids->getPairId(ue->getExpr());
							if (pair != "")
								expr = "(" + ue->getExpr() + " = (" + pair + ".val+=1)";
							else
								expr = "(" + ue->getExpr() + "+=1)";				// (x+=1)
							break;
				}
				case 2: {//--
							pair = ids->getPairId(ue->getExpr());
							if (pair != "")
								expr = "(" + ue->getExpr() + " = (" + pair + ".val-=1)";
							else
								expr = "(" + ue->getExpr() + "-=1)";				// (x-=1)
							break;
				}
				case 3: {//*
							expr = ue->getExpr() + ".val";							// dereference a pointer (Ptr ruby class)
							break;
				}
				case 4: {//&
							expr = ue->getExpr();									// var without address
							break;
				}
				case 5: {//!
							expr = " not( notfalse(" + ue->getExpr() + ") )";		// reverse operator (+ testing for 0)
							break;
				}
				case 6: {//+,-,~
							expr = m[1].str() + ue->getExpr();						// unary operator + , - or ~    + expression
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
			expr = "# " + ex_in;	//ignore delete expression
		}
		else {															// postfix expr
			PostfExpr* pe = new PostfExpr(gc, ids, ex_in);
			expr = pe->getExpr();
			delete pe;
		}
	}
}