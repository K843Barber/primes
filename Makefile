lists: build/lists.o
	gcc -o lists src/lists.c

build/lists.o: src/lists.c
	gcc -o -c src/lists.c

build/%.o: src/%.c | build
	gcc -o $@ -c $<

clean:
	rm  lists ./-c

build:
	mkdir build
