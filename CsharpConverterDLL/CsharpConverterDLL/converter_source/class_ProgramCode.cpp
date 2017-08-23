#include "class_ProgramCode.h"


//constructor
ProgramCode::ProgramCode(GrammarCompiler* gc, string& cppcode_in)
{
	this->gc = gc;
	this->csharp_code = "";

	Idvar* ids = new Idvar(gc);		// empty id list for code parts
	Parser* parser = NULL;
	smatch m;

	string functions = "";
	string statements = "";

	if (cppcode_in != "") {
		// detect code type

		if (regex_match(cppcode_in, m, gc->gl_expr)) {						// expression
			parser = new Expr(gc, ids, m[1].str());
		}
		else if (regex_match(cppcode_in, m, gc->gl_initializer)) {			// initialization
			parser = new Initializer(gc, ids, m[1].str());
		}
		else if (regex_match(cppcode_in, m, gc->gl_declaration)) {			// declaration
			parser = new Decl(gc, ids, m[1].str());
		}
		else if (regex_match(cppcode_in, m, gc->gl_statement)) {			// statements
			statements = m[1].str();
			//parse all statements
			sregex_iterator end;
			for (sregex_iterator iter(cbegin(statements), cend(statements), gc->stat_space); iter != end; iter++) {
				parser = new Stat(gc, ids, (*iter)[1].str(), 0);
				csharp_code += parser->getCsharpCode();
				delete parser;
				parser = nullptr;
			}
		}
		else if (regex_match(cppcode_in, m, gc->program_code)) {			// program code with functions
			functions = m[1].str();
			//parse all functions
			sregex_iterator end;
			for (sregex_iterator iter(cbegin(functions), cend(functions), gc->func_def_spc); iter != end; iter++) {
				parser = new FuncDef(gc, (*iter)[1].str());
				csharp_code += parser->getCsharpCode();
				delete parser;
				parser = nullptr;
			}
		}

		if (csharp_code == "" && parser) {
			csharp_code = parser->getCsharpCode();
			delete parser;
		}		
	}

	delete ids;
}