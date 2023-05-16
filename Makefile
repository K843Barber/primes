lists: build/primes.o
	gcc -o primes src/primes.c

build/lists.o: src/primes.c
	gcc -o -c src/primes.c

build/%.o: src/%.c | build
	gcc -o $@ -c $<

clean:
	rm  -f -r build primes *.o

build:
	mkdir build
