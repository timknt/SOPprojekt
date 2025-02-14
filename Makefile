OBJS  = main.o greppy_args.o linkedList.o readFile.o caseInsensitive.o count.o output.o recursive.o thread.o search.o
SOURCE  = main.c greppy_args.c linkedList.c readFile.c caseInsensitive.c count.c output.c recursive.c thread.c search.c
HEADER  =
OUT = greppy
FLAGS = -g -c -Wall
LFLAGS  =
CC  = gcc

all:  a.out

a.out: $(OBJS)
  $(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
  $(CC) $(FLAGS) main.c

greppy_args.o: greppy_args.c
  $(CC) $(FLAGS) greppy_args.c

linkedList.o: linkedList.c
  $(CC) $(FLAGS) linkedList.c

readFile.o: readFile.c
  $(CC) $(FLAGS) readFile.c

caseInsensitive.o: caseInsensitive.c
  $(CC) $(FLAGS) caseInsensitive.c

count.o: count.c
  $(CC) $(FLAGS) count.c

output.o: output.c
  $(CC) $(FLAGS) output.c

recursive.o: recursive.c
  $(CC) $(FLAGS) recursive.c

thread.o: thread.c
  $(CC) $(FLAGS) thread.c

search.o: search.c
  $(CC) $(FLAGS) search.c

clean:
  rm -f $(OBJS) $(OUT)