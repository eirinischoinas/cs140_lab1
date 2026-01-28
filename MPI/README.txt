Last name of Student 1: Surapaneni
First name of Student 1: Khilan
Email of Student 1: ksurapaneni@ucsb.edu
Last name of Student 2: Schoinas
First name of Student 2: Eirini
Email of Student 2: eirini@ucsb.edu



Report for Question 2.a

The 1-process baseline was 25.328857s (1.3565 GFLOPS). With 2 MPI processes, time dropped to 13.608521s (2.5249 GFLOPS), 
giving speedup 1.86x and efficiency 93.1%. With 4 processes, time dropped to 5.408177s (6.3533 GFLOPS), 
giving speedup 4.68x and efficiency 117.1% (superlinear speedup due to cache/working-set effects and 
reduced memory pressure per rank).



Report for Question 2.b

The single-process baseline ran in 13.44 seconds (1.28 GFLOPS). With 2 MPI processes, 
the runtime dropped to 10.21 seconds (1.68 GFLOPS), giving a speedup of 1.32x and efficiency of 65.8%. 
Using 4 processes reduced the runtime further to 4.55 seconds (3.78 GFLOPS), for a speedup of 2.96x and efficiency of 73.9%. 
Compared to Q2.a, the scaling here is noticeably worse. The main reason is load imbalance caused by the upper triangular matrix 
structure. Rows near the top of the matrix contain many nonzero elements, while rows near the bottom contain very few. 
Since rows are divided into contiguous blocks, some MPI processes get heavier workloads and run longer, 
while others finish early and sit idle. This increases the relative cost of communication and synchronization, 
which limits overall scalability as more cores are added. A practical way to address this is to use a round-robin (cyclic) 
row distribution instead of assigning consecutive row blocks. By spreading heavy and light rows evenly across processes, 
the workload becomes more balanced, idle time is reduced, and parallel efficiency improves. This would help narrow the 
performance gap between the dense and upper triangular cases and make better use of available cores.