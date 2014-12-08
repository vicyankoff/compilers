#include "eoftoken.h"

/* Create a new token */
EofToken::EofToken () : Token() 
{
	set_token_type (TOKEN_EOF);
}

/* Nothing to do here */
EofToken::~EofToken () 
{

}

/* Extract the token type and attribute, and return a string*
   containing the information.  Used for debugging only.
*/
string *EofToken::to_string()
{
	string *attribute_name = new string ("EOF TOKEN");
	return attribute_name;
}
