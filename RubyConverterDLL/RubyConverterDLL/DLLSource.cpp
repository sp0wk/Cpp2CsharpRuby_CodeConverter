#define _BUILD_DLL_
#include "DLLHeader.h"

#include "converter_source\class_GrammarCompiler.h"
#include "converter_source\class_ProgramCode.h"
#include <string>


FUNCTION char* convertCppToRuby(char** code_in)
{
	std::string codestring = *code_in;
	GrammarCompiler gc;
	ProgramCode pcode(&gc, codestring);
	char* result = _strdup((pcode.getRubyCode()).c_str());
	return result;
}
