#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MSG_REPS 100
#define MAX_BUFFLEN 64

int main(int argc, char *argv[]) {
  int rank, nprocs;
  MPI_Status status;
  int *mbuf, len;
  int i;
  double timeMin, timeMax, t1, t2;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  len = MAX_BUFFLEN;
  mbuf = calloc(len, sizeof(int));
  for (i=0; i < MSG_REPS; i++) {
    t1 = MPI_Wtime();
    if (rank == 0) {
      MPI_Send(mbuf, len, MPI_INTEGER, rank+1, 0, MPI_COMM_WORLD);
      MPI_Recv(mbuf, len, MPI_INTEGER, rank+1, 1, MPI_COMM_WORLD, &status);
    } else if (rank == 1) {
      MPI_Send(mbuf, len, MPI_INTEGER, rank-1, 1, MPI_COMM_WORLD);
      MPI_Recv(mbuf, len, MPI_INTEGER, rank-1, 0, MPI_COMM_WORLD, &status);
    } 
    t2 = MPI_Wtime() - t1;
    timeMin = (i == 0 || t2 < timeMin)? t2: timeMin;
    timeMax = (i == 0 || t2 > timeMax)? t2: timeMax;
  }
  printf("process %d, %d words: ping-pong time: min %.2e max %.2e\n", 
	 rank, len, timeMin, timeMax);

  MPI_Barrier(MPI_COMM_WORLD);
  free(mbuf);

  MPI_Finalize( );
  return 0;
} //main()
