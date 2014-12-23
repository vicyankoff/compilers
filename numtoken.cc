
#include "numtoken.h"

/* Create a new token with no attributes. */
NumToken::NumToken() : Token ()
{
	set_token_type (TOKEN_NUM);
	attribute = new string ("UNINITIALIZED NUMTOKEN ATTRIBUTE");
}

/* Create a new token with an attribute */
NumToken::NumToken (string *attr) : Token ()
{
	// Set the token type and init the attribute
	set_token_type (TOKEN_NUM);
	attribute = new string(*attr);
}

/* Nothing to do here */
NumToken::~NumToken () 
{
	if( attribute != NULL) {
		delete attribute;
	}
}

/* Return the token's attribute */
string *NumToken::get_attribute() const
{
	string *attr = new string(*attribute);
	return attr;
}

/* Set the token's attribute */
void NumToken::set_attribute(string *attr)
{
	if( attribute != NULL) {
		delete attribute;
	}
	attribute = new string(*attr);
}

/* Extract the token type and attribute, and return a string*
   containing the information.  Used for debugging only.
*/

string *NumToken::to_string() 
{
	string *attribute_name = new string ("NUM: " + *attribute);
	return attribute_name;
}
