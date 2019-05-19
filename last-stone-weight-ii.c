enum{ MAX = 3005};

int lastStoneWeightII(int*stones, int stonesSz){
    int n = stonesSz;
    bool possible[2*MAX+1];memset(possible,0,sizeof(possible));
    possible[MAX] = true;
    for(int i=0;i<stonesSz;i++){int stone = stones[i];
        bool next_possible[2*MAX+1]; memset(next_possible, 0, sizeof(next_possible));
        for(int x = 0; x <= 2 * MAX; x++)
            if(possible[x])
                next_possible[x + stone] = next_possible[x - stone] = true;
        memcpy(possible, next_possible, sizeof(possible));
    }
    for(int i = 0; i <= MAX; i++)
        if(possible[MAX + i])
            return i;
    return -1;
}
