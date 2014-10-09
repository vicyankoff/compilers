#ifndef BUFFER_H
#define BUFFER_H

#include <fstream>
#include <iostream>
#include <list>

// To get exit()
#include <stdlib.h>

/* This is the maximum number of characters from the source file that
 we will read into memory at once.
*/
#define MAX_BUFFER_SIZE 1024

/* We use '$' to mark the end of the source file in
 the buffer.
*/
#define EOF_MARKER '$'

// Characters that have a special meaning to the buffer.
#define COMMENT_MARKER '#'
#define SPACE ' '
#define NEW_LINE_CHAR '\n'
#define TAB_CHAR '\t'
#define SEMICOLON ';'
#define COLON ':'
#define LEFT_PAREN '('
#define RIGHT_PAREN ')'
#define COMMA ','
#define EQUALS '='
#define LESS_THAN '<'
#define GREATER_THAN '>'
#define PLUS '+'
#define MINUS '-'
#define MULTIPLIER '*'
#define DIVISOR '/'

 using namespace std;

 class Buffer
 {
 public:

	// Open the source file and initialize the buffer.
  Buffer(char *filename);

	// Close the file and cleanup.
  ~Buffer();

	// Remove the next character from the buffer and
	// return it.
  char next_char();

	// Put a character back at the front of the buffer.
  void unread_char (char c);

  // For debugging: dump the contents of the buffer on the screen.
  void dump_buffer();

private:
	// Storage for the buffer
  list<char> *buffer;

	// Input stream for the source.
  ifstream *source_file;

	/* If you encounter an error from which you can't recover, print an
   	error message and call this method.
		Method will have the illegal character for debugging purposes.
 	*/
   void buffer_fatal_error(char c);

	/* Fill the buffer from the file. The buffer filling code is
   where all the action happens in this class.  This function
   is responsible for filling the buffer until it is full with
   characters from the file.  Comments should be omitted,
   whitespace should be compressed to a single space character,
   and a '$' should be inserted at the end of the program to
   mark the end of the source file.
	*/
   void fill_buffer();

	// Is c a whitespace char?
   inline bool is_whitespace (char c)
   {
    return (c == SPACE || c == TAB_CHAR || c == NEW_LINE_CHAR);
  }

	// Is c a valid non-alphanumeric character
  inline bool is_valid_nonalphanum_char (char c)
  {
    return (c == SEMICOLON || c == COLON || c == LEFT_PAREN || c == RIGHT_PAREN || c == COMMA
      || c == EQUALS || c == LESS_THAN || c == GREATER_THAN || c == PLUS || c == MINUS
      || c == MULTIPLIER || c == DIVISOR || c == COMMENT_MARKER);
  }

  // Some helper functions
  inline bool is_alpha (char c)
  {
    return c >= 'a' && c <= 'z';
  }

  inline bool is_digit (char c)
  {
    return c >= '0' && c <= '9';
  }

  inline bool is_alphanumeric (char c)
  {
    return is_alpha(c) || is_digit(c);
  }

	// Is c a valid character?
  inline bool is_valid_char (char c)
  {
    return is_alphanumeric(c) || is_whitespace(c) || is_valid_nonalphanum_char(c);
  }

	// Method to strip characters from comments
  void strip_comment_characters(ifstream *m_source_file);

};

#endif
