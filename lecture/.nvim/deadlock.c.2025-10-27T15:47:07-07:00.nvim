#include <pthread.h>
#include <stdio.h>
int A = 0;
int B = 0;

pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lockB = PTHREAD_MUTEX_INITIALIZER;

static void *funcA() {
  pthread_mutex_lock(&lockA);
  printf("Thread A: locked A\n");
  pthread_mutex_lock(&lockB);
  printf("Thread A: locked B\n");
  pthread_mutex_unlock(&lockB);
  pthread_mutex_unlock(&lockA);
  printf("Thread A: unlocked A & B\n");
  pthread_exit(0);
}

static void *funcB() {
  pthread_mutex_lock(&lockB);
  printf("Thread B: locked B\n");
  pthread_mutex_lock(&lockA);
  printf("Thread B: locked A\n");
  pthread_mutex_unlock(&lockA);
  pthread_mutex_unlock(&lockB);
  printf("Thread B: unlocked A & B\n");
  pthread_exit(0);
}

int main() {
  pthread_t t1;
  pthread_t t2;

  pthread_create(&t1, NULL, funcA, NULL);
  pthread_create(&t2, NULL, funcB, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
