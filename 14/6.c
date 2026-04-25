#include <stdio.h>
#include <stdlib.h>

int main() {
  int *data = (int *)malloc(sizeof(int) * 100);

  free(data);

  printf("data[5]=%d\n", data[5]);

  return 0;
}
