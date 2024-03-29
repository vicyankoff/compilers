#ifndef RELOPTOKEN_H
#define RELOPTOKEN_H

using namespace std;

#include "token.h"
#include <string>

typedef enum relop_attr
{
	RELOP_EQ 	= 300,
	RELOP_NEQ 	= 301,
	RELOP_GT 	= 302,
	RELOP_GE 	= 303,
	RELOP_LT 	= 304,
	RELOP_LE	= 305,
	RELOP_NO_ATTR = 306
} relop_attr_type;

// All token classses are sublasses of token
class RelopToken : public Token
{
public:
	//Construct an uninitialized relop token
	RelopToken();

	~RelopToken();

	// Construc a relop token with an attribute.
	RelopToken(relop_attr_type attr);

	// Return the attribute of this token
	relop_attr_type get_attribute() const;

	// Set the attribute of this token
	void set_attribute(relop_attr_type attr);

	string *to_string();

private:

	// This token's attribute
	relop_attr_type attribute;
};

#endif
