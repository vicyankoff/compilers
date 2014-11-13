#include "scanner.h"
#include "parser.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) 
{
	Scanner *scanner = new Scanner(argv[1]);
	Parser *parser = new Parser(scanner);
	if( parser->parse_program()) 
	{
		cout << "The parse has succeeded" << endl;
	} else 
	{
		cout << "The parse has a syntax error" << endl;
	}
}
