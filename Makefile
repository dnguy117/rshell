CC = g++
CFLAGS = -Wall -c -Werror -ansi -pedantic
DEBUG = $(CFLAGS) += -ggdb

all: main RShellBase Command Connector RShellContainer
	mkdir -p bin
	$(CC) $(CFLAGS) main.o RShellBase.o Command.o Connector.o RShellContainer.o -o ./bin/rshell
  
main:
	$(CC) $(CFLAGS) ./src/main.cpp

RShellBase:
	$(CC) $(CFLAGS) ./src/RShellBase.cc

Command:
	$(CC) $(CFLAGS) ./src/Command.cc

Connector:
	$(CC) $(CFLAGS) ./src/Connector.cc

RShellContainer:
	$(CC) $(CFLAGS) ./src/RShellContainer.cc
 
clean:
	rm -r *.o
