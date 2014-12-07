token.o: token.h token.cc
	g++ -w -c token.cc
addoptoken.o: addoptoken.h token.h addoptoken.cc
	g++ -w -c addoptoken.cc token.cc
idtoken.o: idtoken.h token.h idtoken.cc
	g++ -w -c idtoken.cc token.cc
muloptoken.o: muloptoken.h token.h muloptoken.cc
	g++ -w -c muloptoken.cc token.cc
punctoken.o: punctoken.h token.h punctoken.cc
	g++ -w -c punctoken.cc token.cc
eoftoken.o: eoftoken.h token.h eoftoken.cc
	g++ -w -c eoftoken.cc token.cc
keywordtoken.o: keywordtoken.h token.h keywordtoken.cc
	g++ -w -c keywordtoken.cc token.cc
numtoken.o: numtoken.h token.h numtoken.cc
	g++ -w -c numtoken.cc token.cc
reloptoken.o: reloptoken.h token.h reloptoken.cc
	g++ -w -c reloptoken.cc token.cc
buffer.o: buffer.h buffer.cc
	g++ -w -c buffer.cc
symbol_table.o: symbol_table.h symbol_table.cc
	g++ -w -c symbol_table.cc
register.o: register.h register.cc
	g++ -w -c register.cc
register_allocator.o: register_allocator.h register_allocator.cc register.h emitter.h symbol_table.h
	g++ -w -c register_allocator.cc register.cc emitter.cc symbol_table.cc
emitter.o: emitter.h emitter.cc register.h
	g++ -w -c emitter.cc register.cc
scanner.o: scanner.cc scanner.h token.h	keywordtoken.h punctoken.h reloptoken.h addoptoken.h muloptoken.h idtoken.h numtoken.h eoftoken.h buffer.h
	g++ -w -c scanner.cc token.cc keywordtoken.cc punctoken.cc reloptoken.cc addoptoken.cc muloptoken.cc idtoken.cc	numtoken.cc eoftoken.cc buffer.cc
parser-cogen.o: parser-cogen.cc parser-cogen.h token.h keywordtoken.h punctoken.h reloptoken.h addoptoken.h muloptoken.h idtoken.h numtoken.h eoftoken.h scanner.h symbol_table.h register.h register_allocator.h emitter.h
	g++ -w -c parser-cogen.cc token.cc keywordtoken.cc punctoken.cc reloptoken.cc addoptoken.cc muloptoken.cc idtoken.cc numtoken.cc eoftoken.cc scanner.cc symbol_table.cc register.cc register_allocator.cc emitter.cc
truc.o: parser-cogen.h scanner.h truc.cc
	g++ -w -c truc.cc
truc: token.o keywordtoken.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o parser-cogen.o truc.o symbol_table.o register.o register_allocator.o emitter.o
	g++ -g -w -o truc truc.cc keywordtoken.o token.o addoptoken.o idtoken.o eoftoken.o muloptoken.o numtoken.o punctoken.o reloptoken.o buffer.o scanner.o parser-cogen.o symbol_table.o register.o register_allocator.o emitter.o
clean:
	rm *.o
