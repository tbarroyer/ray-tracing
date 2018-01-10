CC=c++
CFLAGS=-Wall -Wextra -std=c++11
LDFLAGS=
all: main

check: main
	./main

main: obj/main.o obj/sphere.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/main.o: src/main.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/sphere.o: src/sphere.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj:
	mkdir -p $@

clean:
	rm -rf main
	rm -rf obj
