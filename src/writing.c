#include <writing.h>

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

  printf("There are %d prime numbers between 1 and %d which took %f seconds to compute. The biggest is %d\n", counter, A, time_spent, data2[counter-1]);
}
