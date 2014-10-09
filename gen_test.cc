#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
	ofstream myfile;
	myfile.open("allWords.txt");

	string *program = new string("program");
	string *word = new string("");
	for(int i = 0; i < program -> length(); i++) {
		word -> push_back(program -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *procedure = new string("procedure");
	for(int i = 0; i < procedure -> length(); i++) {
		word -> push_back(procedure -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *integer = new string("int");
	for(int i = 0; i < integer -> length(); i++) {
		word -> push_back(integer -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *boolean = new string("bool");
	for(int i = 0; i < boolean -> length(); i++) {
		word -> push_back(boolean -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *begin = new string("begin");
	for(int i = 0; i < begin -> length(); i++) {
		word -> push_back(begin -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *end = new string("end");
	for(int i = 0; i < end -> length(); i++) {
		word -> push_back(end -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *If = new string("if");
	for(int i = 0; i < If -> length(); i++) {
		word -> push_back(If -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *Then = new string("then");
	for(int i = 0; i < Then -> length(); i++) {
		word -> push_back(Then -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *Else = new string("else");
	for(int i = 0; i < Else -> length(); i++) {
		word -> push_back(Else -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *While = new string("while");
	for(int i = 0; i < While -> length(); i++) {
		word -> push_back(While -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *Print = new string("print");
	for(int i = 0; i < Print -> length(); i++) {
		word -> push_back(Print -> at(i));
		myfile << *word << "\n";
	}
	word = new string("");

	string *Not = new string("not");
	for(int i = 0; i < Not -> length(); i++) {
		word -> push_back(Not -> at(i));
		myfile << *word << "\n";
	}

	string *total = new string("programprocedurethenelsewhileprintnotif");
	myfile << *total<< endl;





}