#include "scanner.h"
#include "parser-cogen.h"
#include <iostream>
using namespace std;

/* This is a compiler for a simple programming language called TruPL
   by Viktor Jankov */

int main(int argc, char *argv[]) 
{
	Scanner *scanner = new Scanner(argv[1]);
	Parser *parser = new Parser(scanner);
	if( parser->parse_program()) 
	{
		if (!parser->done_with_input())
		{
			cout << "Syntax Error! Input after the end of program" << endl;
		} else
		{
			cout << "The parse has succeeded" << endl;
		} 
	} else 
	{
		cout << "Syntax Error" << endl;
	}
}
