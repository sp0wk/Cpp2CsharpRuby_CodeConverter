#ifndef ADDEXPR
#define ADDEXPR

#include <string>
#include "class_Expression.h"
#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_MultipExpr.h"

using std::string;


class AddExpr : public Expression
{
public:
	AddExpr(GrammarCompiler* gc, Idvar* ids, string& ex_in);
	~AddExpr() {};
};

#endif