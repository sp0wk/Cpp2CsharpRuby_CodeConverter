#include "../class_TType.h"


// default ctor
TType::TType() 
{
	this->gc = NULL;
	this->type = "";
	this->usertype = false;
}

//ctor
TType::TType(GrammarCompiler* gc, string& type_in) 
{
	this->gc = gc;
	
	if (type_in != "") {
		if (regex_match(type_in, gc->sbyte)) type = "sbyte";				//sbyte
		else if (regex_match(type_in, gc->byte)) type = "byte";				//byte
		else if (regex_match(type_in, gc->int_signed)) type = "int";		//int
		else if (regex_match(type_in, gc->int_unsigned)) type = "uint";		//uint
		else if (regex_match(type_in, gc->sint_signed)) type = "short";		//short
		else if (regex_match(type_in, gc->sint_unsigned)) type = "ushort";	//ushort
		else if (regex_match(type_in, gc->lint_signed)) type = "long";		//long
		else if (regex_match(type_in, gc->lint_unsigned)) type = "ulong";	//ulong
		else if (regex_match(type_in, gc->t_float)) type = "float";			//float
		else if (regex_match(type_in, gc->t_double)) type = "double";		//double
		else if (regex_match(type_in, gc->t_char)) type = "char";			//char
		else if (regex_match(type_in, gc->t_bool)) type = "bool";			//bool
		else if (type_in == "void") type = "void";							//void
		else if (type_in == "auto") type = "var";							//var
		else { type = type_in; usertype = true; }							//user type
	}
}