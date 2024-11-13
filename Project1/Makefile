PJ1	:main.o util.o list_read.o list_write.o
	 g++ -Wall -o PJ1 main.o util.o list_read.o list_write.o

main.o	:main.cpp structs.h util.h list_read.h list_write.h
	 g++ -Wall -c main.cpp

util.o	:util.cpp structs.h util.h
	 g++ -Wall -c util.cpp

list_read.o	:list_read.cpp structs.h list_read.h
	 g++ -Wall -c list_read.cpp

list_write.o	:list_write.cpp structs.h list_write.h
	 g++ -Wall -c list_write.cpp

clean	:
	rm *.o PJ1
