#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
  int fd = open("./2_test_file",O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  printf("(%d): fd=%d\n", getpid(), fd);

  int rc = fork();
  if (rc == 0) {
    printf("child(%d): fd=%d\n", getpid(), fd);

    const char* buf = "child_write\n";
    write(fd, buf, strlen(buf));
  } else {
    printf("parent(%d): fd=%d\n", getpid(), fd);

    const char* buf = "parent_write\n";
    write(fd, buf, strlen(buf));
  }

  return 0;
}
