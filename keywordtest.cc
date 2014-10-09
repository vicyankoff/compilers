#include "keywordtoken.h"
#include "addoptoken.h"
#include "idtoken.h"
#include "muloptoken.h"
#include "numtoken.h"
#include "punctoken.h"
#include "reloptoken.h"
#include "eoftoken.h"
#include "buffer.h"
#include "scanner.h"

#include <iostream>

int main()
{
  //buffer test
  char filestr[] = "TruPLSource.txt";
  Scanner *scanner = new Scanner(filestr);
  Buffer *buff = new Buffer(filestr);
	buff -> dump_buffer();
  cout << endl;
  cout << "Buffer is completly dumped" << endl;
  buff -> fill_buffer();
  cout << "Fill buffer again yo" << endl;
  buff -> dump_buffer();
	delete buff;
// A comment
  cout << endl;

  //addop test
  addop_attr_type add_attr = ADDOP_SUB;
  bool add;

  AddopToken addtoken1;
  AddopToken addtoken2(add_attr);
  addtoken1.set_attribute(add_attr);
  if(addtoken1.get_attribute() == addtoken2.get_attribute())
  {
    add = true;
  } else {
    add = false;
  }
  
  cout << *addtoken1.to_string() << *addtoken2.to_string() << add << endl;

  //idtoken test
  string id_attr ("Id token");
  string *id_attr_address (&id_attr);
  bool id;

  IdToken idtoken1;
  IdToken idtoken2(id_attr_address);
  idtoken1.set_attribute(id_attr_address);
  if(*idtoken1.get_attribute() == *idtoken2.get_attribute())
  {
    id = true;
  } else {
    id = false;
  }

  cout << *idtoken1.to_string() << *idtoken2.to_string() << id << endl;

  //muloptoken test
  mulop_attr_type mul_attr = MULOP_MUL;
  bool mul;

  MulopToken multoken1;
  MulopToken multoken2(mul_attr);
  multoken1.set_attribute(mul_attr);
  if(multoken1.get_attribute() == multoken2.get_attribute())
  {
    mul = true;
  } else {
    mul = false;
  }
  
  cout << *multoken1.to_string() << *multoken2.to_string() << mul << endl;

  //numtoken test
  string *num_attr = new string("alsdjflaj");
  bool num;

  NumToken numtoken1;
  NumToken numtoken2(num_attr);
  numtoken1.set_attribute(num_attr);
  if(*numtoken1.get_attribute() == *numtoken2.get_attribute())
  {
    num = true;
  } else {
    num = false;
  }

  cout << *numtoken1.to_string() << *numtoken2.to_string() << num << endl;

  //punctoken test
  punc_attr_type punc_attr = PUNC_SEMI;
  bool punc;

  PuncToken punctoken1;
  PuncToken punctoken2(punc_attr);
  punctoken1.set_attribute(punc_attr);
  if(punctoken1.get_attribute() == punctoken2.get_attribute())
  {
    punc = true;
  } else {
    punc = false;
  }
  
  cout << *punctoken1.to_string() << *punctoken2.to_string() << punc << endl;

  //reloptoken test
  relop_attr_type relop_attr = RELOP_EQ;
  bool relop;

  RelopToken reloptoken1;
  RelopToken reloptoken2(relop_attr);
  reloptoken1.set_attribute(relop_attr);
  if(reloptoken1.get_attribute() == reloptoken2.get_attribute())
  {
    relop = true;
  } else {
    relop = false;
  }
  
  cout << *reloptoken1.to_string() << *reloptoken2.to_string() << relop << endl;

  //eoftoken test
  EofToken eoftoken;
  cout << *eoftoken.to_string() << endl;

  //keyword test
  keyword_attr_type kw_attr = KW_WHILE;

  KeywordToken kwtoken1;
  KeywordToken kwtoken2(kw_attr);
  kwtoken1.set_attribute(kw_attr);
  cout << *kwtoken1.to_string() << *kwtoken1.to_string() << endl;
}
