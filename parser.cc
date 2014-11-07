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
		&& static_cast<KeywordToken *>(word)->get_attribute() == KW_PROGRAM) {
		/* Advance - Notice that we only delete a token on an ADVANCE, and, if we
		ADVANCE, it is the ADVANCE code that is responsible for getting the next token.
		*/
		delete word;
		word = lex->next_token();

		// Match identifier
		if (word->get_token_type() == TOKEN_ID) {
			// ADVANCE
			delete word;
			word = lex->next_token();	

			// Match ;
			if (word->get_token_type() == TOKEN_PUNC
				&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) {
				// ADVANCE
				delete word;
				word = lex->next_token();

				// Match DECL_LIST
				if( parse_decl_list()) {

					// Match BLOCK - ACTION
					if (parse_block()) {

						// Match ;
						if (word->get_token_type() == TOKEN_PUNC
							&& static_cast<PuncToken *>(word)->get_attribute() == PUNC_SEMI) {

							// ADVANCE
							delete word;
							word = lex->next_token();
							return true;
						} else { // Failed to match the second semicolon
							expected = new string ("';'");
							parse_error (expected, word);
							delete expected;
							delete word;
							return false;
						}
					} else { // Failed to parse BLOCK
						return false;
					}

				} else { // Failed to parse DECL_LIST
					return false;
				}
			} else { // Failed to match the first semicolon
				expected = new string ("';'");
				parse_error (expected, word);
				delete expected;
				delete word;
				return false;
			}
		} else { // Failed to match an identifier			
			expected = new string ("identifier");
			parse_error(expected, word);
			delete expected;
			delete word;
			return false;
		}
	} else { // Failed to match the keyword program
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
			&& static_cast<KeywordToken *>(word)->get_attribute() == KW_BEGIN)) {
		if (parse_variable_decl_list()) {
			if (parse_procedure_decl_list()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		expected = new string ("identifier, keyword \"begin\" or keyword \"procedure\"");
		parse_error (expected, word);
    delete expected;
    delete word;
		return false;
	}
}

bool Parse::parse_variable_decl_list()
{
  // VARIABLE_DECL_LIST -> VARIABLE_DECL ; VARIABLE_DECL_LIST
  // Predict (VARIABLE_DECL_LIST -> VARIABLE_DECL ; VARIABLE_DECL_LIST) = {identifier}
}
