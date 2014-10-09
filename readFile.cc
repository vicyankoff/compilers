#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

// comments should be ommited
// whitespace compressed
// EoF should have $

inline bool is_whitespace(char c) 
{
  return (c == ' ' || c == '\n' || c == '\t');
}

void output(const char *filename) 
{
  char singleChar;
  list<char> *b = new list<char>();
  ifstream *source_file = new ifstream(filename);

  int buffer_size = 1024;
  int buffer_chars = 0;

  while( buffer_chars < buffer_size ) {
    source_file -> get(singleChar);
    char last_char = b -> back();
    if( singleChar == '#' ) {
      source_file -> get(singleChar);
      // this is a comment section
      while( singleChar != '\n' ) {
        source_file -> get(singleChar);
      }
      source_file -> get(singleChar);
    }
    if( is_whitespace(singleChar) && !is_whitespace(last_char)) {
      b->push_back(' ');
      buffer_chars++;
    } else if (source_file->eof()) {
      b->push_back('$');
      buffer_chars++;
      break;
    }else if(is_whitespace(singleChar) && is_whitespace(last_char))
    {

    } else {
      b->push_back(singleChar);
      buffer_chars++;
    }
  }

  list<char>::const_iterator list;
  for(list = b->begin(); list != b->end(); list++) {
    cout << *list;
  }
}

int main () {
  output("file.txt");
  return 0;
}
