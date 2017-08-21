#ifndef DECL
#define DECL

#include "converter_source/class_GrammarCompiler.h"
#include "converter_source/other/class_Idvar.h"
#include "class_Declaration.h"
#include "converter_source/other/class_TType.h"
#include "converter_source/initialization/class_Initializer.h"
#include "converter_source/other/class_ArrayPart.h"



class Decl : public Declaration
{
private:
	string d_const;
	TType* d_type;

public:
	Decl(GrammarCompiler* gc, Idvar* ids, string& decl_in);
	~Decl() { delete d_type; };	

	string singleDecl(string& sd_in);				//parse single decl_init
	string parseDeclList(string& d_in);				//parse declarator list
};

#endif