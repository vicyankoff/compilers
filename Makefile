token.o: token.h token.cc
	g++ -c token.cc
addoptoken.o: addoptoken.h token.h addoptoken.cc
	g++ -c addoptoken.cc token.cc
idtoken.o: idtoken.h token.h idtoken.cc
	g++ -c idtoken.cc token.cc
muloptoken.o: muloptoken.h token.h muloptoken.cc
	g++ -c muloptoken.cc token.cc
punctoken.o: punctoken.h token.h punctoken.cc
	g++ -c punctoken.cc token.cc
eoftoken.o: eoftoken.h token.h eoftoken.cc
	g++ -c eoftoken.cc token.cc
keywordtoken.o: keywordtoken.h token.h keywordtoken.cc
	g++ -c keywordtoken.cc token.cc
numtoken.o: numtoken.h token.h numtoken.cc
	g++ -c numtoken.cc token.cc
reloptoken.o: reloptoken.h token.h reloptoken.cc
	g++ -c reloptoken.cc token.cc
buffer.o: buffer.h buffer.cc
	g++ -c buffer.cc
scanner.o: scanner.h addoptoken.h idtoken.h muloptoken.h punctoken.h eoftoken.h keywordtoken.h numtoken.h reloptoken.h buffer.h scanner.cc token.h
	g++ -c scanner.cc addoptoken.cc idtoken.cc muloptoken.cc punctoken.cc eoftoken.cc keywordtoken.cc numtoken.cc reloptoken.cc buffer.cc token.cc
test_scanner.o: token.h addoptoken.h idtoken.h muloptoken.h punctoken.h eoftoken.h keywordtoken.h numtoken.h reloptoken.h test_scanner.cc scanner.h
	g++ -c test_scanner.cc 
main: token.o keywordtoken.o test_scanner.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o
	g++ -g -Wall -pedantic -o main test_scanner.cc keywordtoken.o token.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o
clean:
	rm *.o
