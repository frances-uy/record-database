project1: user_interface.o database.o
	gcc -o project1 user_interface.o database.o

user_interface.o: user_interface.c database.h record.h
	gcc -ansi -pedantic-errors -Wall -c user_interface.c database.h record.h

database.o: database.c database.h record.h
	gcc -ansi -pedantic-errors -Wall -c database.c database.h record.h

clean: rm user_interface.o database.o
