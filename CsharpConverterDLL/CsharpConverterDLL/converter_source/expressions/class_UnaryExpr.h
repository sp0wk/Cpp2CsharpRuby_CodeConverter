#ifndef UNARYEXPR
#define UNARYEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_PostfExpr.h"
#include "converter_source/other/class_ArrayPart.h"
#include "converter_source/other/class_TType.h"
#include "converter_source/initialization/class_Initializer.h"

using std::string;


class UnaryExpr : public Expression
{
public:
	UnaryExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~UnaryExpr() {};

	int determine_oper(string& op_in);		//0 - "", 1 - "++", 2 - "--", 3 - *, 4 - &, 5 - !, 6 - {+,-,~}
	string new_expr(string& new_type, string& ptr, string& arr_part, string& new_init);
};

#endif