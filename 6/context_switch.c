#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define ITERATIONS 1000000

int main() {
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  CPU_SET(0, &cpu_set);

  int pipe1[2], pipe2[2];
  if (pipe(pipe1) == -1) {
    perror("Failed to init pipe1.\n");
    exit(1);
  }
  if (pipe(pipe2) == -1) {
    perror("Failed to init pipe2.\n");
    exit(1);
  }

  int rc1 = fork();
  if (rc1 == -1) {
    perror("Failed to fork p1.\n");
    exit(1);
  } else if (rc1 == 0) {
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);
    close(pipe1[0]);
    close(pipe2[1]);

    char read_buf, write_buf = '1';
    struct timeval tv_start;
    struct timeval tv_end;
    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < ITERATIONS; i++) {
      write(pipe1[1], &write_buf, 1);
      read(pipe2[0], &read_buf, 1);
    }
    gettimeofday(&tv_end, NULL);
    long measurement = (tv_end.tv_sec - tv_start.tv_sec) * 1000000L +
                       (tv_end.tv_usec - tv_start.tv_usec);

    printf("-------------------\n");
    printf("Avg context switch overhead w/gettimeofday():-\n%Lf\n",
           (long double)(measurement) / (ITERATIONS * 2));
    printf("-------------------\n");

    return 0;
  }

  int rc2 = fork();
  if (rc2 == -1) {
    perror("Failed to fork p2.\n");
    exit(1);
  } else if (rc2 == 0) {
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set);
    close(pipe2[0]);
    close(pipe1[1]);

    char read_buf, write_buf = '2';
    for (int i = 0; i < ITERATIONS; i++) {
      read(pipe1[0], &read_buf, 1);
      write(pipe2[1], &write_buf, 1);
    }

    return 0;
  }

  close(pipe1[0]);
  close(pipe1[1]);
  close(pipe2[0]);
  close(pipe2[1]);

  wait(NULL);
  wait(NULL);

  return 0;
}
