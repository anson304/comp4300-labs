# COMP4300/8300 2023 - Tutorial/Laboratory 1
# Introduction to the NCI Gadi System and MPI

The aim of this session is get up and running on the NCI Gadi system and give you an introduction to MPI.

**To do this session, you need to have obtained an NCI login ID and password, by registering for an account (well) beforehand.** Click [here](https://wattlecourses.anu.edu.au/mod/page/view.php?id=2845897) for the instructions.

The Gadi system is supported by the National Computational Infrastructure program. Staff at Australian Universities are allocated time on this system through a competitive process for use in their research projects. We are extremely fortunate to have been given access to this system for this course. Please use the machine with respect. Note that it is NOT administered by the CS Technical Support Group.

> # TIP
>
> The user documentation for NCI Gadi system is [available here](https://opus.nci.org.au/display/Help/Gadi+User+Guide). You should familiarize yourself with the content. It will be referenced in what follows.

Log on to the Gadi system using your user ID: `ssh <username>@gadi.nci.org.au`

Each user has a file space quota. CPU time is also limited collectively over the entire course group (c07). This means one user can exhaust all the time of the entire group! Thus please monitor your usage of this machine and please ensure your batch file specifies a time limit of no more than 60s (should be more than plenty for anything you will need).

Read the section of Gadi's user-guide labelled **Welcome to Gadi** and execute the following commands on the login node:

`nci_account`

`lquota`

## Forking and Cloning the lab

All labs and assignments for this course will be provided through GitLab. This repository contains all the files that will be needed for this session.
Please fork and clone the lab (instructions [here](https://comp.anu.edu.au/courses/comp4300/assignments_workflow/#gitlab-usage)) to get started. Instructions to set up ssh keys can be found [here](https://docs.gitlab.com/ee/user/ssh.html))

## Modules

Gadi uses modules to provide different user environments. This allows, for instance, users to access old versions of libraries or compilers. Take a quick look at the [Environment Modules](https://opus.nci.org.au/display/Help/Environment+Modules) section of the user manual.

-   Run the command `module avail` to see what modules are available, and `module list` to see what modules you are using
-   Do `module load openmpi` to add MPI. What version of OpenMPI are you using by default? Add the above command into your `~/.bashrc` for later.

You can both `load` and `unload` a module. For this lab we will run with the default environment.

## Editing files

If you have prior experience using a terminal editor such as vi, vim, emacs, or nano, then you can use this editor on Gadi just like you would in a regular terminal. If not, then you can set up [vscode](https://code.visualstudio.com/) to act as a graphical editor over SSH using the [Remote Development](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack) extension by following the instructions [here](vscode-ssh-editing.md). This will work sufficiently for everything you are required to do in this course, however it is highly recommended to learn how to use a terminal based editor as it is likely that it will be a beneficial skill in future. The VSCode Remote Development extension does not support X display forwarding so you will need to use a regular terminal (or [MobaXterm](https://mobaxterm.mobatek.net/download-home-edition.html) on Windows) when a graphic display is required.

## `mpiexample1.c`

Open the file `mpiexample1.c`.

This program is just to get started. Note there are 3 basic requirements for **all** MPI codes:

```c
#include <mpi.h>
MPI_Init(&argc, &argv); 
MPI_Finalize(); 
```

You can find the header file in `/apps/openmpi/4.1.4/include/mpi.h`. (Do you know what version of OpenMPI are you using now?) Take a look at it. It provides the definition of `MPI_COMM_WORLD` in a complicated fashion involving a global structure that is initialized in another function in the library (it used to be easier!).

`MPI_Init()` and `MPI_Finalize()` should be the first and last executable statements in your code -- basically because it is not clear what happens before or after calls to these functions!! `man MPI_Init` says:

> The MPI Standard does not say what a program can do before an MPI_Init or after an MPI_Finalize. In the Open MPI implementation, it should do as little as possible. In particular, avoid anything that changes the external state of the program, such as opening files, reading standard input, or writing to standard output.

------------------------------------------------------------------------

If you want to know what an MPI function does you can:

-   look up `man MPI_<function>` (assuming the `openmpi` module has been loaded first).
-   read the [MPI1 standard](http://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/mpi-report.html)
-   read the online [MPI-1 book](http://www.netlib.org/utk/papers/mpi-book/mpi-book.html)
-   ask your tutor!

Note that at the moment we are only interested in MPI1.

------------------------------------------------------------------------

Compile the code: `make mpiexample1`

This will result in:

```sh
mpicc -c mpiexample1.c
mpicc -o mpiexample1 mpiexample1.o 
```

`mpicc` is a wrapper that will end up calling a standard C compiler (in this case gcc) Do `mpicc -v mpiexample1.c` to see all the details. `mpicc` also ensures that the program links with the MPI library.

Run the code interactively by typing `./mpiexample1`.

You should find the executable runs using just one process. With some MPI implementations the code will fail because you have not defined the number of processes to be used. Using OpenMPI this is done using the command `mpirun`.

Try running the code interactively again but this time by typing `mpirun -np 2 ./mpiexample1`.

Now try: `mpirun -np 6 ./mpiexample1`.

Try using `-np 64`; it will fail - why? What is the maximum number of MPI processes you can create interactively?

If you run this program enough times you may see that the order in which the output appears changes. Output to `stdout` is line buffered, but beyond that can appear in any order.

`mpirun` has a host of different options. Do `man mpirun` for more information. The `-np` option refers to the number of processes that you wish to spawn.

So far we have only been running our code on one of the Gadi nodes. In total, Gadi has 3,074 nodes (and 180,000 cores). Ten of these are reserved for interactive logins; the remaining nodes are only available via a batch queuing system (which of the six interactive nodes are you logged on to? Run the command `hostname` if unsure).

Go back to the Gadi user guide, Welcome to Gadi section; scroll down to the PBS Jobs section.

Now we will run the same job, but using the PBS batch queuing system. To submit a job to the queuing system, we have to write a batch script. An example of this is given in file `batch_job`. Take a look at this. Lines starting with `PBS` are commands to the queuing system, informing it of how much resources you require and how your job should be executed. We use one of these lines to set the number of processors you want to use. *Very important is the line to limit the walltime!*. Click [here](https://comp.anu.edu.au/courses/comp4300/assignments_workflow/#usage-of-gadi) for additional details.

Please ensure you limit walltime similarly for any batch job that you use. After all this setup information you run the job by issuing the `mpirun` command, but taking the number of processes from the number of processors allocated by the queuing system.

To submit your job to the queuing system, run `qsub batch_job`.

It will respond with something like

```sh
$ qsub batch_job
2095424.gadi-pbs
```

where `2095424.gadi-pbs` is the id of the job in the queuing system. To see what is happening on the batch queue, run `qstat`:

```
aaa444@gadi:~/> qstat
Job id                 Name             User              Time Use S Queue
---------------------  ---------------- ----------------  -------- - -----
2095424.gadi-pbs       batch_job        aaa444                   0 R express-exec
```

In the above, the `batch_job` is running as indicated by the `R` in the `S` column. If it was queued, this would be  indicated by a `Q`.

To track the progress of only one job, try `qstat 2095424.gadi-pbs`. To track all of your current jobs, use `qstat -a `.

To delete a job from the queue, run `qdel 2095424.gadi-pbs`.

When your job completes, the combined standard output and error will be put in a file, in this case named `batch_job.o2095424`. Inspect this file.

Make sure you are happy with the above since you will need to use the batch system later.

## Exercise 1

Modify the code in `mpiexample1.c` to also print out the name of the node each process is executing on. Do this by using the system call:

```sh
gethostname(name, sizeof(name));
```

Use `man gethostname` to find the relevant include file that you need to add.

1.  Run your modified version of `mpiexample1` interactively. What nodes of the cluster are being used?
2.  Repeat the above, but now use the batch file. What nodes are now being used?
3.  Modify the batch script so that your MPI code has enough processes to run on at least two different nodes of the Gadi system. *Hint:* request PBS for more CPUs than there are on one node; you may also need to increase the memory accordingly. After you know how to do this, return to using one node.

## Exercise 2

Throughout the course we will be measuring the elapsed time taken to run our parallel jobs. So we start by assessing how good our various timing functions are.

1.  What is the difference between timer call overhead and timer resolution?
2.  We can assess the call overhead and resolution of a timer by calling it twice in quick succession, printing the difference, and repeating this whole process many times. Why is this? (see the lecture on performance models)
3.  Code that does the above for the `gettimeofday()` system call is provided in `walltime.c`. Compile and run this, and from the output estimate the overhead and resolution of `gettimeofday()` (if you are not familiar with this system call, do `man gettimeofday`).
4.  MPI provides its own timing function, `MPI_Wtime()` (do `man MPI_Wtime`). Modify the code to test the resolution of this function. What do you estimate the resolution to be?
5.  What does the function `MPI_Wtick()` do? What value does it report?

## Exercise 3

In `mpiexample2.c`, each process allocates an integer buffer of size `BUFFLEN` (= 128 integers). Each buffer is initialized to the rank of the process. Process 0 sends its buffer to process 1 and vice versa, i.e. process 0 sends a message of zeros and receives a message of 1s, while process 1 does the opposite.

1.  Compile and run the code interactively using two processes, i.e. `mpirun -np 2 ./mpiexample2`. Verify that it works as you expect.
2.  Now change the code so that `BUFFLEN` is 67336. Attempt to run the code. You should find that it fails to complete. Why? Fix the code so that it completes for any value of `BUFFLEN`.

## Exercise 4

`mpiexample3.c` is a basic ping-pong code. Run the code and make sure it works. After doing so several times, do you observe a (small) potential accuracy problem for timing this operation? *Hint:* refer to your results in Q3.

1.  Currently the code only does ping-pong between processes 0 and 1 for a message containing 64 integers and measures the time using `MPI_Wtime()`. Modify the code so that it runs with a message length `len` from 1 to 4\*1024\*1024 integers in powers of 4 (i.e. 1, 4, 16, 64, 256, 1024, ...). Also rectify the timing problem. Modify the code to print out the average time and the corresponding bandwidth in GB/s (on process 0). As always, test the code interactively first. Are the results what you expected?
2.  Taking into account we are measuring the round trip time of 2 messages, what is the latency and what is peak bandwidth for a single message (which in this case is between 2 Gadi cores on the same node)? How does the bandwidth change with message length?
3.  Further modify the code so that it measures the ping-pong time between process 0 and all other processes in `MPI_COMM_WORLD` for messages of 1, 1024 and 1048576 integers.
4.  Run your code on the batch system using 96 CPUs (again you may need to ask for some more memory) and complete the following table:

    | Message Size (ints) | time for ping-pong between two processes |                 |
    |---------------------|------------------------------------------|-----------------|
    |                     | within a node                            |between two nodes|
    | 1                   |                                          |                 |
    | 1024                |                                          |                 |
    | 1048576             |                                          |                 |

5.  What results did you expect to see? Are the results in line with these expectations? If not why not?

