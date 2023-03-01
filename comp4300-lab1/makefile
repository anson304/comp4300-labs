#
CC 	= mpicc
CFLAGS 	= 
LDFLAGS	= 

all:		walltime mpiexample1 mpiexample2 mpiexample3

walltime:	walltime.o
		$(CC) -o $@ $@.o $(LDFLAGS) -lm

mpiexample1:	mpiexample1.o
		$(CC) -o $@ $@.o $(LDFLAGS)

mpiexample2:	mpiexample2.o
		$(CC) -o $@ $@.o $(LDFLAGS)

mpiexample3:	mpiexample3.o
		$(CC) -o $@ $@.o $(LDFLAGS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c    

clean:
	rm -f *.o walltime mpiexample1 mpiexample2 mpiexample3 batch_job.o* *~


