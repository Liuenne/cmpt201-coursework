#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Start PID=%d, parent PID=%d\n", getpid(), getppid());
  int pid = fork();
  if (pid == 0) {
    printf("CHILD: PID=%d, parent PID=%d\n", getpid(), getppid());
  } else {
    printf("PARENT: PID=%d, child PID=%d\n", getpid(), pid);
  }
}
