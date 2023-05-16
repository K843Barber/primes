VERSION=1

lists: build/primes.o
	gcc -o primes src/primes.c

build/lists.o: src/primes.c
	gcc -o -c src/primes.c

build/%.o: src/%.c | build
	gcc -o $@ -DVERSION=$(VERSION) -c $<

clean:
	@rm  -f -r build primes *.o
	@echo Cleaned it ya filthy animal!

build:
	mkdir build
