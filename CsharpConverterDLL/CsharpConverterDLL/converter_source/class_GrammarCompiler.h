#ifndef GCOMP
#define GCOMP

#include <boost/xpressive/xpressive.hpp>



using namespace boost::xpressive;
using namespace boost::xpressive::regex_constants;



class GrammarCompiler
{
public:
	//ctor and dtor
	GrammarCompiler();
	~GrammarCompiler() {};

	//public members
		
		//////// keywords	
		sregex keywords, correct_name;

		//////// comments
		sregex lc, mlc, comments, spc;

		//////// var identifier
		sregex namescope, idname, idvar;

		//////// t_types
			//// byte
			sregex sbyte, byte, t_byte;
			//// int
			sregex int_signed, int_unsigned, sint_signed, sint_unsigned, lint_signed, lint_unsigned, t_int;
			//// float
			sregex t_float, t_double;
			//// other
			sregex t_char, t_bool, t_basic, t_stdtype, t_usertype, t_type;

		//////// t_pointer
		sregex t_ref, t_ptr, t_pointer;

		//////// array part
		sregex arr_part;

		//////// literals
			//// integer
			sregex int16, int2, int8, int10, int_lit;
			//// char
			sregex chr, chars, char_lit;
			//// float
			sregex float_lit;
			//// bool
			sregex bool_lit;

		sregex literal;

		//////// EXPRESSIONS
			//// primary
			sregex primary_expr, primary_expr_pars;
			//// postfix
			sregex postfix_oper, postfix_dot_arrow, postfix_sqpars, postfix_func, postfix_expr, postfix_expr_full;
			//// unary
			sregex new_array, new_expr, del_expr, unary_oper, unary_expr, unary_getaddr, unary_expr_full;
			//// multiplication
			sregex multipl_expr, multipl_expr_full;
			//// addition
			sregex add_expr, add_expr_full;
			//// shift
			sregex shift_expr, shift_expr_full;
			//// relational
			sregex relat_oper, relat_expr, relat_expr_full;
			//// equality
			sregex equ_expr, equ_expr_full;
			//// bitwise AND
			sregex bw_and_expr, bw_and_expr_full;
			//// bitwise Exclusive OR
			sregex bw_eor_expr, bw_eor_expr_full;
			//// bitwise Inclusive OR
			sregex bw_ior_expr, bw_ior_expr_full;
			//// logical AND
			sregex log_and_expr, log_and_expr_full;
			//// logical OR
			sregex log_or_expr, log_or_expr_full;
			//// conditional
			sregex cond_expr, cond_expr_full;
			//// assignment
			sregex assign_oper, assign_expr, assign_expr_full;
			//// constant expression
			sregex const_expr = cond_expr;

		sregex expression, expression_full;

		//////// DECLARATION
			//// Initialization
			sregex init_clause, equal_init, init_list, init_list_full, braced_init_list, init_expr_list, initializer;
			//// Declarators
			sregex decl_ptr, decl_id, decl_arr_part, declarator, decl_init, decl_init_full, decl_list, decl_list_full;
			//// Function definition
			sregex ret_val, param_list, param_list_full;

		sregex decl_qualifier, decl_type, declaration, single_decl, func_def;

		//////// STATEMENTS
			//// console input/output
			sregex cin_part, cin, cout_part, cout, console_io;
			//// labeled statement (case, default)
			sregex lbl_case, lbl_def, lbl_stat;
			//// expression statement
			sregex expr_stat;
			//// compound statement
			sregex comp_stat;
			//// selection statement (if, if-else, switch)
			sregex condition;
			sregex if_stat, ifelse_stat, switch_stat, select_stat;
			//// iteration statement (while, do-while, for)
			sregex while_stat, dowhile_stat, for_init_stat, for_stat, iter_stat;
			//// jump statement (break, continue, return)
			sregex jump_return, jump_continue, jump_break, jump_stat;
			//// declaration statement
			sregex decl_stat;

		sregex statement, stat_space;

		sregex func_def_spc, program_code;

		// GLOBAL PARSING
		sregex gl_expr, gl_initializer, gl_declaration, gl_statement;
};

#endif