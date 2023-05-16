#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
  int a=0, C=0, D=0, counter=0;	// Count initialisers
  int i, j;				              // for loop
  int A;				                // Value to scan for
  int  *data, *data1, *data2;		// array pointers

  printf("Enter the first n numbers you want to see: ");
  scanf("%d", &A);

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


//  printf("\nThe list of primes between 1 and %d are: \n", A);
  // This loop is two-fold, it populates a list of ordered primes, as well as counting all the primes in the list.
  for (i=0; i<a;i++)
  {
    if(data2[i]!=0)
    {
     // printf("%d ", data2[i]);
      counter++;
    }
  }

  clock_t end = clock();
  double time_spent = (double)(end-begin) /CLOCKS_PER_SEC;
  FILE *fptr, *gptr;

  fptr = fopen("data/headers.txt", "w");
  gptr = fopen("data/timetaken.txt", "a");

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
  return 0;
}
