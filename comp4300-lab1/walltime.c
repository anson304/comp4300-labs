#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>
#define ASIZE 100
int main(int argc, char *argv[]) {
  int time[ASIZE];
  int i, icnt;
  struct timeval tp1, tp2;

  MPI_Init(&argc, &argv);
  i = 0;
  icnt = 0;
  while (i < ASIZE) {
    icnt++;
    gettimeofday(&tp1, NULL);
    gettimeofday(&tp2, NULL);
    time[i] = (tp2.tv_sec - tp1.tv_sec)*1000000 + 
              (tp2.tv_usec - tp1.tv_usec);
    if (i%3 == 0) i++;
    else if (i%3 == 1 && time[i] > 0) i++;
    else if (i%3 == 2 && time[i] > 1) i++;
  }
  printf("Total timings %d \n", icnt);
  for (i = 0; i < ASIZE; i++) {
    printf("%d ", time[i]); 
    if (i%10 == 9) printf("\n");
  }

  printf("\n");
  MPI_Finalize();
  return 0;
} //main()
