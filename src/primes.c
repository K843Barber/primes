#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//#include <writing.h>
//#define VERSION 2

void startup_message()
{
  printf("\e[1;1H\e[2J");
  
  printf("\t\t\t\t\t\033[1;31mPPPPPPP   RRRRRRR   IIIIII  MM      MM   EEEEEE  SSSSSSS\033[0m\n");
  printf("\t\t\t\t\t\033[1;32mPP   PP   RR   RR     II    MMMM  MMMM   EE      SS\033[0m\n");
  printf("\t\t\t\t\t\033[1;33mPPPPPPP   RRRRRRR     II    MM  MM  MM   EEEEE   SSSSSSS\033[0m\n");
  printf("\t\t\t\t\t\033[1;34mPP        RR RR       II    MM      MM   EE           SS\033[0m\n");
  printf("\t\t\t\t\t\033[1;35mPP        RR   RR   IIIIII  MM      MM   EEEEEE  SSSSSSS\033[0m\n");

  printf("\n\n");

}

void write_fn(char *file_headers, char *stats, int A, int counter, int *data2, double time_spent)
{
  FILE *fptr, *gptr;

  fptr = fopen(file_headers, "w");
  gptr = fopen(stats, "a");

  if(fptr == NULL || gptr == NULL)
  {
    printf("Error!");
    exit(1);
  }
  
  fprintf(fptr, "N		primes		Biggest Prime		time\n");
  fprintf(gptr, "%d		%d		%d			%f seconds\n", A, counter, data2[counter-1], time_spent);
  fclose(fptr);
  fclose(gptr);

  printf("There are %d prime numbers between 1 and %d which took %f seconds to compute, bitch. The biggest is %d\n", counter, A, time_spent, data2[counter-1]);
}

int contains(int value, int *data, size_t count) {
  const int* end = data + count;
  for (; data < end; data++) {
    if (value == (*data)) {
      return 1;
    }
  }
  return 0;
}

void check_is_prime(int A, int value, int *data2)
{
  if (contains(value, data2, A)) {
    printf("%d is a prime number!\n", value);
  } else {
    printf("%d is not a prime number!\n", value);
  }
}

int main()
{
  int A, value;				                // Value to scan for
  int  *data, *data1;                	// array pointers
  int *iter;

  startup_message();

  printf("Enter a number N: ");
  scanf("%d", &A);

  printf("Is it prime? Check if a value is prime or not between 1 and %d: ", A);
  scanf("%d", &value);


  clock_t begin = clock();

  const int datacount = A / 2 + 1;

  data = calloc(sizeof(int), datacount * 2);
  if (!data)
  {
    perror("Error allocating memory");
    abort();
  }
  data1 = data + datacount;

  // First steps to remove non primes. We remove both 1 and even numbers > 2
  iter = data;
  *iter++ = 2;
  for (size_t i=3; i < A; i++)
  {
  	if ((i%2) != 0)
  	{
  		*iter++ = i;
  	}
  }
  const size_t a = iter - data;

  // Here, we take the same list, one inside the other, take their remainder dividing one by the other and if we return 0, then take the smaller value since it is a factor of the larger number. i.e. 9 and 3, we keep 3. So our list now has primes but repeated.
  iter = data1;
  for (size_t i = 0; i < a; i++)
  {
    const int P = data[i];
    const int sqrtP = ((int)sqrt(P)) + 1;
    int *iterQ = data1;
    for (; iterQ < iter; iterQ++)
    {
      const int Q = *iterQ;
      if (Q > sqrtP) {
        iterQ = iter; // ugly way to show that this is a prime
        break;
      }
      if (P%Q == 0)
      {
        break;
      }
    }
    if (iterQ == iter) {
      *iter++ = P;
    }
  }

  const int count = iter - data1;
  check_is_prime(count, value, data1);

  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;  
  
  write_fn("data/headers.txt", "data/timetaken.txt", A, count, data1, time_spent);



  return 0;
}

// Options: Write to file with text output, print all the primes between range, chec if value is prime