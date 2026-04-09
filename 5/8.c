#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("Failed to establish pipe.\n");
    exit(1);
  }

  pid_t p1 = fork();
  if (p1 < 0) {
    perror("Failed to fork p1.\n");
    exit(1);
  } else if (p1 == 0) { // p1
    close(pipefd[1]);
    char buf;
    while (read(pipefd[0], &buf, 1)) {
      printf("p1(%d): reads %c\n", getpid(), buf);
    }
    close(pipefd[0]);
    return 0;
  }
  
  pid_t p2 = fork();
  if (p2 < 0) {
    perror("Failed to fork p2.\n");
    exit(1);
  } else if (p2 == 0) { // p2
    close(pipefd[0]);
    char* buf = "PIPE TEST.";
    printf("p2(%d): writes %s\n", getpid(), buf);
    write(pipefd[1], buf, strlen(buf));
    close(pipefd[1]);
    return 0;
  }

  close(pipefd[0]);
  close(pipefd[1]);
  return 0;
}
