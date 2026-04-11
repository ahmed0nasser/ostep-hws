#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 1000000

int main() {
  struct timeval tv_start;
  struct timeval tv_end;

  char buf;
  gettimeofday(&tv_start, NULL);
  for (int i = 0; i < ITERATIONS; i++) {
    read(STDIN_FILENO, &buf, 0);
  }
  gettimeofday(&tv_end, NULL);
  long long measurement = (tv_end.tv_sec - tv_start.tv_sec) * 1000000L +
                          (tv_end.tv_usec - tv_start.tv_usec);

  printf("-------------------\n");
  printf("Avg syscall overhead w/gettimeofday():-\n%Lf\n",
         (long double)(measurement) / ITERATIONS);
  printf("-------------------\n");

  return 0;
}
