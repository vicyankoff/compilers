token.o: token.h token.cc
	g++ -c -w token.cc
addoptoken.o: addoptoken.h token.h addoptoken.cc
	g++ -c -w addoptoken.cc token.cc
idtoken.o: idtoken.h token.h idtoken.cc
	g++ -c -w idtoken.cc token.cc
muloptoken.o: muloptoken.h token.h muloptoken.cc
	g++ -c -w muloptoken.cc token.cc
punctoken.o: punctoken.h token.h punctoken.cc
	g++ -c -w punctoken.cc token.cc
eoftoken.o: eoftoken.h token.h eoftoken.cc
	g++ -c -w eoftoken.cc token.cc
keywordtoken.o: keywordtoken.h token.h keywordtoken.cc
	g++ -c -w keywordtoken.cc token.cc
numtoken.o: numtoken.h token.h numtoken.cc
	g++ -c -w numtoken.cc token.cc
reloptoken.o: reloptoken.h token.h reloptoken.cc
	g++ -c -w reloptoken.cc token.cc
buffer.o: buffer.h buffer.cc
	g++ -c -w buffer.cc
symbol_table.o: symbol_table.h symbol_table.cc
	g++ -c -w symbol_table.cc
scanner.o: scanner.cc scanner.h token.h	keywordtoken.h punctoken.h reloptoken.h addoptoken.h muloptoken.h idtoken.h numtoken.h eoftoken.h buffer.h
	g++ -c -w scanner.cc token.cc keywordtoken.cc punctoken.cc reloptoken.cc addoptoken.cc muloptoken.cc idtoken.cc numtoken.cc eoftoken.cc buffer.cc
parser-semantic.o: parser-semantic.cc parser-semantic.h token.h keywordtoken.h punctoken.h reloptoken.h addoptoken.h muloptoken.h idtoken.h numtoken.h eoftoken.h scanner.h symbol_table.h
		g++ -c -w parser-semantic.cc token.cc keywordtoken.cc punctoken.cc reloptoken.cc addoptoken.cc muloptoken.cc idtoken.cc numtoken.cc eoftoken.cc scanner.cc symbol_table.cc
test_scanner.o: token.h addoptoken.h idtoken.h muloptoken.h punctoken.h eoftoken.h keywordtoken.h numtoken.h reloptoken.h test_scanner.cc scanner.h
	g++ -c -w test_scanner.cc 
main: token.o keywordtoken.o test_scanner.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o
	g++ -g -Wall -pedantic -o main test_scanner.cc keywordtoken.o token.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o
truc.o: parser-semantic.h scanner.h truc.cc
	g++ -c -w truc.cc
truc: token.o keywordtoken.o test_scanner.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o parser-semantic.o truc.o symbol_table.o
	g++ -g -w -o truc truc.cc keywordtoken.o token.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o parser-semantic.o symbol_table.o	
clean:
	rm *.o
