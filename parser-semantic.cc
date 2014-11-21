#include "parser-semantic.h"

Parser::Parser(Scanner *s) 
{
	lex = s;
	
	// Init the word variable
	word = lex->next_token();

	// Create the symbol table
	stab = new Symbol_Table();

	// Init the environments to null
	current_env = NULL;
	main_env = NULL;
	proc_call_env = NULL;
	parm_pos = -1;
}

Parser::~Parser() 
{
	if (lex != NULL) {
		delete lex;
	}
	if (word != NULL) {
		delete word;
	}	
}

void Parser::parse_error(string * expected, Token * found) 
{
	cout << "Expected: " << *expected << endl;
	cout << "Found: ";
	switch (found -> get_token_type())
	 	{
  			case TOKEN_KEYWORD:{
				KeywordToken *token_keyword = static_cast<KeywordToken*>(found);
				cout << *token_keyword -> to_string() << endl;
	 			break;}
	 		case TOKEN_PUNC:{
	 			PuncToken *token_punc = static_cast<PuncToken*>(found); 	
				cout << *token_punc -> to_string() << endl;
				break;}
	 		case TOKEN_RELOP:{
	 			RelopToken *token_relop = static_cast<RelopToken*>(found);
				cout << *token_relop -> to_string() << endl;
	 			break;}
	 		case TOKEN_ADDOP:{
	 			AddopToken *token_addop = static_cast<AddopToken*>(found);
				cout << *token_addop -> to_string() << endl;
	 			break;}
	 		case TOKEN_MULOP:{
	 			MulopToken *token_mulop = static_cast<MulopToken*>(found);
				cout << *token_mulop -> to_string() << endl;
	 			break;}
	 		case TOKEN_ID:{
	 			IdToken *token_id = static_cast<IdToken*>(found);
				cout << *token_id -> to_string() << endl;
	  			break;}
	 		case TOKEN_NUM:{
	 			NumToken *token_num = static_cast<NumToken*>(found);
				cout << *token_num -> to_string() << endl;
	 			break;}
	 		case TOKEN_NO_TYPE: {
	 			break;
	 		}
	 		case TOKEN_EOF:{
	 	 		EofToken *token_eof = static_cast<EofToken*>(found);
				cout << *token_eof -> to_string() << endl;
				break;}
		}
}

void Parser::type_error(Token *where, string * message)
{
		cout << "Type error occured in: ";
		switch (where -> get_token_type())
	 	{
  			case TOKEN_KEYWORD:{
				KeywordToken *token_keyword = static_cast<KeywordToken*>(where);
				cout << *token_keyword -> to_string() << endl;
	 			break;}
	 		case TOKEN_PUNC:{
	 			PuncToken *token_punc = static_cast<PuncToken*>(where); 	
				cout << *token_punc -> to_string() << endl;
				break;}
	 		case TOKEN_RELOP:{
	 			RelopToken *token_relop = static_cast<RelopToken*>(where);
				cout << *token_relop -> to_string() << endl;
	 			break;}
	 		case TOKEN_ADDOP:{
	 			AddopToken *token_addop = static_cast<AddopToken*>(where);
				cout << *token_addop -> to_string() << endl;
	 			break;}
	 		case TOKEN_MULOP:{
	 			MulopToken *token_mulop = static_cast<MulopToken*>(where);
				cout << *token_mulop -> to_string() << endl;
	 			break;}
	 		case TOKEN_ID:{
	 			IdToken *token_id = static_cast<IdToken*>(where);
				cout << *token_id -> to_string() << endl;
	  			break;}
	 		case TOKEN_NUM:{
	 			NumToken *token_num = static_cast<NumToken*>(where);
				cout << *token_num -> to_string() << endl;
	 			break;}
	 		case TOKEN_NO_TYPE: {
	 			break;
	 		}
	 		case TOKEN_EOF:{
	 	 		EofToken *token_eof = static_cast<EofToken*>(where);
				cout << *token_eof -> to_string() << endl;
				break;}
		}
		cout << *message << endl;
	exit(-1);
}

