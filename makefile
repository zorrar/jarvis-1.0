CC = g++
CFLAGS =-c -Wall
FILES = a.out
OUT_EXE = out_executable

all: execute
execute: download.o compile.o

download.o: 
		sudo apt-get install g++
		sudo apt-get install sqlite3
		sudo apt-get install libsqlite3-dev

compile.o: Jarvis.cpp
		$(CC) Jarvis.cpp -lsqlite3
		
build: $(FILES)
		$(CC) -o $(OUT_EXE) $(FILES)

clean: rm -rf *o main
