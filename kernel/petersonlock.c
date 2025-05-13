#include "types.h"
#include "petersonlock.h"

void initPeterson(void){
    for(int i = 0; i < PETERSON_LOCKS; i++){
        //peterson_acquire(i, 0);
        if(__sync_lock_test_and_set(&pLocks.locks[i].created, 0) == 0){
        __sync_synchronize();
        }
        //peterson_release(i, 0);
    }
  }