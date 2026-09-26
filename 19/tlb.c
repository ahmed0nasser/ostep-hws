#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: tlb <num_pages> <trials>\n");
    return 1;
  }

  cpu_set_t mask;
  CPU_ZERO(&mask);
  CPU_SET(0, &mask); // Pin to CPU core 0
  if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
    perror("sched_setaffinity failed");
    return 1;
  }

  int numpages = atoi(argv[1]);
  long trials = atol(argv[2]);

  int pagesize = getpagesize();
  int jump = pagesize / sizeof(int);

  // Allocate on the heap (not as a VLA on the stack) so large page counts
  // don't blow past the ~8 MiB stack limit and cause SIGSEGV.
  int *a = calloc(numpages * (size_t)jump, sizeof(int));
  if (a == NULL) {
    perror("calloc failed");
    return 1;
  }

  // Warm-up: touch every page once so page-fault cost doesn't skew trial 1.
  for (int i = 0; i < numpages * jump; i += jump)
    a[i] = 0;

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int repeat = 0; repeat < trials; repeat++)
    for (int i = 0; i < numpages * jump; i += jump)
      a[i] += 1;
  clock_gettime(CLOCK_MONOTONIC, &end);

  printf("%f ns\n", (double)((end.tv_sec - start.tv_sec) * 1000000000 +
                            end.tv_nsec - start.tv_nsec) /
                       ((double)numpages * trials));

  free(a);
  return 0;
}