#include "buffer.h"

/* The constructor for the Buffer*/
Buffer::Buffer (char *filename) 
{
	source_file = new ifstream (filename);
	buffer = new list<char>();
	fill_buffer();
}

/* The deconstructor for the Buffer where we close the file name */
Buffer::~Buffer ()
{
	if( source_file -> is_open()) 
	{
		source_file -> close();
	}

	if( source_file != NULL ) {
		delete source_file;
	}
	if( buffer != NULL ) {
		delete buffer;
	}
}

/* Remove the next character from the buffer and return it */
char Buffer::next_char() 
{
	if( buffer -> empty() )
	{
		fill_buffer();
	}
	char next_char = buffer -> front();
	buffer -> pop_front();
	return next_char;
}

/* Put a character back at the front of the buffer */
void Buffer::unread_char(char c) 
{
	if(!is_whitespace(c)) {
		buffer -> push_front (c);
	}
}

void Buffer::buffer_fatal_error(char c)
{
	cout << "BUFFER ENCOUNTERED A FATAL ERROR" << endl;
	cout << "ILLEGAL CHARACTER: " << c << endl;
}

void Buffer::fill_buffer() 
{
	char next_file_char;
	char previous_char_in_buffer;
	int buffer_number_of_chars = 0;

	while( buffer_number_of_chars < MAX_BUFFER_SIZE) 
	{
		previous_char_in_buffer = buffer -> back();
		source_file -> get(next_file_char);

		while(next_file_char == COMMENT_MARKER) {
			while( next_file_char != NEW_LINE_CHAR && !source_file -> eof()) {
			source_file -> get(next_file_char);
				
			}
		}

		if( source_file -> eof() ) {
			if( is_whitespace(previous_char_in_buffer)) {
				buffer -> pop_back();
			}
			buffer -> push_back(EOF_MARKER);
			break;
		} else if( is_whitespace(next_file_char) && !is_whitespace(previous_char_in_buffer)) {
			buffer -> push_back(SPACE);
			buffer_number_of_chars++;
		} else if( is_whitespace(next_file_char) && is_whitespace(previous_char_in_buffer))
		{
				// don't consume this whitespace
		} else if (is_valid_char(next_file_char)) {
			buffer -> push_back(next_file_char);
			buffer_number_of_chars++;
		} else {
			buffer_fatal_error(next_file_char);
			exit(0);
		}
	}
}

void Buffer::dump_buffer() 
{
	std::list<char>::const_iterator iterator;
	for (iterator = buffer -> begin(); iterator != buffer -> end(); ++iterator) {
		std::cout << *iterator;
	}
}


