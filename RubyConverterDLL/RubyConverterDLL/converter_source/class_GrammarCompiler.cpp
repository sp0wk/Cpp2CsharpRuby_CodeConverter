#include "class_GrammarCompiler.h"



GrammarCompiler::GrammarCompiler()
{
	//comments
	lc = as_xpr("//") >> -*_ >> _n;			// one line comment
	mlc = as_xpr("/*") >> -*_ >> "*/";		// multi line comment
	comments = *(lc >> *_s | mlc >> *_s);	// comments block
	spc	= *_s >> comments;					// space or comment or both

	
	keywords = as_xpr("alignas") | "continue" | "friend" | "register" | 
		"true" | "alignof" | "decltype" | "goto" | "reinterpret_cast" | "try" | 
		"asm" | "default" | "if" | "return" | "typedef" | "auto" | "delete" | "inline" | 
		"short" | "typeid" | "bool" | "do" | "int" | "signed" | "typename" | "break" | 
		"double" | "long" | "sizeof" | "union" | "case" | "dynamic_cast" | "mutable" | 
		"static" | "unsigned" | "catch" | "else" | "namespace" | "static_assert" | "using" | 
		"char" | "enum" | "new" | "static_cast" | "virtual" | "char16_t" | "explicit" | 
		"noexcept" | "struct" | "void" | "char32_t" | "export" | "nullptr" | "switch" | 
		"volatile" | "class" | "extern" | "operator" | "template" | "wchar_t" | "const" | 
		"false" | "private" | "this" | "while" | "constexpr" | "float" | "protected" | 
		"thread_local" | "const_cast" | "for" | "public" | "throw";
	
	correct_name = ~before(_b >> keywords >> _b) >> (('_' | range('a','z') | range('A', 'Z')) >> *_w);

	///////// variable identifier //////////
		namescope = (+(correct_name) >> *_s >> "::" >> *_s);
		idname = correct_name;
	idvar = *(s1= namescope) >> (s2= idname);


	////////////////////////	t_type	/////////////////////////////////
		//basic_types
			//integer
				int_sign = (as_xpr("signed") | "unsigned");
				int_size = (as_xpr("short") | "long" | "long long");
				t_int = !(int_sign) >> *_s >> !(int_size) >> *_s >> "int";
			//float
				t_float = as_xpr("float") | "double" | "long double";
			//char
				t_char = as_xpr("unsigned char") | "signed char" | "char" | "w_char_t" | "char16_t" | "char32_t";
			//bool
				t_bool = as_xpr("bool");
			
		t_basic = t_int | t_float | t_char | t_bool;
	
	// all standard types
	t_stdtype = t_basic | "void" | "auto";
	// user type name
	t_usertype = *(s1= namescope) >> (s2= correct_name);

	t_type = _b >> ((t_stdtype) | (t_usertype)) >> _b;
	
	
	/////////// t_pointer  //////////////////
		t_ref = *(as_xpr('*') >> *_s) >> '&';
		t_ptr = +('*' >> *_s);

	t_pointer = +('*' >> *_s) >> '&' | +as_xpr('*') | '&' ;


	///////////////// array part  ///////////////////////
	arr_part = as_xpr('[') >> *_s >> !(s1 = by_ref(const_expr)) >> *_s >> ']';
	
	
	/////////////////////	Literals	////////////////////// 
	
		// integer literal
			int10 = +_d;
			int2 = as_xpr('0') >> (set= 'b', 'B') >> +(set= '0', '1');
			int8 = as_xpr('0') >> +(range('0', '7'));
			int16 = as_xpr('0') >> (set= 'x', 'X') >> +xdigit;
		int_lit = int16 | int2 | int8 | int10;
		
		// char literal
			chr = as_xpr('\'') >> (s1= (!as_xpr("\\\\") >> (((set= '\\') >> _) | _)) | ((set= '\\') >> +alnum)) >> '\'';
			chars = as_xpr('\"') >> ("" | (-*(_) >> (~(set= '\\') | "\\\\"))) >> '\"';		//from	\"   to    any non "\" symbol + \"	or \\\"
		char_lit = chr | chars;
		
		// float literal
		float_lit =	+_d >> '.' >> +_d >> !((set= 'e', 'E') >> !(set= '+', '-') >> -+_d);	
		
		// bool literal
		bool_lit = as_xpr("true") | "false";
		
	literal = _b >> (float_lit | int_lit | bool_lit) >> _b | char_lit;
	
	
	
	///////////////////////// EXPRESSIONS ///////////////////////////////


		// primary
		primary_expr_pars = as_xpr('(') >> *_s >> (s1= by_ref(expression)) >> *_s >> ')';
		primary_expr = keep(idvar) | keep(literal) | keep(primary_expr_pars);


		// postfix
		postfix_func = as_xpr('(') >> *_s >> !(s1= by_ref(init_list)) >> *_s >> ')';						//function call
		postfix_dot_arrow = (as_xpr("->") | '.') >> *_s >> (s1= primary_expr >> *_s >> !(postfix_func));	//access class member operator
		postfix_sqpars = as_xpr('[') >> *_s >> (s1= by_ref(expression)) >> *_s >> ']';
		postfix_oper = keep("++") | keep("--") | keep(postfix_sqpars) | keep(postfix_func);
		postfix_expr = (s1= primary_expr) >> (s2= *(*_s >> postfix_oper)) >> !(s3= *_s >> postfix_dot_arrow);

		postfix_expr_full = (s1= primary_expr >> *(*_s >> postfix_oper)) >> (*_s >> (s2= postfix_oper | postfix_dot_arrow));
		

		// unary
		unary_oper = keep("++") | keep("--") | keep((set = '*', '&', '+', '-', '!', '~'));

		new_expr = _b >> as_xpr("new")>> _b >> *_s >> (s1= t_type) >> *_s >> !(s2= t_pointer) >> *_s >> !(s3= arr_part) >> *_s >> !(s4 = by_ref(initializer));
		del_expr = _b >> as_xpr("delete") >> _b >> *_s >> !('[' >> *_s >> ']') >> *_s >> by_ref(unary_expr);

		unary_expr = keep(new_expr) | keep(del_expr) | keep(*(*_s >> unary_oper) >> *_s >> postfix_expr);
		unary_getaddr = as_xpr('&') >> *_s >> (s1= *(*_s >> unary_oper) >> *_s >> postfix_expr);

		unary_expr_full = ((s1 = unary_oper) >> *_s) >> (s2 = *(unary_oper >> *_s) >> postfix_expr);
		

		// multiplication
		multipl_expr = unary_expr >> *(*_s >> (set = '*', '/', '%') >> *_s >> unary_expr);

		multipl_expr_full = (s1= unary_expr) >> *_s >> (s2= (set = '*', '/', '%')) >> *_s >> (s3= unary_expr 
			>> *(*_s >> (set = '*', '/', '%') >> *_s >> unary_expr));


		// addition
		add_expr = multipl_expr >> *(*_s >> (set = '+', '-') >> *_s >> multipl_expr);

		add_expr_full = (s1 = multipl_expr) >> *_s >> (s2 = (set = '+', '-')) >> *_s >> (s3 = multipl_expr 
			>> *(*_s >> (set = '+', '-') >> *_s >> multipl_expr));


		// shift
		shift_expr = add_expr >> *(*_s >> (as_xpr("<<") | ">>") >> *_s >> add_expr);

		shift_expr_full = (s1 = add_expr) >> *_s >> (s2 = as_xpr("<<") | ">>") >> *_s >> (s3 = add_expr 
			>> *(*_s >> (as_xpr("<<") | ">>") >> *_s >> add_expr));


		// relational
		relat_oper = keep((set = '<', '>')) | keep("<=") | keep(">=");
		relat_expr = shift_expr >> *(*_s >> relat_oper >> *_s >> shift_expr);

		relat_expr_full = (s1 = shift_expr) >> *_s >> (s2= relat_oper) >> *_s >> (s3 = shift_expr 
			>> *(*_s >> relat_oper >> *_s >> shift_expr));


		// equality
		equ_expr = relat_expr >> *(*_s >> (as_xpr("==") | "!=") >> *_s >> relat_expr);

		equ_expr_full = (s1 = relat_expr) >> *_s >> (s2 = as_xpr("==") | "!=") >> *_s >> (s3 = relat_expr
			>> *(*_s >> (as_xpr("==") | "!=") >> *_s >> relat_expr));


		// bitwise AND
		bw_and_expr = equ_expr >> *(*_s >> as_xpr('&') >> *_s >> equ_expr);

		bw_and_expr_full = (s1 = equ_expr) >> *_s >> (s2 = as_xpr('&')) >> *_s >> (s3 = equ_expr
			>> *(*_s >> as_xpr('&') >> *_s >> equ_expr));


		// bitwise Exclusive OR
		bw_eor_expr = bw_and_expr >> *(*_s >> as_xpr('^') >> *_s >> bw_and_expr);

		bw_eor_expr_full = (s1 = bw_and_expr) >> *_s >> (s2 = as_xpr('^')) >> *_s >> (s3 = bw_and_expr
			>> *(*_s >> as_xpr('^') >> *_s >> bw_and_expr));


		// bitwise Inclusive OR
		bw_ior_expr = bw_eor_expr >> *(*_s >> as_xpr('|') >> *_s >> bw_eor_expr);

		bw_ior_expr_full = (s1 = bw_eor_expr) >> *_s >> (s2 = as_xpr('|')) >> *_s >> (s3 = bw_eor_expr
			>> *(*_s >> as_xpr('|') >> *_s >> bw_eor_expr));


		// logical AND
		log_and_expr = bw_ior_expr >> *(*_s >> as_xpr("&&") >> *_s >> bw_ior_expr);

		log_and_expr_full = (s1 = bw_ior_expr) >> *_s >> (s2 = as_xpr("&&")) >> *_s >> (s3 = bw_ior_expr
			>> *(*_s >> (as_xpr("&&")) >> *_s >> bw_ior_expr));


		// logical OR
		log_or_expr = log_and_expr >> *(*_s >> as_xpr("||") >> *_s >> log_and_expr);

		log_or_expr_full = (s1 = log_and_expr) >> *_s >> (s2 = as_xpr("||")) >> *_s >> (s3 = log_and_expr
			>> *(*_s >> (as_xpr("||")) >> *_s >> log_and_expr));


		// conditional 
		cond_expr = log_or_expr >> !(*_s >> '?' >> *_s
			>> by_ref(expression) >> *_s >> ':' >> *_s >> by_ref(assign_expr));

		cond_expr_full = (s1 = log_or_expr) >> *_s >> '?' >> *_s >> (s2 = by_ref(expression)) >> *_s >> ':' >> *_s >> (s3 = by_ref(assign_expr));



		// assignment
		assign_oper = as_xpr('=') | "*=" | "/=" | "%=" | "+=" | "-=" | ">>=" | "<<=" | "&=" | "^=" | "|=";
		assign_expr = log_or_expr >> *_s >> assign_oper >> *_s >> by_ref(init_clause) | cond_expr;

		assign_expr_full = (s1= log_or_expr) >> *_s >> (s2= assign_oper) >> *_s >> (s3= by_ref(init_clause));


		// constant expression
		const_expr = cond_expr;
		
		
		// expression
		expression = assign_expr >> *(*_s >> ',' >> *_s >> assign_expr);


		expression_full = (s1 = assign_expr) >> *_s >> ',' >> *_s >> (s2 = assign_expr
			>> *(*_s >> ',' >> *_s >> assign_expr));


		
		//--------------------------------------  DECLARATION  ---------------------------------------------------
		

		/////////////////////////////// INITIALIZATION //////////////////////////////////

		// initializer clause
		init_clause = keep(by_ref(braced_init_list)) | keep(assign_expr);

		// equal initializer
		equal_init = as_xpr('=') >> *_s >> (s1= init_clause);

		// initializer list
		init_list = init_clause >> *(*_s >> ',' >> *_s >> init_clause);

		init_list_full = (s1= init_clause) >> *_s >> ',' >> *_s >> (s2= init_clause 
			>> *(*_s >> ',' >> *_s >> init_clause));

		// braced init list
		braced_init_list = as_xpr('{') >> *_s >> !(s1= init_list) >> *_s >> '}';

		// initializers
		init_expr_list = as_xpr('(') >> *_s >> !(s1= init_list) >> *_s >> ')';

		initializer = init_expr_list | equal_init | braced_init_list;
		
		
		////////////////////////////// Declarators //////////////////////////////////
				
		// declarator (without initialization)
		decl_ptr = t_pointer;									// pointer modifier
		decl_id = idvar;										// variable name
		decl_arr_part = *(*_s >> arr_part);						// array part of declarator


		declarator = !(s1= decl_ptr) >> *_s >> (s2= decl_id) >> (s3= decl_arr_part);
				
		
		// init declarator (with initialization)
		decl_init = (s1= declarator) >> *_s >> !(s2= initializer);

		decl_init_full = !(s1= decl_ptr) >> *_s >> (s2= decl_id) >> (s3= decl_arr_part) >> *_s >> !(s4= initializer);
		
		
		// init declarator list
		decl_list = (s1= decl_init) >> *(*_s >> ',' >> *_s >> decl_init);

		decl_list_full = (s1 = decl_init) >> *_s >> ',' >> *_s >> (s2 = decl_init
			>> *(*_s >> ',' >> *_s >> decl_init));
				
		


		///////////////////////////////// Declaration /////////////////////////////////////////

		decl_qualifier = as_xpr("const");				// quailifier
		decl_type = t_type;								// declaration specifier (type)
		single_decl = !(s1 = decl_qualifier) >> *_s >> (s2 = decl_type) >> *_s >> (s3 = declarator) >> !(*_s >> '=' >> *_s >> (s4= init_clause));	//for condition decl and parameters

		declaration = !(s1 = decl_qualifier) >> *_s >> (s2 = decl_type) >> *_s >> (s3= decl_list);


		// function definition
		ret_val = (s1= decl_type) >> *_s >> !(s2= decl_ptr);								//return value
		param_list = (s1= single_decl) >> *(*_s >> ',' >> *_s >> single_decl);				//function parameter list
		param_list_full = (s1 = single_decl) >> *_s >> ',' >> *_s >> (s2 = single_decl
			>> *(*_s >> ',' >> *_s >> single_decl));

		func_def =  ret_val >> *_s >> (s1= decl_id) >> *_s >> '(' >> *_s >> !(s2= param_list) >> *_s >> ')' >> spc >> (s3= by_ref(comp_stat));

				
		//--------------------------------------------------------------------------------------------------------




		//--------------------------------------------- STATEMENTS -----------------------------------------------

		///// console input/output
			cin_part = *_s >> as_xpr(">>") >> *_s >> (s1= add_expr);
			cout_part = *_s >> as_xpr("<<") >> *_s >> (s1= add_expr);
			cin = _b >> (as_xpr("cin") | "std::cin") >> _b >> (s1= +(cin_part)) >> *_s >> ";";
			cout = _b >> (as_xpr("cout") | "std::cout") >> _b >> (s1= +(cout_part)) >> *_s >> ";";

		console_io = cin | cout;

		///// labeled statement
			lbl_case = as_xpr("case") >> *_s >> (s1= const_expr) >> *_s >> ':' >> spc >> (s2= by_ref(statement));
			lbl_def = as_xpr("default") >> *_s >> ':' >> spc >> (s1= by_ref(statement));
		
		lbl_stat = keep(lbl_def) | keep(lbl_case);


		///// expression statement
		expr_stat = !(s1= expression) >> *_s >> ';';
		

		///// compound statement
		comp_stat = as_xpr('{') >> spc >> (s1= *(by_ref(statement) >> spc)) >> '}';							

		
		//////////////////////// Selection statement (if, if else, switch) ///////////////////////////
		condition = keep(single_decl) | keep(expression);


		////// if statement
		if_stat = as_xpr("if") >> *_s >> '(' >> *_s >> (s1 = condition) >> *_s >> ')' >> spc
								>> (s2= by_ref(statement));


		////// if else statement
		ifelse_stat = as_xpr("if") >> *_s >> '(' >> *_s >> (s1 = condition) >> *_s >> ')' >> spc
								>> (s2 = by_ref(statement)) >> spc
								>> !("else" >> spc 
								>> (s3 = by_ref(statement)));



		////// switch statement
		switch_stat = as_xpr("switch") >> *_s >> '(' >> *_s >> (s1 = condition) >> *_s >> ')' >> spc 
									>> (s2 = by_ref(statement));



		select_stat = keep(switch_stat) | keep(ifelse_stat) | keep(if_stat);


		////////////////////// Iteration statement (for, while , do while) ////////////////////////////

		///// while statement
		while_stat = as_xpr("while") >> *_s >> '(' >> *_s >> (s1 = condition) >> *_s >> ')' >> spc 
									>> (s2 = by_ref(statement));



		///// do while statement
		dowhile_stat = as_xpr("do") >> spc 
									>> (s1= by_ref(statement)) >> *_s 
									>> "while" >> *_s >> '(' >> *_s >> (s2= expression) >> *_s >> ')' >> *_s >> ';';



		///// for statement
		for_init_stat = keep(by_ref(decl_stat)) | keep(expr_stat);

		for_stat = as_xpr("for") >> *_s 
			>> '(' >> *_s >> (s1= for_init_stat) >> *_s >> !(s2= condition) >> *_s >> ';' >> *_s >> !(s3= expression) >> *_s >> ')' >> spc
			>> (s4= by_ref(statement));



		iter_stat = keep(for_stat) | keep(dowhile_stat) | keep(while_stat);


		///////////////////////// Jump statements (break, continue, return)//////////////////////////
		jump_return = as_xpr("return") >> *_s >> !(s1= expression) >> *_s >> ';';
		jump_continue = as_xpr("continue") >> *_s >> ';';
		jump_break = as_xpr("break") >> *_s >> ';';

		jump_stat = keep(jump_return) | keep(jump_continue) | keep(jump_break);


		//////////////////////  Declaration statement /////////////////////////////////
		decl_stat = (s1= declaration) >> *_s >> ';';



		statement = (keep(expr_stat) | keep(comp_stat) | keep(iter_stat) | keep(select_stat) | keep(lbl_stat) | keep(jump_stat) | keep(decl_stat));
		stat_space = (s1= statement) >> spc;

		
		func_def_spc = (s1= func_def) >> spc;
		program_code = -*_ >> (s1= +(func_def >> spc)) >> *_;


		// SOME ELEMENTS FOR GLOBAL PARSING
		gl_expr = spc >> (s1= expression) >> spc;
		gl_initializer = spc >> (s1= initializer) >> spc;
		gl_declaration = spc >> (s1= declaration) >> spc;
		gl_statement = spc >> (s1= +(stat_space)) >> spc;
	
}