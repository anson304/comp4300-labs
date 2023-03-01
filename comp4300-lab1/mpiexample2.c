#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define BUFFLEN 128
int main(int argc, char *argv[]) {
  int rank, nprocs;
  MPI_Status status;
  int *sbuf, *rbuf; //send a receive buffers
  int j;
  int tag0 = 100, tag1 = 200; 

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  printf("Hello from process %d \n", rank);

  sbuf = malloc(BUFFLEN*sizeof(int));
  rbuf = malloc(BUFFLEN*sizeof(int));
  for (j=0; j < BUFFLEN; j++)
    sbuf[j] = rank;

  if (rank == 0) {
    MPI_Send(sbuf, BUFFLEN, MPI_INTEGER, rank+1, tag0, MPI_COMM_WORLD);
    MPI_Recv(rbuf, BUFFLEN, MPI_INTEGER, rank+1, tag1, MPI_COMM_WORLD,&status);
  } else if (rank == 1) {
    MPI_Send(sbuf, BUFFLEN, MPI_INTEGER, rank-1, tag1, MPI_COMM_WORLD);
    MPI_Recv(rbuf, BUFFLEN, MPI_INTEGER, rank-1, tag0, MPI_COMM_WORLD,&status);
  } 

  MPI_Barrier(MPI_COMM_WORLD);
  printf("Process %d: first 5 elements of rbuf: %d %d %d %d %d\n",
         rank, rbuf[0], rbuf[1], rbuf[2], rbuf[3], rbuf[4]);
  printf("Goodbye from process %d \n",rank);
  MPI_Barrier(MPI_COMM_WORLD);

  free(sbuf);
  free(rbuf);
  MPI_Finalize();
  return 0;
} //main()
