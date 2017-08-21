#define _BUILD_DLL_
#include "DLLHeader.h"

#include "converter_source\class_GrammarCompiler.h"
#include "converter_source\class_ProgramCode.h"
#include <string>


FUNCTION char* convertCppToCsharp(char** code_in)
{
	std::string codestring = *code_in;
	GrammarCompiler gc;
	ProgramCode pcode(&gc, codestring);
	char* result = _strdup((pcode.getCsharpCode()).c_str());
	return result;
}
