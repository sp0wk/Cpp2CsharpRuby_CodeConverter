#ifndef POSTFEXPR
#define POSTFEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_PrimaryExpr.h"
#include "class_Expr.h"
#include "converter_source/initialization/class_InitList.h"


using std::string;


class PostfExpr : public Expression
{
private:
	string oper_expr;		

public:
	PostfExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~PostfExpr() {};

	int determine_oper(string& op_in);		//0 - "", 1 - "++", 2 - "--", 3 - [expr], 4 - (!expr)
};

#endif