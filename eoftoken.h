#ifndef EOFTOKEN_H
#define EOFTOKEN_H

using namespace std;

#include "token.h"
#include <string>

// All token classes are subclasses of token
class EofToken : public Token 
{
public:
	// Construct an uninitialized keyword token
	EofToken();

	~EofToken();

	string *to_string();
};

#endif