void Parser::undeclared_id_error(string *id, string *proc_env, string *main_env, string * function_call)
{
		cout << "Undeclared error occurs with id: " << *id <<endl;
		cout << "Current environment: " << *proc_env << endl;
		cout << "Main environment: " << *main_env << endl;
		cout << "Function called: " << *function_call << endl;
		exit(-1);
}

void Parser::variable_already_declared_error( string * variable)
{
	cout << "Variable Already Declared Error: the variable '" << *variable << "' has already been declared" << endl;
	exit (-1);
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
			string * external_env = new string ("_EXTERNAL");
			stab->install (static_cast<IdToken *>(word)->get_attribute(), 
			external_env, PROGRAM_T);
			current_env = static_cast<IdToken *>(word)->get_attribute();
			main_env = static_cast<IdToken *>(word)->get_attribute();

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
							expected = new string ("';'...Failed to parse in parse_program()");
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
				expected = new string ("';'...Failed to parse in parse_program()");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{ // Failed to match an identifier			
			expected = new string ("identifier...Failed to parse in parse_program()");
			parse_error(expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else 
	{ // Failed to match the keyword program
		expected = new string ("program...Failed to parse in parse_program()");
		parse_error(expected, word);
		delete expected;
		delete word;
		return false;
	}
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
		expected = new string ("identifier, keyword \"begin\" or keyword \"procedure\"...Failed to parse in parse_decl_list()");
		parse_error (expected, word);
    	delete expected;
    	delete word;
		return false;
	}
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
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) 
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
				expected = new string ("';'...Failed to parse in parse_variable_decl_list()");
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
				|| (word->get_token_type() == TOKEN_KEYWORD
					&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)) 
	{
		return true;
	} else 
	{
		expected = new string ("identifier or procedure or begin...Failed to parse in parse_variable_decl_list()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_variable_decl()
{

	expr_type standard_type_type;
	// VARIABLE_DECL -> IDENTIFIER_LIST : STANDARD_TYPE
	// Predict {identifier}
	if (word->get_token_type() == TOKEN_ID) 
	{
		// Match IDENTIFIER_LIST
		if (parse_identifier_list()) 
		{

			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COLON) 
			{
				delete word;
				word = lex->next_token();
		
				if (parse_standard_type(standard_type_type)) {

					stab->update_type (standard_type_type);
					return true;
				} else 
				{ // Failed to match STANDARD_TYPE
					return false;
				}
			} else 
			{
				expected = new string ("':'...Failed to parse in parse_variable_decl_()");
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
		expected = new string ("identifier...Failed to parse in parse_variable_decl_()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_procedure_decl_list() 
{
	// procedure_decl_list -> procedure_decl ; procedure_decl_list
	// Predict = {procedure}
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROCEDURE) 
	{

		if (parse_procedure_decl()) 
		{
			
			if (word->get_token_type() == TOKEN_PUNC 
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
				expected = new string ("';'...Failed to parse in parse_proceure_decl_list");
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
			 	&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN) 
	{
		return true;
	} else 
	{
		expected = new string ("procedure or begin...Failed to parse in parse_proceure_decl_list");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_procedure_decl()
{
	// PROCEDURE_DECL -> procedure identifier ( ARG_LIST ) VARIABLE_DECL_LIST BLOCK
	// Predict {procedure}

	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROCEDURE) 
	{
		delete word;
		word = lex->next_token();

		if (word->get_token_type() == TOKEN_ID) 
		{

			if ( stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(),current_env))
			{
				variable_already_declared_error (static_cast<IdToken *>(word)->get_attribute());
			} else 
			{
				stab->install (static_cast<IdToken *>(word)->get_attribute(),current_env, PROCEDURE_T);
				current_env = static_cast<IdToken *>(word)->get_attribute();
				parm_pos = 0;
			}

			delete word;
			word = lex->next_token();
			
			if (word->get_token_type() == TOKEN_PUNC 
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
								current_env = main_env;
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
						expected = new string ("')'...Failed to parse in parse_procedure_decl()");
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
				expected = new string ("'('...Failed to parse in parse_procedure_decl()");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else 
		{
			expected = new string ("identifier...Failed to parse in parse_procedure_decl()");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else 
	{
		expected = new string ("procedure...Failed to parse in parse_procedure_decl()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_arg_list() 
{
	expr_type standard_type_type;
	// ARG_LIST -> IDENTIFIER_LIST : STANDARD_TYPE ARG_LIST_HAT 
	// Predict {identifier}
	if (word->get_token_type() == TOKEN_ID) 
	{
		if (parse_identifier_list()) 
		{
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COLON)
			{
				delete word;
				word = lex->next_token();

				if (parse_standard_type(standard_type_type)) 
				{
					stab -> update_arg_list( parm_pos, standard_type_type);

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
				expected = new string ("':'...Failed to parse in parse_arg_list()");
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
		expected = new string ("identifier or )...Failed to parse in parse_arg_list()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
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
			return true;
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
		expected = new string ("';' or ')'...Failed to parse in parse_arg_list_hat()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_identifier_list() 
{
	// IDENTIFIER_LIST -> identifier IDENTIFIER_LIST_PRM
	// Predict(identifier) = {identifier}

	if (word->get_token_type() == TOKEN_ID ) 
	{
		if ( !stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(), current_env))
		{
			stab->install (static_cast<IdToken *>(word)->get_attribute(), current_env, UNKNOWN_T);
		} else 
		{
			variable_already_declared_error( static_cast<IdToken *>(word)->get_attribute());
		}

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
		expected = new string ("identifier...Failed to parse in parse_identifier_list()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
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
			if ( !stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(), current_env))
			{
				stab -> install (static_cast<IdToken *>(word)->get_attribute(),
				current_env, UNKNOWN_T);
			} else 
			{
				variable_already_declared_error(static_cast<IdToken *>(word)->get_attribute());
			}
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
			expected = new string ("identifier...Failed to parse in parse_identifier_list_prm()");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COLON)
	{
		return true;
	} else 
	{
		expected = new string ("',' or ':'...Failed to parse in parse_identifier_list_prm()");
		parse_error	(expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_standard_type(expr_type &standard_type_type) 
{
	if (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_INT) 
	{
		standard_type_type = INT_T;
		delete word;
		word = lex->next_token();
		return true;
	} else if (word->get_token_type() == TOKEN_KEYWORD
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BOOL)
	{
		standard_type_type = BOOL_T;
		delete word;
		word = lex->next_token();
		return true;
	} else 
	{
		expected = new string ("int or bool...Failed to parse in parse_standard_type()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
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
			if (word->get_token_type() == TOKEN_KEYWORD
				&& static_cast<KeywordToken *>(word)->get_attribute() == KW_END) 
			{
				delete word;
				word = lex->next_token();
				return true;
			} else 
			{
				expected = new string ("end...Failed to parse in parse_block()");
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
		expected = new string ("begin...Failed to parse in parse_block()");
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
				delete word;
				word = lex->next_token();
				if (parse_stmt_list_prm()) 
				{
					return true;
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("';'...Failed to parse in parse_stmt_list()");
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
		expected = new string ("if, while, print or identifier...Failed to parse in parse_stmt_list()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
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
				delete word;
				word = lex->next_token();
				if (parse_stmt_list_prm()) 
				{
					return true;
				} else 
				{
					return false;
				}
			} else 
			{
				expected = new string ("';'...Failed to parse in parse_stmt_list_prm()");
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
		expected = new string ("if, while, print or identifier or end...Failed to parse in parse_stmt_list_prm()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_stmt() 
{
	expr_type stmt_ass_proc_tail_type;

	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_IF) 
	{
		if (parse_if_stmt())
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
		string *identifier = static_cast<IdToken *>(word)->get_attribute();
		proc_call_env = static_cast<IdToken *>(word)->get_attribute();
		if (!stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(),
			current_env) && !stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(),
			main_env))
			{
				undeclared_id_error (static_cast<IdToken *>(word)->get_attribute(),
				current_env, main_env, new string ("parse_stmt()") );
			}
		delete word;
		word = lex->next_token();

		if (parse_stmt_ass_proc_tail(stmt_ass_proc_tail_type)) 
		{
			if ( stab -> get_type (identifier, current_env) != stmt_ass_proc_tail_type)
			{
				type_error(word, new string ("Incompatible types in assignment. Method: parse_stmt()"));
			}
			return true;
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("if, while, print or identifier...Failed to parse in parse_stmt()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_stmt_ass_proc_tail(expr_type &stmt_ass_proc_tail_type) 
{
	expr_type assignment_stmt_tail_type;
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_ASSIGN) 
	{
		if (parse_assignment_stmt_tail(assignment_stmt_tail_type)) 
		{
			stmt_ass_proc_tail_type = assignment_stmt_tail_type;
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
			stmt_ass_proc_tail_type = PROCEDURE_T;
			return true; 
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string (":= or (...Failed to parse in parse_stmt_ass_proc_tail()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_assignment_stmt_tail(expr_type &assignment_stmt_tail_type)
{
	expr_type the_expr_type;
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_ASSIGN) 
	{
		delete word;
		word = lex->next_token();

		if (parse_expr(the_expr_type)) 
		{
			assignment_stmt_tail_type = the_expr_type;
			return true;
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string (":=...Failed to parse in parse_assignment_stmt_tail()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_if_stmt() 
{
	expr_type the_expr_type;
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_IF) 
	{
		delete word;
		word = lex->next_token();

		if (parse_expr(the_expr_type)) 
		{
			if (the_expr_type != BOOL_T)
			{
				type_error(word, new string ("Expression in IF statement must be bool"));
			}
			if (word->get_token_type() == TOKEN_KEYWORD
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
				expected = new string ("then...Failed to parse in parse_if_stmt()");
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
		expected = new string ("if...Failed to parse in parse_if_stmt()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
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
		expected = new string ("else or ';'...Failed to parse in parse_if_stmt_hat()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
	return false;
}

bool Parser::parse_while_stmt() 
{
	expr_type the_expr_type;
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_WHILE) 
	{
		delete word;
		word = lex->next_token();
		if (parse_expr(the_expr_type)) 
		{
			if (the_expr_type != BOOL_T)
			{
				type_error (word, new string ("Expression in WHILE statement must be a bool"));
			}
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
		expected = new string ("while...Failed to parse in parse_while_stmt()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_print_stmt() 
{
	expr_type the_expr_type;
	if (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PRINT) 
	{
		delete word;
		word = lex->next_token();
		if (parse_expr(the_expr_type)) 
		{
			if (the_expr_type != INT_T)
			{
				type_error (word, new string ("You can only print integer variables"));
			}
			return true; 
		} else 
		{
			return false;
		}
	} else 
	{
		expected = new string ("print...Failed to parse in parse_print_stmt()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_procedure_call_stmt_tail() 
{
	if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_OPEN) 
	{
		delete word;
		word = lex->next_token();
		parm_pos = 0;
		if (parse_expr_list()) 
		{
			if (word->get_token_type() == TOKEN_PUNC 
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
			{
				delete word;
				word = lex->next_token();
				return true;
			} else 
			{
				expected = new string ("')'...Failed to parse in parse_procedure_call_stmt_tail()");
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
		expected = new string ("(...Failed to parse in parse_procedure_call_stmt_tail()");
			parse_error (expected, word);
			delete expected;
			delete word;
			return false;
	}
}

bool Parser::parse_expr_list() 
{
	expr_type the_expr_type;

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
		if (parse_expr(the_expr_type)) 
		{
			if (the_expr_type != stab -> get_type (proc_call_env, parm_pos))
			{
				type_error (word, new string ("Incompatible types in expression. Method: parse_expr_list()"));
				cout << "Position: " << parm_pos << endl;
			}
			parm_pos++;

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
		expected = new string ("identifier or num or ( or + or - or not or )...Failed to parse in parse_expr_list()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
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
	} else if (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE) 
	{
		return true;
	} else 
	{
		expected = new string ("',' or ')'...Failed to parse in parse_expr_list_hat()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_expr(expr_type &the_expr_type) 
{
	expr_type simple_expr_type, expr_hat_type;
		
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
		if (parse_simple_expr(simple_expr_type)) 
		{
			if (parse_expr_hat(expr_hat_type)) 
			{
				/* semantics actions: calculate expr_type */
				if (expr_hat_type == NO_T) 
				{
					the_expr_type = simple_expr_type;

				} else if (simple_expr_type == INT_T && expr_hat_type == INT_T) 
				{
					the_expr_type = BOOL_T;
				} else 
				{
					type_error(word, new string ("Incompatible types in expression. Method parse_expr()"));
				}

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
		expected = new string ("identifier or num or ( or + or - or not or )...Failed to parse in parse_expr()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_expr_hat(expr_type &expr_hat_type) 
{
	expr_type simple_expr_type;
	if (word->get_token_type() == TOKEN_RELOP)
	{
		delete word;
		word = lex->next_token();
		if (parse_simple_expr(simple_expr_type)) 
		{
			if (simple_expr_type == INT_T)
			{
				expr_hat_type = INT_T;
			} else 
			{
				type_error (word, new string ("Incompatible types in expression. Method: parse_expr_hat()"));
			}

			return true;
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
	|| (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE)) 
	{
		expr_hat_type = NO_T;
		return true;
	} else 
	{
		expected = new string ("relational operator...Failed to parse in parse_expr_hat()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_simple_expr(expr_type &simple_expr_type) 
{
	expr_type term_type;
	expr_type simple_expr_prm_type;

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
		if (parse_term(term_type)) 
		{
			if (parse_simple_expr_prm(simple_expr_prm_type)) 
			{
				if (simple_expr_prm_type == NO_T)
				{
					simple_expr_type = term_type;
				} else if (term_type == simple_expr_prm_type)
				{
					simple_expr_type = term_type;
				} else 
				{
					type_error (word, new string ("Incompatible types in expression. Method: parse_simple_expr()"));
				}
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
		expected = new string ("identifier or num or ( or + or - or not or )...Failed to parse in parse_simple_expr()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;	
	}
}

bool Parser::parse_simple_expr_prm(expr_type &simple_expr_prm_type) 
{
	expr_type term_type;
	expr_type simple_expr_prm_type_two;
	expr_type addop_type;

	if (word->get_token_type() == TOKEN_ADDOP) 
	{
		if (static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD
			|| static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB)
		{
			addop_type = INT_T;
		} else if (static_cast<AddopToken *>(word)->get_attribute() == ADDOP_OR)
		{
			addop_type = BOOL_T;
		}
		delete word;
		word = lex->next_token();
		if (parse_term(term_type)) 
		{
			if (parse_simple_expr_prm(simple_expr_prm_type_two)) 
			{
				if (simple_expr_prm_type_two == NO_T)
				{
					if (addop_type == term_type) 
					{
						simple_expr_prm_type = addop_type;
					} else
					{
						type_error (word, new string ("Incompatible types in expression"));
					}
				} else if (addop_type == term_type
					&& term_type == simple_expr_prm_type_two)
				{
					simple_expr_prm_type = addop_type;
				} else
				{
					type_error (word, new string ("Incompatible types in expression"));
				}
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
		|| (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI)
		|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_THEN)
		|| (word->get_token_type() == TOKEN_KEYWORD
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)
		|| (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_COMMA)
		|| (word->get_token_type() == TOKEN_PUNC
			&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE))
	{
		simple_expr_prm_type = NO_T;
		return true;
	} else 
	{
		expected = new string ("addop token or relop token or then or begin or ,...Failed to parse in parse_simple_expr_prm()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_term(expr_type &term_type) 
{
	expr_type factor_type;
	expr_type term_prm_type;

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
		if (parse_factor(factor_type)) 
		{
			if (parse_term_prm(term_prm_type)) 
			{
				if (term_prm_type == NO_T)
				{
					term_type = factor_type;
				} else if (factor_type == term_prm_type)
				{
					term_type = factor_type;
				} else 
				{
					type_error (word, new string ("Incompatible types in expression"));
				}

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
		expected = new string ("identifier or num or ( or + or - or not or )...Failed to parse in parse_term()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;	
	}
}

bool Parser::parse_term_prm(expr_type &term_prm_type) 
{
	expr_type factor_type;
	expr_type term_prm_type_two;
	expr_type mulop_type;

	if (word->get_token_type() == TOKEN_MULOP) 
	{
		if (static_cast<MulopToken *>(word)->get_attribute() == MULOP_MUL
			|| static_cast<MulopToken *>(word)->get_attribute() == MULOP_DIV)
		{
			mulop_type = INT_T;
		} else if (static_cast<MulopToken *>(word)->get_attribute() == MULOP_AND)
		{
			mulop_type = BOOL_T;
		} 
		delete word;
		word = lex->next_token();
		if (parse_factor(factor_type)) 
		{
			if (parse_term_prm(term_prm_type_two)) {

				if (term_prm_type_two == NO_T && mulop_type == factor_type)
				{
					term_prm_type = mulop_type;
				} else if (mulop_type == factor_type && factor_type == term_prm_type_two)
				{
					term_prm_type = mulop_type;
				} else 
				{
					type_error (word, new string ("Incompatible types in expression"));
				}

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
	|| (word->get_token_type() == TOKEN_ADDOP)
	|| (word->get_token_type() == TOKEN_PUNC
		&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_CLOSE)) 
	{
		term_prm_type = NO_T;
		return true;
	} else 
	{
		expected = new string ("mulop or relop or addop or ; or then or begin or comma...Failed to parse in parse_term_prm()");
		parse_error (expected, word);
		delete expected;
		delete word;
		return false;
	}
}

bool Parser::parse_factor(expr_type &factor_type)
{
	expr_type the_expr_type;
	expr_type factor_type_two;
	if (word->get_token_type() == TOKEN_ID) 
	{
		if (stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(), current_env))
		{
			factor_type = stab -> get_type (static_cast<IdToken *>(word)->get_attribute(), current_env);
		} else if (stab -> is_decl (static_cast<IdToken *>(word)->get_attribute(), main_env))
		{
			factor_type = stab -> get_type (static_cast<IdToken *>(word)->get_attribute(), main_env);

		} else 
		{
			undeclared_id_error (static_cast<IdToken *>(word)->get_attribute(), current_env, main_env, new string ("parse_factor()"));
		}
		delete word;
		word = lex->next_token();
		return true;

	} else if (word->get_token_type() == TOKEN_NUM) 
	{	
		factor_type = INT_T;
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

			if (parse_expr(the_expr_type)) 
			{
				if (word->get_token_type() == TOKEN_PUNC
					&& static_cast<PuncToken*>(word)->get_attribute() == PUNC_CLOSE) 
				{
					factor_type = the_expr_type;
					delete word;
					word = lex->next_token();
					return true;
				} else 
				{
					expected = new string (")...Failed to parse in parse_factor()");
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
			expected = new string ("(...Failed to parse in parse_factor()");
			parse_error (expected, word);
			delete expected;
			delete word;
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

			if (parse_factor(factor_type_two)) 
			{
				if (factor_type_two == BOOL_T)
				{
					factor_type = BOOL_T;
				} else 
				{
					type_error (word, new string ("Incompatible types in expression"));
				}
				return true;
			} else 
			{
				return false;
			}
		} else 
		{
			expected = new string ("not...Failed to parse in parse_factor()");
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
			if (parse_factor(factor_type_two)) 
			{
				if (factor_type_two == INT_T)
				{
					factor_type = INT_T;
				} else 
				{
					type_error (word, new string ("Incompatible types in expression"));
				}
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
		expected = new string ("identifier or num or ( or not or +...Failed to parse in parse_factor()");
		return false;
	}
}

bool Parser::parse_sign() 
{
	if (word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_ADD)
	{
		delete word;
		word = lex->next_token();
		return true;
	} else if(word->get_token_type() == TOKEN_ADDOP
			&& static_cast<AddopToken *>(word)->get_attribute() == ADDOP_SUB)
	{
		delete word;
		word = lex->next_token();
		return true;
	} else 
	{	
		expected = new string (" + or -...Failed to parse in parse_sign()");
		delete expected;
		delete word;
		return false;
	}
}
