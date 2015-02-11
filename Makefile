
build: p2es.o
default: p2es.o

all.c: tweetnacl.c p2es.c seckey.c
	cat $^ > $@

CC=clang
CFLAGS = -g -Wall

p2es.o: all.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm all.c p2es.o

.PHONY: clean
