#Priya Upadhyay
#2018202012
CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = cursor.h delete.h commandmode.h ls.h mk_dir.h mk_file.h rename.h runcommands.h
OBJ = cursor.h delete.h commandmode.h ls.h mk_dir.h mk_file.h rename.h runcommands.h files.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

files: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

