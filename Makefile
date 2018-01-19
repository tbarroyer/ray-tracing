CC=c++
CFLAGS=-Wall -Wextra -std=c++11 -O3 -fopenmp
LDFLAGS=-fopenmp
all: main

check: main
	./main
	feh *.ppm

main: obj/main.o obj/sphere.o obj/renderer.o obj/scene.o obj/background.o obj/perio_plan.o obj/water_plan.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/perio_plan.o: src/perio_plan.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

obj/water_plan.o: src/water_plan.cc obj
	$(CC) -o $@ -c $< $(CFLAGS)

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
