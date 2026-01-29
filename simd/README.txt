Last name of Student 1: Surapaneni
First name of Student 1: Khilan
Email of Student 1: ksurapaneni@ucsb.edu
Last name of Student 2: Schoinas
First name of Student 2: Eirini
Email of Student 2: eirini@ucsb.edu



Report for Question 3

With -O on Expanse and n=1,000,000, the naïve sum is substantially slower at 0.004949 seconds and 2.02 GFLOPs compared to the 
SIMD implementations, with SSE at 0.002294 seconds and 4.36 GFLOPs and AVX at 0.002070 seconds and 4.83 GFLOPs. With -O3, 
the naive sum is not substantially slower, running at 0.002131 seconds and 4.69 GFLOPs, 
which is comparable to AVX at 0.002044 seconds and 4.89 GFLOPs and faster than SSE at 0.002492 seconds and 4.01 GFLOPs. 
The reason for this is that -O3 enables aggressive compiler optimizations such as auto-vectorization, loop unrolling, and 
better instruction scheduling, allowing the naïve loop to achieve performance close to hand-written SIMD while also reducing 
some overhead that limits the SSE version.