#ifndef ADDOPTOKEN_H
#define ADDOPTOKEN_H
#include "token.h"
#include <string>

using namespace std;

typedef enum addop_attr
{
	ADDOP_ADD = 400,
	ADDOP_SUB = 401,
	ADDOP_OR  = 402,
	ADDOP_NO_ATTR = 403
} addop_attr_type;

// All token classes are subclasses of token
class AddopToken : public Token 
{
public:
	// Construct an uninitialized addop token
	AddopToken();

	~AddopToken();

	// Construct a addop token with an attribute
	AddopToken(addop_attr_type attr);

	// Return the attribute of this token
	addop_attr_type get_attribute() const;

	// Set the attribute of this token
	void set_attribute(addop_attr_type attr);

	string *to_string();

private:

	// This token's attribute
	addop_attr_type attribute;
};

#endif