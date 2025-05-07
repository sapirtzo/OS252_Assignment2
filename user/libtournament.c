int tournament_create(int processes){
    if((processes < 2 || processes > 16) || ((processes & (processes - 1)) != 0)){
        return -1;
    }

    int levels = 0;
    int role[processes];
    while((1 << levels) < processes) levels++;
    for(int p = 0; p < processes; p++){
        for(int l = 0; l < levels; l++){
            role[p] = (p & (1 << (levels - l - 1))) >> (levels - l - 1);
        }
    }
    return 0;
}

int tournament_acquire(void){
    //TODO
}

int tournament_release(void){
    //TODO
}