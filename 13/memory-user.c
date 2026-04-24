#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#define MEGA 1000000
#define USAGE "Usage: ./memory-user MEGA_BYTES SECONDS\n"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Error: Too few arguments.\n");
    printf(USAGE);
    exit(1);
  } else if (argc > 3) {
    printf("Error: Too many arguments.\n");
    printf(USAGE);
    exit(1);
  }
  printf("PID: %d\n", getpid());

  // PARSING ARGS
  int mbs = atoi(argv[1]);
  int secs = atoi(argv[2]);
  printf("Arguments: MEGA_BYTES=%d, SECONDS=%d.\n", mbs, secs);

  // ALLOCATING MEMORY
  int bytes = MEGA * mbs;
  char* arr = (char *) malloc(sizeof(char) * bytes);
  if (arr == NULL) {
    printf("Error: Failed to allocate memory.\n");
    exit(1);
  }
  printf("%d Bytes Allocated.\n", bytes);

  struct timeval start, end;
  gettimeofday(&start, NULL);
  gettimeofday(&end, NULL);

  while (end.tv_sec - start.tv_sec < secs) {
    for (int i = 0; i < bytes; i++) {
      arr[i] = arr[i];
    }
    gettimeofday(&end, NULL);
  }
  printf("Finished after %d seconds.\n", secs);

  free(arr);
  printf("Memory freed.\n");

  return 0;
}
