LDFLAGS=-lm
VERSION=1

primes: build/primes.o
	gcc -o $@ $^ $(LDFLAGS) -O2

build/primes.o: build src/primes.c
	gcc -o $@ -c src/primes.c -O2

build/%.o: src/%.c | build
	gcc -o $@ -DVERSION=$(VERSION) -c -O2 

clean:
	@rm  -f -r build primes *.o ./-c
	@echo Cleaned it ya filthy animal!

build:
	mkdir build
