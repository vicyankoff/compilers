#ifndef PARSER_H
#define PARSER_H

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

#include <iostream>

using namespace std;

class Parser {
   public:
      Parser (Scanner *s);
      ~Parser();
  
      bool parse_program();
  
   private:
      // 1
      bool parse_decl_list();
      // // 2 Predict
      // bool parse_variable_decl_list();
      // // 3
      // bool parse_variable_decl();
      // // 4
      // bool parse_procedure_decl_list();
      // // 5
      // bool parse_procedure_decl();
      // // 6
      // bool parse_arg_list();
      // // 7
      // bool parse_arg_list_hat();
      // // 8
      // bool parse_identifier_list();
      // // 9
      // bool parse_identifier_list_prm();
      // // 10
      // bool parse_standard_type();
      // // 11
      // bool parse_block();
      // // 12
      // bool parse_stmt_list(); 
      // // 13
      // bool parse_stmt_list_prm();
      // // 14
      // bool parse_stmt();
      // // 15
      // bool parse_stmt_ass_proc_tail();
      // // 16
      // bool parse_assignment_stmt_tail();
      // // 17
      // bool parse_if_stmt();
      // // 18
      // bool parse_if_stmt_hat();
      // // 19
      // bool parse_while_stmt();
      // // 20
      // bool parse_print_stmt();
      // // 21
      // bool parse_procedure_call_stmt_tail();
      // // 22
      // bool parse_expr_list();
      // // 23
      // bool parse_expr_list_hat();
      // // 24
      // bool parse_expr();
      // // 25
      // bool parse_expr_hat();
      // // 26
      // bool parse_simple_expr();
      // // 27
      // bool parse_simple_expr_prm();
      // // 28
      // bool parse_term();
      // // 29
      // bool parse_term_prm();
      // // 30
      // bool parse_factor();
      // // 31
      // bool parse_sign();

  
      // Return true if current word is the EOF token
      bool done_with_input();
  
      // The lexical analyzer
      Scanner *lex;
      // The current token the parser is looking at
      Token *word;
   
      string * expected;
      void parse_error (string *expected, Token *found);

      // Other helper functions that you may define
  
};

#endif