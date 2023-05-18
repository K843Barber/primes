LDFLAGS=-lm
VERSION=1

primes: build/primes.o
	gcc -o $@ $^ $(LDFLAGS)

build/primes.o: src/primes.c
	gcc -o $@ -c src/primes.c

build/%.o: src/%.c | build
	gcc -o $@ -DVERSION=$(VERSION) -c 

clean:
	@rm  -f -r build primes *.o ./-c
	@echo Cleaned it ya filthy animal!

build:
	mkdir build
