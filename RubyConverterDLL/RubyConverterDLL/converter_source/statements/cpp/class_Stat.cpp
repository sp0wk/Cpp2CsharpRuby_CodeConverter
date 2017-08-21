#include "../class_Stat.h"


//constructor
Stat::Stat(GrammarCompiler* gc, Idvar* ids, string& stat_in, int tabs)
{
	this->gc = gc;
	this->ids = ids;
	this->stat = "";
	this->tabs = tabs;

	Parser* parser = NULL;

	if (stat_in != "") {
		if (regex_match(stat_in, gc->console_io)) {
			parser = new ConsoleIOStat(gc, ids, stat_in, tabs);				//cin or cout statement
		}
		else if (regex_match(stat_in, gc->decl_stat)) {							//declaration statement
			parser = new DeclStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->expr_stat)) {						//expression statement
			parser = new ExprStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->comp_stat)) {						//compound statement
			parser = new CompStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->while_stat)) {					//while loop statement
			parser = new WhileStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->dowhile_stat)) {					//do-while loop statement
			parser = new DowhileStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->for_stat)) {						//for loop statement
			parser = new ForStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->ifelse_stat)) {					//if-else statement
			parser = new IfStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->switch_stat)) {					//switch statement
			parser = new SwitchStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->lbl_stat)) {						//label statement
			parser = new LblStat(gc, ids, stat_in, tabs);
		}
		else if (regex_match(stat_in, gc->jump_stat)) {						//jump statement
			parser = new JumpStat(gc, ids, stat_in, tabs);
		}
		
		if (parser != NULL) {
			this->stat = parser->getRubyCode();
			delete parser;
		}
	}
}