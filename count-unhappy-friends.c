
int rating[505][505];
int currentrating[505];

int unhappyFriends(int n, int**preferences, int preferencesSz, int*preferences0sz, int**pairs, int pairsSz, int*pairs0sz){
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < preferences0sz[i]; j++){
        rating[i][preferences[i][j]] = j;
      }
    }
    int ret = 0;
    for(int z=0;z<pairsSz;z++){int*out=pairs[z];
        currentrating[out[0]] = rating[out[0]][out[1]];
        currentrating[out[1]] = rating[out[1]][out[0]];
    }
    for(int z=0;z<pairsSz;z++){int*out=pairs[z];
        for(int i = 0; i < n; i++){
            if(i == out[0])
                continue;
            if(rating[out[0]][i] < currentrating[out[0]] && rating[i][out[0]] < currentrating[i]){
              ret++;
              break;
            }
        }
        for(int i = 0; i < n; i++){
            if(i == out[1])
                continue;
            if(rating[out[1]][i] < currentrating[out[1]] && rating[i][out[1]] < currentrating[i]){
              ret++;
              break;
            }
        }
        
    }
    return ret;
}
