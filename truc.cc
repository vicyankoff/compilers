#include "scanner.h"
#include "parser-semantic.h"
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
			cout << "Input after the end of program" << endl;
		} else
		{
			cout << "The parse has succeeded" << endl;
		} 
	} else 
	{
		cout << "The parse has a syntax error" << endl;
	}
}
