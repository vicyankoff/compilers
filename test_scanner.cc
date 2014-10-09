#include "scanner.h"
#include <iostream>
using namespace std;

string * get_string_token_type(int id) 
{
	string * token;
	switch(id){
		case 0: {	token = new string ("TOKEN_KEYWORD");break;	}
		case 1: { token = new string ("TOKEN_PUNC");break; }
		case 2: {	token = new string ("TOKEN_RELOP");break; }
		case 3: {	token = new string ("TOKEN_ADDOP");break; }
		case 4: { token = new string ("TOKEN_MULOP");break;	}
		case 5: {	token = new string ("TOKEN_ID");break;	}
		case 6: { token = new string ("TOKEN_NUM");break; }
		case 7: { token = new string ("TOKEN_EOF");break; }
		case 99: { token = new string ("TOKEN_NO_TYPE");break; }
		
	}
	return token;
}


int main(int argc, char *argv[]) 
{
	Scanner *scanner = new Scanner(argv[1]);
	Token *eof_token = new EofToken();

	cout << endl;
	Token *scanner_token = scanner -> next_token();
	
	while( *scanner_token -> to_string() != *eof_token -> to_string()) {
	 switch (scanner_token -> get_token_type())
	 {
  	case TOKEN_KEYWORD:{
			KeywordToken *token_keyword = static_cast<KeywordToken*>(scanner_token);
			cout << "Token attribute: " << *token_keyword -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_keyword -> get_token_type()) << endl << endl;
	 		break;}
	 	case TOKEN_PUNC:{
	 		PuncToken *token_punc = static_cast<PuncToken*>(scanner_token); 	
			cout << "Token attribute: " << *token_punc -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_punc -> get_token_type()) << endl << endl;
			break;}
	 	case TOKEN_RELOP:{
	 		RelopToken *token_relop = static_cast<RelopToken*>(scanner_token);
			cout << "Token attribute: " << *token_relop -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_relop -> get_token_type()) << endl << endl;
	 		break;}
	 	case TOKEN_ADDOP:{
	 		AddopToken *token_addop = static_cast<AddopToken*>(scanner_token);
			cout << "Token attribute: " << *token_addop -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_addop -> get_token_type()) << endl << endl;
	 		break;}
	 	case TOKEN_MULOP:{
	 		MulopToken *token_mulop = static_cast<MulopToken*>(scanner_token);
			cout << "Token attribute: " << *token_mulop -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_mulop -> get_token_type()) << endl << endl;
	 		break;}
	 	case TOKEN_ID:{
	 		IdToken *token_id = static_cast<IdToken*>(scanner_token);
			cout << "Token attribute: " << *token_id -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_id -> get_token_type()) << endl << endl;
	  	break;}
	 	case TOKEN_NUM:{
	 		NumToken *token_num = static_cast<NumToken*>(scanner_token);
			cout << "Token attribute: " << *token_num -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_num -> get_token_type()) << endl << endl;
	 		break;}
	 	 }
			scanner_token = scanner -> next_token();
	}

	 		scanner_token = scanner -> next_token();
	 		EofToken *token_eof = static_cast<EofToken*>(scanner_token);
			cout << "Token attribute: " << *token_eof -> to_string() << endl;
	 		cout << "Token type: " << *get_string_token_type(token_eof -> get_token_type()) << endl << endl;
}


