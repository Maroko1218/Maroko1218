run: parser
	./parser < prog.txt > prog.out
parser: driver.c parser.c keytoktab.c lexer.c optab.c symtab.c keytoktab.h parser.h symtab.h lexer.h optab.h
	gcc driver.c parser.c keytoktab.c lexer.c optab.c symtab.c -Wall -o parser