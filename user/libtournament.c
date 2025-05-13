#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROCESSES 16
#define MAX_LEVELS 4  // since log2(16) = 4

int levels = 0; // L = log2(N)
int process_index; // Index of the current process (0 to N-1)
int roles[MAX_PROCESSES-1]; // Role at each level for current process
int* locks = 0; 

int tournament_create(int processes){
    if((processes < 2 || processes > MAX_PROCESSES) || ((processes & (processes - 1)) != 0)){
        return -1;
    }

    locks = (int*)malloc((processes-1) * sizeof(int));
    if(!locks){
        free(locks);
        return -1;
    }

    while((1 << levels) < processes) levels++;
    

    for(int lock_index = 0; lock_index < processes - 1; lock_index++){
        locks[lock_index] =  peterson_create();
        if(locks[lock_index] == -1){
            free(locks);
            return -1;
        }
    }
    
    for(int index = 0; index < processes - 1 ; index++){
        int pid = fork();
        if(pid < 0){
            free(locks);
            return -1;
        }
        // child procecss
        if(pid == 0){
            process_index = index + 1;
            return process_index;
        }
    }
    // The parent is always 0 - root
    return 0;
}

int tournament_acquire(void){
    if(process_index < 0 || !locks){
        free(locks);
        return -1;
    }

    for(int lvl = levels -1; lvl >= 0; lvl--){
        int lock_lvl = process_index >> (levels - lvl);
        int i = lock_lvl + (1 << lvl) - 1;
        int role = (process_index & (1 << (levels - lvl - 1))) >> (levels - lvl -1);

        if(peterson_acquire(locks[i], role) < 0){
            free(locks);
            return -1;
        }
    }

    return 0;
}

int tournament_release(void){
    if(process_index < 0 || !locks){
        free(locks);
        return -1;
    }

    for(int lvl = 0; lvl < levels; lvl++){
        int lock_lvl = process_index >> (levels - lvl);
        int i = lock_lvl + (1 << lvl) - 1;
        int role = (process_index & (1 << (levels - lvl - 1))) >> (levels - lvl -1);

        if(peterson_release(locks[i], role) < 0){
            free(locks);
            return -1;
        }
    }

    return 0;
}