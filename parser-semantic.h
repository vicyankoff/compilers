#ifndef PARSER-SEMANTIC_H
#define PARSER-SEMANTIC_H

#include "token.h"
#include "keywordtoken.h"
#include "punctoken.h"
#include "reloptoken.h"
#include "addoptoken.h"
#include "muloptoken.h"
#include "idtoken.h"
#include "numtoken.h"
#include "eoftoken.h"
#include "scanner.h"
#include "symbol_table.h"

#include <iostream>

using namespace std;

class Parser {
public:
	Parser (Scanner *s);
	~Parser();
	
	bool parse_program();

      // Return true if current word is the EOF token
	bool done_with_input();
	
private:
      // 1
	bool parse_decl_list();
      // 2 Predict
	bool parse_variable_decl_list();
      // 3
	bool parse_variable_decl();
      // 4
	bool parse_procedure_decl_list();
      // 5
	bool parse_procedure_decl();
      // 6
	bool parse_arg_list();
      // 7
	bool parse_arg_list_hat();
      // 8
	bool parse_identifier_list();
      // 9
	bool parse_identifier_list_prm();
      // 10
	bool parse_standard_type(expr_type &standard_type_type);
      // 11
	bool parse_block();
      // 12
	bool parse_stmt_list(); 
      // 13
	bool parse_stmt_list_prm();
      // 14
	bool parse_stmt();
      // 15
	bool parse_stmt_ass_proc_tail(expr_type &stmt_ass_proc_tail_type);
      // 16
	bool parse_assignment_stmt_tail(expr_type &assignment_stmt_tail_type);
      // 17
	bool parse_if_stmt();
      // 18
	bool parse_if_stmt_hat();
      // 19
	bool parse_while_stmt();
      // 20
	bool parse_print_stmt();
      // 21
	bool parse_procedure_call_stmt_tail();
      // 22
	bool parse_expr_list();
      // 23
	bool parse_expr_list_hat();
      // 24
	bool parse_expr(expr_type &the_expr_type);
      // 25
	bool parse_expr_hat(expr_type &expr_hat_type);
      // 26
	bool parse_simple_expr(expr_type &simple_expr_type);
      // 27
	bool parse_simple_expr_prm(expr_type &simple_expr_prm_type);
      // 28
	bool parse_term(expr_type &term_type);
      // 29
	bool parse_term_prm(expr_type &term_prm_type);
      // 30
	bool parse_factor(expr_type &factor_type);
      // 31
	bool parse_sign();
	
      // The lexical analyzer
	Scanner *lex;
      // The current token the parser is looking at
	Token *word;
	// The symbol table
	Symbol_Table * stab;

	/* The current environment we are doing semantic analysis in.
	 * It will be either the main program name or a procedure
	 * name.
	 */
	 string *current_env;	

	// The main environment. Always the name of the main program
	 string *main_env;

	/* Used in semantic analysis to determine which position a paramenter
	 * is in during the parsing of actual parameters and formal parameters
	 */
	 int parm_pos;


	 void variable_already_declared_error(string * variable);

	 string * expected;

	 void parse_error (string *expected, Token *found);

	// Called when a type error occurs. "where" is the current token
	 void type_error(Token *where);

	/* Called when an undeclared identifier is referenced in a statement
	 * Print the identifier and the current environment
	 */
	 void undeclared_id_error(string *id, string *env, string * function_call);
	};

#endif

