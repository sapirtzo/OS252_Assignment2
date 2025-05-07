#define PETERSON_LOCKS 15

struct petersonlock{
    volatile int flag[2];
    volatile int turn;
    unsigned int created;
};

struct petersonlocks {
    struct petersonlock locks[PETERSON_LOCKS];
};

extern struct petersonlocks pLocks;

void initPeterson(void);
int peterson_acquire(int lock_id, int role);
int peterson_release(int lock_id, int role);