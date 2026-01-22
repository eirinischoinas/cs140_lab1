
/*
 * File:     treesum_test_mpi.c
 *
 * Purpose:  test tree-structured communication to find the global sum
 *           of a random collection of ints.  This version doesn't
 *           require that no of processes  be a power of 2.
 *
 * Compile:  mpicc -Wall -o treesum_test_mpi  treesum_test_mpi.c treesum_mpi.c
 * minunit.c Run:      ibrun  -v ./treesum_test_mpi
 *
 * IPP:      Programming Assignment Text Book Problem 3.3 Page 148
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

int my_rank, no_proc;
MPI_Comm comm;

int global_sum(int my_int, int my_rank, int no_proc, MPI_Comm comm);

/*-------------------------------------------------------------------
 * Test global_sum()
 * If successful, return NULL
 */
/*-------------------------------------------------------------------
 * Test global_sum()
 * If successful, return NULL
 */
char *treesum_test1() {
  int my_int, got, expected, pass;

  my_int = my_rank + 1;
  got = global_sum(my_int, my_rank, no_proc, comm);

  if (my_rank == 0) {
    expected = no_proc * (no_proc + 1) / 2;
    pass = (got == expected);
  }

  if (my_rank == 0) {
    for (int r = 1; r < no_proc; r++) {
      MPI_Send(&pass, 1, MPI_INT, r, 100, comm);
    }
  } else {
    MPI_Recv(&pass, 1, MPI_INT, 0, 100, comm, MPI_STATUS_IGNORE);
  }

  mu_assert("treesum_test1 case1 failed: rank0 did not get expected sum", pass);

  my_int = (my_rank % 3) - 1;
  got = global_sum(my_int, my_rank, no_proc, comm);

  if (my_rank == 0) {
    expected = 0;
    for (int r = 0; r < no_proc; r++) {
      expected += (r % 3) - 1;
    }
    pass = (got == expected);
  }

  if (my_rank == 0) {
    for (int r = 1; r < no_proc; r++) {
      MPI_Send(&pass, 1, MPI_INT, r, 101, comm);
    }
  } else {
    MPI_Recv(&pass, 1, MPI_INT, 0, 101, comm, MPI_STATUS_IGNORE);
  }

  mu_assert("treesum_test1 case2 failed: rank0 did not get expected sum", pass);

  return NULL;
}

/*-------------------------------------------------------------------
 * Run all tests.  Ignore returned messages.
 */
void run_all_tests(void) { mu_run_test(treesum_test1); }

/*-------------------------------------------------------------------
 * The main entrance to run all tests.
 * Only Proc 0 prints the test summary
 */
int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &no_proc);
  MPI_Comm_rank(comm, &my_rank);

  run_all_tests();

  if (my_rank == 0) {
    mu_print_test_summary("Summary:");
  }
  MPI_Finalize();
  return 0;
}
