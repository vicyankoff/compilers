#include "parser.h"

Parser::Parser(Scanner *s) 
{
	lex = s;
	word = lex->next_token();
}

Parser::~Parser() 
{
	if (lex != null) {
		delete lex;
	}
	if (word != null) {
		delete word;
	}	
}

bool Parser::done_with_input() 
{
	return word->get_token_type() == TOKEN_EOF;
}

bool Parser::parse_program() 
{
	// PROGRAM -> program identifier ; DECL_LIST BLOCK ;
	// Predict (program identifier ; DECL_LIST BLOCK ;) == {program}

	// Match keyword program
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROGRAM)
	{
		/* Advance - Notice that we only delete a token on an ADVANCE, and, if we
		ADVANCE, it is the ADVANCE code that is responsible for getting the next token.
		*/
		delete word;
		word = lex->next_token();

		// Match identifier
		if (word->get_token_type() == TOKEN_ID)
		{
			// ADVANCE
			delete word;
			word = lex->next_token();	

			// Match ;
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI)
			{
				// ADVANCE
				delete word;
				word = lex->next_token();

				// Match DECL_LIST
				if (parse_decl_list())
				{
					// Match BLOCK - ACTION
					if (parse_block()) 
					{
						// Match ;
						if (word->get_token_type() == TOKEN_PUNC
							&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI)
						{

							// ADVANCE
							delete word;
							word = lex->next_token();
							return true;
						} else 
						{ // Failed to match the second semicolon
							expected = new string ("';'");
							parse_error (expected, word);
							delete expected;
							delete word;
							return false;
						}
					} else
					{ // Failed to parse BLOCK
						return false;
					}

				} else
				{ // Failed to parse DECL_LIST
					return false;
				}
			} else
			{ // Failed to match the first semicolon
				expected = new string ("';'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{ // Failed to match an identifier			
			expected = new string ("identifier");
			parse_error(expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else 
	{ // Failed to match the keyword program
		expected = new string ("program");
		parse_error(expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_decl_list()
{
	if (word->get_token_type() == TOKEN_ID
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROCEDURE)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN))
	{
		
		if (parse_variable_decl_list()) 
		{
		
			if (parse_procedure_decl_list()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("identifier, keyword \"begin\" or keyword \"procedure\"");
		parse_error (expected, word);
    	delete expected;
    	delete word;
		return false;
	}
	return false;
}

bool Parser::parse_variable_decl_list()
{
	// VARIABLE_DECL_LIST -> VARIABLE_DECL ; VARIABLE_DECL_LIST
	// Predict (VARIABLE_DECL_LIST -> VARIABLE_DECL ; VARIABLE_DECL_LIST) = {identifier}
	if (word->get_token_type() == TOKEN_ID) 
	{

		// Match VARIABLE_DECL
		if (parse_variable_decl()) 
		{
			
			// Match ;
			if (word->get_token_type == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute == PUNC_SEMI) 
			{
				delete word;
				word = lex->next_token();

				if (parse_variable_decl_list()) 
				{
					return true;
				} else 
				{ // Failed to match VARIABLE_DECL_LIST
					return false;
				}
			} else 
			{ // Failed to match ;
				expected = new string ("';'")
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}

		} else 
		{ // Failed to match VARIABLE_DECL
			return false;
		}

	} else if ((word->get_token_type() == TOKEN_KEYWORD
					&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROCEDURE)
				|| (word->get_token_type == TOKEN_KEYWORD
					&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)) 
	{
		return true;
	} else 
	{
		expected = new string ("identifier or procedure or begin");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_variable_decl()
{
	// VARIABLE_DECL -> IDENTIFIER_LIST : STANDARD_TYPE
	// Predict {identifier}
	if (word->get_token_type == TOKEN_ID ) 
	{
		// Match IDENTIFIER_LIST
		if (parse_identifier_list()) 
		{

			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COLON) 
			{
				delete word;
				word = lex->next_token();
		
				if (parse_standard_type()) {
					return true;
				} else 
				{ // Failed to match STANDARD_TYPE
					return false;
				}
			} else 
			{
				expected = new string ("':'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("identifier");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_procedure_decl_list() 
{
	// procedure_decl_list -> procedure_decl ; procedure_decl_list
	// Predict = {procedure}
	if (word->get_token_type == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute == KW_PROCEDURE) 
	{

		if (parse_procedure_decl()) 
		{
			
			if (word->get_token_type == TOKEN_PUNC 
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) 
			{
				delete word;
				word = lex->next_token();

				if (parse_procedure_decl_list()) 
				{
					return true;
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("';'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			return false;
		}
	} else if (word->get_token_type == TOKEN_KEYWORD
			 	&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN) 
	{
		return true;
	} else 
	{
		expected = new string ("procedure or begin");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_procedure_decl()
{
	// PROCEDURE_DECL -> procedure identifier ( ARG_LIST ) VARIABLE_DECL_LIST BLOCK
	// Predict {procedure}

	if (word->get_token_type == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROCEDURE) 
	{
		delete word;
		word = lex->next_token();

		if (word->get_token_type == TOKEN_ID) 
		{
			delete word;
			word = lex->next_token();
			
			if (word->get_token_type == TOKEN_PUNC 
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN) 
			{
				delete word;
				word = lex->next_token();
			
				if (parse_arg_list()) 
				{
			
					if (word->get_token_type() == TOKEN_PUNC 
						&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
					{
						delete word;
						word = lex->next_token();
			
						if (parse_variable_decl_list()) 
						{
			
							if (parse_block()) 
							{
								return true;
							} else 
							{
								return false;
							}
						} else 
						{
							return false;
						}
					} else 
					{
						expected = new string ("')'");
						parse_error (expected, word);
						delete expected;
						delete word;
						return false;
					}
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("'('");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			expected = new string ("identifier");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else 
	{
		expected = new string ("procedure");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_arg_list() 
{
	// ARG_LIST -> IDENTIFIER_LIST : STANDARD_TYPE ARG_LIST_HAT 
	// Predict {identifier}
	if (word->get_token_type == TOKEN_ID) 
	{
		if (parse_identifier_list()) 
		{
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COLON)
			{
				delete word;
				word = lex->next_token();

				if (parse_standard_type()) 
				{
					if (parse_arg_list_hat()) 
					{
						return true;
					} else 
					{
						return false;
					}
				} else
				{
					return false;
				}
			} else
			{
				expected = new string ("':'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;	
			}
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
	{
		return true;
	} else 
	{	
		expected = new string ("identifier or )");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_arg_list_hat() 
{
	// ARG_LIST_HAT -> ; ARG_LIST
	// Predict {;} 
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) 
	{
		delete word;
		word = lex->next_token();

		if (parse_arg_list()) 
		{
			retur true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE)
	{
		return true;
	} else
	{
		expected = new string ("';' or ')'");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_identifier_list() 
{
	if (word->get_token_type() == TOKEN_ID ) 
	{
		delete word;
		word = lex->next_token();
		if (parse_identifier_list_prm()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("identifier");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_identifier_list_prm()
{
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COMMA) 
	{
		delete word;
		word = lex->next_token();

		if (word->get_token_type() == TOKEN_ID) 
		{
			delete word;
			word = lex->next_token();

			if (parse_identifier_list_prm()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else
		{
			expected = new string ("identifier");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI)
	{
		return true;
	} else 
	{
		expected = new string ("',' or ':'");
		parse_error	(expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_standard_type() 
{
	if ((word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_INT)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BOOL)) 
	{
		return true;
	} else 
	{
		expected = new string ("int or bool");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_block()
{
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN) 
	{
		delete word;
		word = lex->next_token();
		if (parse_stmt_list()) 
		{
			if (word->get_token_type == TOKEN_KEYWORD
				&& static_cast<KeywordToken *>(word)->get_attribute() == KW_END) 
			{
				delete word;
				word = lex->next_token();
				return true;
			} else 
			{
				expected = new string ("end");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else
		{
			return false;
		}
	} else 
	{
		expected = new string ("begin");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_stmt_list() 
{
	if ( (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_IF)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_WHILE)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PRINT)
		|| (word->get_token_type() == TOKEN_ID))
	{
		if (parse_stmt()) 
		{
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) 
			{
				if (parse_stmt_list_prm()) 
				{
					return true;
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("';'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("if, while, print or identifier");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_stmt_list_prm() 
{
	if ( (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_IF)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_WHILE)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PRINT)
		|| (word->get_token_type() == TOKEN_ID))
	{
		if (parse_stmt()) 
		{
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) 
			{
				if (parse_stmt_list_prm()) 
				{
					return true;
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("';'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_KEYWORD
				&& static_cast<KeywordToken *>(word)->get_attribute() == KW_END)
	{
		return true;
	} else 
	{
		expected = new string ("if, while, print or identifier or end");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_stmt() 
{
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_IF) 
	{
		if (parse_if_stmt() 
		{
			return true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken* >(word)->get_attribute() == KW_WHILE) 
	{
		if (parse_while_stmt()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PRINT) 
	{
		if (parse_print_stmt()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_ID) 
	{
		delete word;
		word = lex->next_token();

		if (parse_stmt_ass_proc_tail()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("if, while, print or identifier");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_stmt_ass_proc_tail() 
{
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_ASSIGN) 
	{
		if (parse_assignment_stmt_tail()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN) 
	{
		if (parse_procedure_call_stmt_tail()) 
		{
			return true; 
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string (":= or (");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_assignment_stmt_tail()
{
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_ASSIGN) 
	{
		delete word;
		word = lex->next_token();

		if (parse_expr()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string (":=");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_if_stmt() 
{
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_IF) 
	{
		delete word;
		word = lex->next_token();

		if (parse_expr()) 
		{
			if (word-.get_token_type() == TOKEN_KEYWORD
				&& static_cast<KeywordToken* >(word)->get_attribute() == KW_THEN) 
			{
				delete word;
				word = lex->next_token();
				if (parse_block()) 
				{
					if (parse_if_stmt_hat()) 
					{
						return true;
					} else 
					{
						return false;
					}
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("then");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("if");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_if_stmt_hat() 
{
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_ELSE)
	{
		delete word;
		word = lex->next_token();

		if (parse_block()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC 
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) 
	{
		return true;
	} else 
	{
		expected = new string ("else or ';'");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_while_stmt() 
{
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_WHILE) 
	{
		delete word;
		word = lex->next_token();
		if (parse_expr()) 
		{
			if (parse_block()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("while");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_print_stmt() 
{
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PRINT) 
	{
		delete word;
		word = lex->next_token();
		if (parse_expr()) 
		{
			return true; 
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("print");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_procedure_call_stmt_tail() 
{
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN) 
	{
		delete word;
		word = lex->next_token();
		if (parse_expr_list()) 
		{
			if (word->get_token_type() == TOKEN_PUNC 
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
			{
				return true;
			} else 
			{
				expected = new string ("')'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("(");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
	}
	return false;
}

bool Pareser::parse_expr_list() 
{
	if (word->get_token_type() == TOKEN_ID
		|| (word->get_token_type() == TOKEN_NUM)
		|| (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_NOT))
	{
		if (parse_expr()) 
		{
			if (parse_expr_list_hat()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
	{
		return true;
	} else 
	{
		expected = new string ("identifier or num or ( or + or - or not or )");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_expr_list_hat() 
{
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COMMA) 
	{
		delete word;
		word = lex->next_token();

		if (parse_expr_list()) 
		{
			return true;
		} else 
		{
			return false;
		}
	} else if (word->get_token_type() = TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
	{
		return true;
	} else 
	{
		expected = new string ("',' or ')'");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_expr() 
{
	if (word->get_token_type() == TOKEN_ID
		|| (word->get_token_type() == TOKEN_NUM)
		|| (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_NOT))
	{
		if (parse_simeple_expr()) 
		{
			if (expr_hat()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("identifier or num or ( or + or - or not or )");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_expr_hat() 
{
	if (word->get_token_type() == TOKEN_RELOP)
	{
		delete word;
		word = lex->next_token();
		if (parse_simple_expr()) 
		{
			return false;
		} else
		{
			return false;
		}
	} else if ((word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI)
	|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_THEN)
	|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)
	|| (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COMMA)) 
	{
		return true;
	} else 
	{
		expected = new string ("relational operator");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_simple_expr() 
{
	if (word->get_token_type() == TOKEN_ID
		|| (word->get_token_type() == TOKEN_NUM)
		|| (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_NOT))
	{
		if (parse_term()) 
		{
			if (parse_simple_expr_prm()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("identifier or num or ( or + or - or not or )");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;	
	}
}

bool Parser::parse_simple_expr_prm() 
{
	if (word->get_token_type() == TOKEN_ADDOP) 
	{
		delete word;
		word = lex->next_token();
		if (parse_term()) 
		{
			if (parse_simple_expr_prm()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else if ((word->get_token_type() == TOKEN_RELOP)
	|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_THEN)
	|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)
	|| (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COMMA))
	{
		return true;
	} else 
	{
		expected = new string ("addop token or relop token or then or begin or ,");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_term() 
{
	if (word->get_token_type() == TOKEN_ID
		|| (word->get_token_type() == TOKEN_NUM)
		|| (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB)
		|| (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_NOT))
	{
		if (parse_factor()) 
		{
			if (parse_term_prm()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else {
		expected = new string ("identifier or num or ( or + or - or not or )");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;	
	}
	return false;
}

bool Parser::parse_term_prm() 
{
	if (word->get_token_type() == TOKEN_MULOP) 
	{
		delete word;
		word = lex->next_token()
		if (parse_factor()) 
		{
			if (parse_term_prm()) {
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else if ((word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI)
	|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_THEN)
	|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)
	|| (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COMMA)
	|| (word->get_token_type() == TOKEN_RELOP)
	|| (word->get_token_type() == TOKEN_ADDOP)) 
	{
		return true;
	} else 
	{
		expected = new string ("mulop or relop or addop or ; or then or begin or comma");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_factor()
{
	if (word->get_token_type() == TOKEN_ID) 
	{
		delete word;
		word = lex->next_token();
		return true;
	} else if (word->get_token_type() == TOKEN_NUM) 
	{		
		delete word;
		word = lex->next_token();
		return true;
	} else if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN) 
	{
		if (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN)
		{
			delete word;
			word = lex->next_token();
			if (parse_expr()) 
			{
				if (word->get_token_type() == TOKEN_PUNC
					&& static_cast<PuncToken*>(word)->get_attribute() == PUNC_CLOSE) 
				{
					return true;
				} else 
				{
					expected = new string (")");
					parse_error (expected, word);
					delete expected;
					delete word;
					return false;
				}
			} else 
			{	
				return false;
			}
		} else 
		{
			expected = new string ("(");
			parse_error (expected, word);
			delete expected;
			delete wor;
			return false;
		}
	} else if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_NOT) 
	{
		if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_NOT) 
		{
			delete word;
			word = lex->next_token();

			if (parse_factor()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			expected = new string ("not");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else if ((word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD)
		|| (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB))
	{
		if (parse_sign()) 
		{
			if (parse_factor()) 
			{
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("identifier or num or ( or not or +")
		return false;
	}
	return false;
}

bool Parser::parse_sign() 
{
	if ((word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD))
	{
		delete word;
		word = lex->next_token();
		return true;
	} else if(word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB))
	{
		delete word;
		word = lex->next_token();
		return true;
	} else 
	{	
		expected = new string (" + or -");
		delete expected;
		delete word;
		return false;
	}
	return false;
}