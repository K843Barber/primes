#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int count_primes(int *data2, int a)
{
  int i, counter=0;
  for (i=0; i<a;i++)
  {
    if(data2[i]!=0)
    {
      counter++;
    }
  }
  return counter;
}

int check_is_prime(int A, int value, int *data2)
{
  int i=0;

  while(value<=A)
  {
    if(value==data2[i])
    {
      printf("%d is a prime number!\n", value);
      break;
    }
    else if (i==A)
    {
      printf("%d is not a prime number!\n", value);
      break;
    }
    i++;
  }
}

int main()
{
  int a=0, C=0, D=0;	                // Count initialisers
  int i, j;				                    // for loop
  int A, value;				                // Value to scan for
  int  *data, *data1, *data2, count;	// array pointers

  startup_message();

  printf("Enter a number N: ");
  scanf("%d", &A);

  printf("Is it prime? Check if a value is prime or not between 1 and %d: ", A);
  scanf("%d", &value);


  clock_t begin = clock();

  const int datacount = A;
  data = malloc(sizeof(int) * datacount);
  data1 = malloc(sizeof(int) * datacount);
  data2 = malloc(sizeof(int) * datacount);

  if (!data || !data1 || !data2)
  {
    perror("Error allocating memory");
    abort();
  }

  memset(data, 0, sizeof(int)*datacount);
  memset(data1, 0, sizeof(int)*datacount);
  memset(data2, 0, sizeof(int)*datacount);

  // First steps to remove non primes. We remove both 1 and even numbers > 2
  for (i=0; i<datacount; i++)
  {
  	if ((i%2!=0 && i>2) || i==2)
  	{
  		data[a] = i;
			a++;
  	}
  }

  // Here, we take the same list, one inside the other, take their remainder dividing one by the other and if we return 0, then take the smaller value since it is a factor of the larger number. i.e. 9 and 3, we keep 3. So our list now has primes but repeated.
  for (i=0;i<a;i++)
  {
    for (j=0;j<a;j++)
    {
      int P = data[i];
      int Q = data[j];

      if (P%Q==0)
      {
        data1[C] = data[j];
        C++;
        break;
      }
    }
  }

  // Here, we go about removing the duplicates, so we have an ordered set of prime numbers.
  for (i=0; i<a;i++)
  {
    for (j=0;j<a;j++)
    {
      if (data1[i] == data[j] && i==j)
      {
        data2[D] = data[i];
        D++;
      }
    }
  }

  check_is_prime(A, value, data2);

  count = count_primes(data2, a); // Counts the number of primes

  clock_t end = clock();
  double time_spent = (double)(end-begin) /CLOCKS_PER_SEC;  
  
  write_fn("data/headers.txt", "data/timetaken.txt", A, count, data2, time_spent);



  return 0;
}

// Options: Write to file with text output, print all the primes between range, chec if value is prime