#include "types.h"
#include "petersonlock.h"

void initPeterson(void){
    for(int i = 0; i < PETERSON_LOCKS; i++){
        peterson_acquire(i, 0);
        pLocks.locks[i].created = 0;
        peterson_release(i, 0);
    }
  }