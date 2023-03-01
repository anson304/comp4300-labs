#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int rank, nprocs;
  char name[32];
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("Hello world from process %d of %d\n", rank, nprocs);
  MPI_Finalize();
  return 0;
} //main()

