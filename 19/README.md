1-
Timer must be nanoseconds precision so `gettimeofday()` may be inappropriate choice.

3-
Practically, greater than 1000 trials.

5-
This kind of compiler optimizations never take place on my measurements, however we can declare the array variable as volatile `volatile int *a` to eliminate possible optimization.

6-
We schedule program's thread to run on CPU 0 only using `sched_setaffinity()`. If we don't do this we get unreliable results because each CPU has its own TLB thus on mid-run migration, TLB seems to be flushed that causes unintended extra TLB-misses thus distorting the graph.

7-
Uninitialized array would cause expensive TLB-misses on first accesses which leads to. To counterbalance this effect we introduce a warm-up initialization loop, or simply use `calloc()`.
