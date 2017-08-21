#include "../class_ArrayPart.h"


ArrayPart::ArrayPart(GrammarCompiler* gc, Idvar* ids, string& arr_in)
{
	this->gc = gc;
	this->ids = ids;

	if (arr_in != "") {
		// fill vector with array sizes
		sregex_iterator end;
		for (sregex_iterator iter(cbegin(arr_in), cend(arr_in), gc->arr_part); iter != end; iter++) {
			CondExpr* ce = new CondExpr(gc, ids, (*iter)[1].str());
			sizes.push_back(ce->getExpr());
			delete ce;
			ce = NULL;
		}
	}
}


string ArrayPart::getArrayInit() 
{
	switch (sizes.size()) {
		case 1: return "Array.new(" + sizes[0] + ")";															//1d array
		case 2: return "Array.new(" + sizes[0] + ", Array.new("+sizes[1]+"))";									//2d array
		case 3: return "Array.new(" + sizes[0] + ", Array.new("+sizes[1]+", Array.new("+sizes[2]+")))";			//3d array
		default: return "[]";																					//empty 1d array
	}
}


int ArrayPart::getArrayType()
{// return number of "[]"
	return sizes.size();
}


string ArrayPart::operator[] (int i)
{// return size in "[]"(i)
	return sizes[i];
}