#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

#define BLK_SIZE 128

void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BLK_SIZE];
  ssize_t len;

  if (data_size == sizeof(uint64_t)) {
    uint64_t val = *(uint64_t *)data;
    len = snprintf(buf, BLK_SIZE, format, val);
  } else if (data_size == sizeof(void *)) {
    void *ptr = *(void **)data;
    len = snprintf(buf, BLK_SIZE, format, ptr);
  } else if (data_size == sizeof(uint8_t)) {
    unsigned int val = *(uint8_t *)data;
    len = snprintf(buf, BLK_SIZE, format, val);
  } else {
    handle_error("Unsupported data size");
  }

  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *base = sbrk(256);

  if (base == (void *)-1) {
    perror("sbrk failed");
    return 1;
  }
  struct header *first = (struct header *)base;
  first->size = BLK_SIZE;
  first->next = NULL;
  void *first_data = (char *)first + sizeof(struct header);
  memset(first_data, 0, BLK_SIZE - sizeof(struct header));

  struct header *second = (struct header *)((char *)base + BLK_SIZE);
  second->size = BLK_SIZE;
  second->next = first;
  void *second_data = (char *)second + sizeof(struct header);
  memset(second_data, 1, BLK_SIZE - sizeof(struct header));

  print_out("first block:       %p\n", first, sizeof(first));
  print_out("second block:      %p\n", second, sizeof(second));

  print_out("first block size:  %lu\n", &first->size, sizeof(first->size));
  print_out("first block next:  %p\n", &first->next, sizeof(first->next));
  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  for (size_t i = 0; i < BLK_SIZE - sizeof(struct header); i++) {
    print_out("%u\n", &first_data[i], sizeof(uint8_t));
  }

  for (size_t i = 0; i < BLK_SIZE - sizeof(struct header); i++) {
    print_out("%u\n", &second_data[i], sizeof(uint8_t));
  }

  return 0;
}
