#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  char *msg = "Hello World";
  char buf[12];

  int fd = open("tmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  write(fd, msg, strlen(msg));

  lseek(fd, -6, SEEK_CUR);
  read(fd, buf, sizeof(buf) - 1);

  write(STDOUT_FILENO, buf, 6);
}
