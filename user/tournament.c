#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // Parse the number of processes
  int n = 16;
  
  // Create tournament tree
  int id = tournament_create(n);
  if (id < 0) {
    printf("Failed to create tournament tree\n");
    exit(1);
  }

  // Acquire the lock at the root
  if (tournament_acquire() < 0) {
    printf("Process %d: Failed to acquire tournament lock\n", getpid());
    exit(1);
  }

  // Critical section
  printf("Process %d (Tournament ID: %d) in critical section\n", getpid(), id);
  
  // Sleep briefly to demonstrate mutual exclusion
  sleep(10);

  // Release the lock
  if (tournament_release() < 0) {
    printf("Process %d: Failed to release tournament lock\n", getpid());
    exit(1);
  }

  exit(0);
}