#include "scanner.h"

#define FINAL_STATE 1024

Scanner::Scanner (char *filename)
{
	buffer = new Buffer(filename);
}

Scanner::~Scanner()
{
	if( buffer != NULL) 
	{
		delete buffer;
	}
}

void Scanner::scanner_fatal_error() 
{
	cout << "SCANNER ENCOUNTERED A FATAL ERROR IN STATE: ";
}

Token *Scanner::next_token()
{
	Token *token;
	int state = 0;
	string * attribute = new string("");
	while(state != FINAL_STATE) 
	{
		char c = buffer -> next_char();
		switch(state) 
		{
			case 0:
			if( c == 't') {
				state = 101;
				attribute -> push_back(c);
			} else if (c == 'p') {
				state = 105;
				attribute -> push_back(c);
			} else if (c == 'i') {
				state = 121;
				attribute -> push_back(c);
			} else if (c == 'b') {
				state = 125;
				attribute -> push_back(c);
			} else if (c == 'e') {
				state = 133;
				attribute -> push_back(c);
			} else if (c == 'w') {
				state = 139;
				attribute -> push_back(c);
			} else if (c == 'n') {
				state = 144;
				attribute -> push_back(c);
			} else if (c == 'a') {
				state = 503;
				attribute -> push_back(c);
			} else if (c == '/') {
				state = 502;
				attribute -> push_back(c);
			} else if (c == '*') {
				state = 501;
				attribute -> push_back(c);
			} else if (c == 'o') {
				state = 403;
				attribute -> push_back(c);
			} else if (c == '-') {
				state = 402;
				attribute -> push_back(c);
			} else if (c == '+') {
				state = 401;
				attribute -> push_back(c);
			} else if (c == '<') {
				state = 304;
				attribute -> push_back(c);
			} else if (c == '>') {
				state = 302;
				attribute -> push_back(c);
			} else if (c == '=') {
				state = 301;
				attribute -> push_back(c);
			} else if (is_digit(c)) {
				state = 701;
				attribute -> push_back(c);
			} else if ( is_valid_identifier(c)) {
				state = 601;
				attribute -> push_back(c);
			} else if (c == '(') {
				state = 206;
				attribute -> push_back(c);
			} else if (c == ')') {
				state = 205;
				attribute -> push_back(c);
			} else if (c == ',') {
				state = 204;
				attribute -> push_back(c);
			} else if (c == ':') {
				state = 202;
				attribute -> push_back(c);
			} else if (c == ';') {
				state = 201;
				attribute -> push_back(c);
			} else if (c == EOF_MARKER) {
				state = FINAL_STATE;
				token = new EofToken();
			} break;
		
			// KEYWORD TOKENS
			case 101:
			if( c == 'h') {
				state = 102;
				attribute -> push_back(c);
			} else if ( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 102:
			if( c == 'e') {
				state = 103;
				attribute -> push_back(c);
			} else if (is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 103:
			if( c == 'n') {
				state = 104;
				attribute -> push_back(c);
			} else if (is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_THEN
			case 104:
			if(is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_THEN);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 105:
			if( c == 'r' ) {
				state = 106;
				attribute -> push_back(c);
			} else if(is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 106:
			if( c == 'i') {
				state = 107;
				attribute -> push_back(c);
			} else if( c == 'o') {
				state = 110;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);			
			} break;

			case 107:
			if( c == 'n') {
				state = 108;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 108:
			if( c == 't') {
				state = 109;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_PRINT
			case 109:
			if(is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_PRINT);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 110:
			if( c == 'g') {
				state = 111;
				attribute -> push_back(c);
			} else if( c == 'c') {
				state = 115;
				attribute -> push_back(c);
			} else if(is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 111:
			if( c == 'r') {
				state = 112;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 112:
			if( c == 'a') {
				state = 113;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 113:
			if( c == 'm') {
				state = 114;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_PROGRAM
			case 114:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_PROGRAM);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 115:
			if( c == 'e') {
				state = 116;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 116:
			if( c == 'd') {
				state = 117;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 117:
			if( c == 'u') {
				state = 118;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 118:
			if( c == 'r') {
				state = 119;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 119:
			if( c == 'e') {
				state = 120;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_PROCEDURE
			case 120:
			 if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_PROCEDURE);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 121:
			if( c == 'f') {
				state = 122;
				attribute -> push_back(c);
			}else if( c == 'n') {
				state = 123;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_IF
			case 122:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_IF);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 123:
			if( c == 't') {
				state = 124;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_INT
			case 124:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_INT);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 125:
			if( c == 'o') {
				state = 126;
				attribute -> push_back(c);
			} else if( c == 'e') {
				state = 129;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 126:
			if( c == 'o') {
				state = 127;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 127:
			if( c == 'l') {
				state = 128;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_BOOL
			case 128:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_BOOL);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 129:
			if( c == 'g') {
				state = 130;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 130:
			if( c == 'i') {
				state = 131;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 131:
			if( c == 'n') {
				state = 132;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_BEGIN
			case 132:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_BEGIN);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 133:
			if( c == 'n') {
				state = 134;
				attribute -> push_back(c);
			} else if( c == 'l') {
				state = 136;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 134:
			if( c == 'd') {
				state = 135;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_END
			case 135:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_END);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 136:
			if( c == 's') {
				state = 137;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 137:
			if( c == 'e') {
				state = 138;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_ELSE
			case 138:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_ELSE);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 139:
			if( c == 'h') {
				state = 140;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 140:
			if( c == 'i') {
				state = 141;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 141:
			if( c == 'l') {
				state = 142;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 142:
			if( c == 'e') {
				state = 143;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_WHILE
			case 143:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_WHILE);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 144:
			if( c == 'o') {
				state = 145;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 145:
			if( c == 't') {
				state = 146;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// KW_NOT
			case 146:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new KeywordToken(KW_NOT);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// PUNCTUATION TOKENS
			// ;
			case 201:
				token = new PuncToken(PUNC_SEMI);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// :
			case 202:
			if( c == '=') {
				state = 203;
				attribute -> push_back(c);
			} else {
				token = new PuncToken(PUNC_COLON);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// :=
			case 203:
				token = new PuncToken(PUNC_ASSIGN);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// ,
			case 204:
				token = new PuncToken(PUNC_COMMA);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// )
			case 205:
				token = new PuncToken(PUNC_CLOSE);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// (
			case 206:
				token = new PuncToken(PUNC_OPEN);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// RELATIONAL_TOKEN
			// =
			case 301:
				token = new RelopToken(RELOP_EQ);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// >
			case 302:
			if( c == '=') {
				state = 303;
				attribute -> push_back(c);
			} else {
				token = new RelopToken(RELOP_GT);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// >=
			case 303:
				token = new RelopToken(RELOP_GE);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// <
			case 304:
			if( c == '=') {
				state = 306;
				attribute -> push_back(c);
			} else if( c == '>') {
				state = 305;
				attribute -> push_back(c);
			} else {
				token = new RelopToken(RELOP_LT);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// <>
			case 305:
				token = new RelopToken(RELOP_NEQ);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// <=
			case 306:
				token = new RelopToken(RELOP_LE);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// ADDOP_TOKEN
			// +
			case 401:
				token = new AddopToken(ADDOP_ADD);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// -
			case 402:
				token = new AddopToken(ADDOP_SUB);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			
			case 403:
			if( c == 'r') {
				state = 404;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// OR
			case 404:
				if( is_alphanumeric(c)) {
					state = 601;
					attribute -> push_back(c);
				} else {
					token = new AddopToken(ADDOP_OR);
					state = FINAL_STATE;
					buffer -> unread_char(c);
				}
				break;

			// MULOP_TOKEN
			// *
			case 501:
				token = new MulopToken(MULOP_MUL);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			// /
			case 502:
				token = new MulopToken(MULOP_DIV);
				state = FINAL_STATE;
				buffer -> unread_char(c);
				break;

			case 503:
			if( c == 'n') {
				state = 504;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			case 504:
			if( c == 'd') {
				state = 505;
				attribute -> push_back(c);
			} else if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new IdToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// AND
			case 505:
			if( is_alphanumeric(c)) {
				state = 601;
				attribute -> push_back(c);
			} else {
				token = new MulopToken(MULOP_AND);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			// IDENTIFIER
			case 601:
				if( is_alphanumeric(c)) {
					state = 601;
					attribute -> push_back(c);
				} else {
					token = new IdToken(attribute);
					state = FINAL_STATE;
					buffer -> unread_char(c);
				} break;

			// NUM
			case 701:
			if( is_digit(c)) {
				state = 701;
				attribute -> push_back(c);
			} else {
				token = new NumToken(attribute);
				state = FINAL_STATE;
				buffer -> unread_char(c);
			} break;

			default:
				scanner_fatal_error();
				break;
		}
	}
	return token; 
}

Buffer *Scanner::get_buffer() {
		return buffer;
}




