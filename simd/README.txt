Last name of Student 1: Surapaneni
First name of Student 1: Khilan
Email of Student 1: ksurapaneni@ucsb.edu
Last name of Student 2: Schoinas
First name of Student 2: Eirini
Email of Student 2: eirini@ucsb.edu



Report for Question 3

With -O on CSIL and n=1,000,000, the naive sum is substantially slower at 0.006915 seconds and 1.45 GFLOPs 
compared to the SIMD implementations, with SSE at 0.003857 seconds and 2.59 GFLOPs and AVX at 0.003466 seconds and 2.88 GFLOPs. 
With -O3, the naive sum is not substantially slower, running at 0.003241 seconds and 3.09 GFLOPs, 
which is comparable to AVX at 0.003205 seconds and 3.12 GFLOPs and faster than SSE at 0.003787 seconds and 2.64 GFLOPs. 
The reason for this is because -O3 enables aggressive compiler optimizations like auto vectorization, loop unrolling, 
and improved instruction scheduling, allowing the naive loop to come near to SIMD in the performance domain while reducing overhead 
that limits SSE version.