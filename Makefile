CC=c++
CFLAGS=-Wall -Wextra -std=c++11 -g
LDFLAGS=
all: main

check: main
	./main

main: obj/main.o obj/sphere.o obj/renderer.o obj/scene.o obj/background.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/main.o: src/main.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/renderer.o: src/renderer.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/background.o: src/background.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/scene.o: src/scene.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/sphere.o: src/sphere.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj:
	mkdir -p $@

clean:
	rm -rf main
	rm -rf obj
