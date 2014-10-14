#include "scanner.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) 
{
	Scanner *scanner = new Scanner(argv[1]);
	Token *eof_token = new EofToken();

	cout << endl;
	Token *scanner_token = scanner -> next_token();
	
	while( *scanner_token -> to_string() != *eof_token -> to_string()) 
	{
		switch (scanner_token -> get_token_type())
	 	{
	 		case TOKEN_KEYWORD:{
				KeywordToken *token_keyword = static_cast<KeywordToken*>(scanner_token);
				cout << "Token attribute: " << *token_keyword -> to_string() << endl;
	 			break;}
	 		case TOKEN_PUNC:{
	 			PuncToken *token_punc = static_cast<PuncToken*>(scanner_token); 	
				cout << "Token attribute: " << *token_punc -> to_string() << endl;
				break;}
	 		case TOKEN_RELOP:{
	 			RelopToken *token_relop = static_cast<RelopToken*>(scanner_token);
				cout << "Token attribute: " << *token_relop -> to_string() << endl;
	 			break;}
	 		case TOKEN_ADDOP:{
	 			AddopToken *token_addop = static_cast<AddopToken*>(scanner_token);
				cout << "Token attribute: " << *token_addop -> to_string() << endl;
	 			break;}
	 		case TOKEN_MULOP:{
	 			MulopToken *token_mulop = static_cast<MulopToken*>(scanner_token);
				cout << "Token attribute: " << *token_mulop -> to_string() << endl;
	 			break;}
	 		case TOKEN_ID:{
	 			IdToken *token_id = static_cast<IdToken*>(scanner_token);
				cout << "Token attribute: " << *token_id -> to_string() << endl;
	  			break;}
	 		case TOKEN_NUM:{
	 			NumToken *token_num = static_cast<NumToken*>(scanner_token);
				cout << "Token attribute: " << *token_num -> to_string() << endl;
	 			break;}
	 	 	case TOKEN_NO_TYPE:{
	 	 		break;
	 	 	}
	 	 	case TOKEN_EOF: {
	 	 		EofToken *token_eof = static_cast<EofToken*>(scanner_token);
	 	 		cout << "Token attribute: " << *token_eof -> to_string() << endl;
	 	 		break;}
	 	 }
	}
	scanner_token = scanner -> next_token();
	scanner_token = scanner -> next_token();
	EofToken *token_eof = static_cast<EofToken*>(scanner_token);
	cout << "Token attribute: " << *token_eof -> to_string() << endl;
}


