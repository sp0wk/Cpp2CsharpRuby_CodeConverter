#include "../class_TType.h"


// default ctor
TType::TType() 
{
	this->gc = NULL;
	this->type = 0;
	this->usertype = "";
}

//ctor
TType::TType(GrammarCompiler* gc, string& type_in) 
{
	this->gc = gc;
	this->usertype = "";
	
	if (type_in != "") {
		if (regex_match(type_in, gc->t_int)) this->type = 1;				//int
		else if (regex_match(type_in, gc->t_float)) this->type = 2;			//float
		else if (regex_match(type_in, gc->t_bool)) this->type = 3;			//bool
		else if (regex_match(type_in, gc->t_char)) this->type = 4;			//char
		else if (type_in == "void") this->type = 0;							//void
		else {																//usertype
			this->type = 5;
			this->usertype = type_in;
		}
	}
}

//methods
int TType::getType()
{
	return this->type;
}

string TType::getTypeInit()
{
	switch (this->type) {
		case 0: return "nil";
		case 1: return "0";
		case 2: return "0.0";
		case 3: return "false";
		case 4: return "\"\"";
		case 5: return usertype + ".new";
		default: return "nil";
	}
}