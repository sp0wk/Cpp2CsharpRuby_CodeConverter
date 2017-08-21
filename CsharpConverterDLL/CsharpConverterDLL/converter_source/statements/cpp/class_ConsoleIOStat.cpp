#include "../class_ConsoleIOStat.h"


//constructor
ConsoleIOStat::ConsoleIOStat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs = 0)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	string cins = "";
	string couts = "";

	smatch m;

	if (stat_in != "") {
		
		if (regex_match(stat_in, m, gc->cin)) {
			cins = m[1].str();
			this->stat = parseCIN(cins);
		}
		else if (regex_match(stat_in, m, gc->cout)) {
			couts = m[1].str();
			this->stat = parseCOUT(couts);
		}
	}
}

string ConsoleIOStat::parseCIN(string& cins) 
{
	string result = "";

	smatch m;
	AddExpr* exp = NULL;
	string input = "";
	string vartype = "";
	string newio = "";

	sregex_iterator end;
	for (sregex_iterator iter(cbegin(cins), cend(cins), gc->cin_part); iter != end; iter++) {
		exp = new AddExpr(gc, ids, (*iter)[1].str());
		input = exp->getExpr();

		if (regex_match(input, gc->idvar)) {		// if input is variable
			if (ids) vartype = this->ids->getVarType(input);

			if (vartype != "") {
				newio = input + " = " + vartype + ".Parse(Console.ReadLine());\n";
			}
			else {
				newio = input + " = Console.ReadLine();\n";
			}
		}
		else {	// unknown input
			newio = input + " = Console.ReadLine();\n";			
		}
		
		result += makeIndent(tabs) + newio;

		delete exp;
		exp = NULL;
	}

	return result;
}


string ConsoleIOStat::parseCOUT(string& couts) 
{
	string result = "";

	AddExpr* exp = NULL;
	string output = "";
	string newio = "";

	sregex_iterator end;
	for (sregex_iterator iter(cbegin(couts), cend(couts), gc->cout_part); iter != end; iter++) {
		exp = new AddExpr(gc, ids, (*iter)[1].str());
		output = exp->getExpr();

		newio = "Console.Write(" + output + ");\n";
		
		result += makeIndent(tabs) + newio;

		delete exp;
		exp = NULL;
	}

	return result;
}