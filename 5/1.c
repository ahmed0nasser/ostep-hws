#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int x = 100;

  printf("(%d): x=%d\n", getpid(), x);

  int rc = fork();
  if (rc == 0) {
    printf("child_before_change(%d): x=%d\n", getpid(), x);
    x = 200;
    printf("child_after_change(%d): x=%d\n", getpid(), x);
  } else {
    printf("parent_before_change(%d): x=%d\n", getpid(), x);
    x = 300;
    printf("parent_after_change(%d): x=%d\n", getpid(), x);
  }

  return 0;
}
