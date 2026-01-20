/*
 * File:     treesum_mpi.c
 *
 * Purpose:  Use tree-structured communication to find the global sum
 *           of a random collection of ints.  This version doesn't
 *           require that comm_sz be a power of 2.
 *
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------
 * Function:
 *  global_sum
 *
 * Purpose:
 *  Implement a global sum using tree-structured communication
 *
 * Notes:
 *  1.  The return value for global sum is only valid on process 0
 */
int global_sum(int my_int, int my_rank, int comm_sz, MPI_Comm comm) {
    int my_sum = my_int;

    for (int step = 1; step < comm_sz; step *= 2) {
        if (my_rank % (2 * step) == 0) {
            int partner = my_rank + step;
            if (partner < comm_sz) {
                int recv_val;
                MPI_Recv(&recv_val, 1, MPI_INT,
                         partner, 0, comm, MPI_STATUS_IGNORE);
                my_sum += recv_val;
            }
        } else {
            int partner = my_rank - step;
            MPI_Send(&my_sum, 1, MPI_INT,
                     partner, 0, comm);
            break;
        }
    }

    return my_sum;
}

  return my_sum;
} /* Global_sum */
