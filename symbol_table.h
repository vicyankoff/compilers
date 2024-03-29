#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <stdlib.h>
#include "emitter.h"

using namespace std;

// The max size of our symbol table.
#define MAX_SYMBOLS 128

/* Types of expressions that the semantic analyzer must
	 manipulate. These are stored in the symbol table
	 or returned by parser functions as an attribute
	 of a non-terminal
*/
typedef enum expression_type {INT_T					= 700, // int
		BOOL_T  			= 701, // bool
		PROCEDURE_T		= 703, // procedure name
		PROGRAM_T			= 702, // program name
		UNKNOWN_T 		= 704, // type is currently unknown
		NO_T					= 705, // no type associated with this attribute
		GARBAGE_T			= 799} expr_type; //initial value

class Symbol_Table {

public:
	Symbol_Table();
	~Symbol_Table();
	
	/* 
		These are the methods that I used to manipulate the symbol table in
		my compiler. You may or may not use all of these in yours
	*/

	/* Install an identifier in the symbol table if the environment
		and type are known */
	void install (string *id, string *environment, expr_type t);

	/* Install a formal parameter in the symbol table */
	void install_parm (string *id, string *environment, expr_type t, int position);

	/* Has an identifier been defined in this environment? */
	bool is_decl (string *id, string *environment);

	/* Get the typeof an identifier in a given environment. Used when
		 determining whether an expression or statement
		 is semantically correct. */
	expr_type get_type (string *id, string *environment);

	/* Get the type of a formal parameter declared in environment
		 by its position in the argument list */
	expr_type get_type (string *environment, int position);

	/* Iterate over symbol table, updating all entries with
		 type == UNKNOWN_T to standard_type_type */
	void update_type (expr_type standard_type_type);

	void update_arg_list (int &parm_pos, expr_type standard_type_type);

	/* Find the first identifier in the symbol table with an unknown
		 type, and set its parameter position. Note that this needs to 
		 be called before update_type in order to correctly set
		 the positions of parameters in the argument list.
	*/
	void set_parm_pos (int pos);

	// Convert an expr_type to a string - useful for debugging.
	string *to_string (expr_type t);

	// Print the contents of the table
	void dump_table();
	
	void emit_data_directives();

	int get_table_size();
	
	private:

	// One symbol table entry
	typedef struct stab_entry {
		string *id;
		string *env;
		int position;
		expr_type type;
	} STAB_ENTRY;

	STAB_ENTRY table[MAX_SYMBOLS];

	Emitter *e;
	int size;
	void error_stab_overflow (string *id, string *env);

	/* A get_type() was attempted, but the symbol wasn't found.
		 Shouldn't happen if you use a is_decl() before searching.
	*/
	void error_stab_not_found (string *id, string *env);
};

#endif

