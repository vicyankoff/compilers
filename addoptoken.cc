#include "addoptoken.h"

/* Create a new token with no attribute */
AddopToken::AddopToken () : Token ()
{
	// Set the token type and init the attribute to undefined
	set_token_type (TOKEN_ADDOP);
	attribute = ADDOP_NO_ATTR;
}

/* Create a new token with an attribute */
AddopToken::AddopToken (addop_attr_type attr) : Token() 
{
	set_token_type (TOKEN_ADDOP);
	attribute = attr;
}

/* Nothing to do here */
AddopToken::~AddopToken () 
{

}

/* Return the token's attribte */
addop_attr_type AddopToken::get_attribute() const
{
	return attribute;
}

/* Set the token's attribute */
void AddopToken::set_attribute(const addop_attr_type attr)
{
	attribute = attr;
}

/* Extract the token type and attribute, and return a string*
	containing the information. Used for debugging only.
*/
string *AddopToken::to_string()
{
	string *attribute_name;

	switch (attribute)
	{
		case ADDOP_ADD:
			attribute_name = new string ("ADDITON");
			break;
		case ADDOP_SUB:
			attribute_name = new string ("SUBTRACTION");
			break;
		case ADDOP_OR:
			attribute_name = new string ("OR");
			break;
		case ADDOP_NO_ATTR:
			attribute_name = new string ("NO ATTRIBUTE VALUE");
			break;
		default:
			attribute_name = new string ("GARBAGE ATTRIBUTE VALUE");
			break;
	}

	string *result = new string ("ADDITIVE OPERATOR: " + *attribute_name);
	delete attribute_name;
	return result;
}
