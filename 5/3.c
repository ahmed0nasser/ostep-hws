#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int rc = fork();
  if (rc == 0) {
    printf("hello\n");
  } else {
    wait(NULL);
    printf("goodbye\n");
  }

  return 0;
}
