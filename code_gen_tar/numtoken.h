#ifndef NUMTOKEN_H
#define NUMTOKEN_H

using namespace std;

#include "token.h"
#include <string>

// All token classes are subclasses of Token
class NumToken : public Token
{
public:
	// Construct an uninitialized keyword token.
	NumToken();

	~NumToken();

    // Construct a num token with an attribute.
	NumToken(string *attr);

	// Return the attribute of this token
	string *get_attribute() const;

	// Set the attribute of this token
	void set_attribute(string *attr);

	string *to_string();

private:
	// This token's attribute
	string *attribute;
};

#endif
