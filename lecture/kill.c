#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void handle_sigint(int signum) {
  write(STDOUT_FILENO, "CTRL-C Pressed\n", strlen("CTRL-C Pressed\n"));
}

int main() {
  pid_t pid = fork();
  if (pid != 0) {
    struct sigaction act;
    act.sa_handler = handle_sigint;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    if (sigaction(SIGINT, &act, NULL) == -1) {
      perror("Sigaction() failed");
      exit(EXIT_FAILURE);
    }

    while (1) {
      sleep(1);
    }
  } else {
    while (1) {
      sleep(2);
      printf("HEY PARENT");
      if (kill(getppid(), SIGINT) == -1) {
        perror("Unable to send signal to parent");
        exit(EXIT_FAILURE);
      }
    }
  }
}
