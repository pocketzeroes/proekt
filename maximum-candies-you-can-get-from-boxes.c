int exist[1005], has[1005], o[1005];

int maxCandies(int*status, int statusSz, int*candies, int candiesSz, int**keys, int keysSz, int*keys0sz, int**containedBoxes, int containedBoxesSz, int*containedBoxes0sz, int*initialBoxes, int initialBoxesSz){
    int n = statusSz;
    int ans = 0;
    for(int i=0; i<n; i++){
        exist[i] = has[i] = 0;
        o[i] = status[i];
    }
    for(int z=0;z<initialBoxesSz;z++){int i = initialBoxes[z];
        has[i] = 1;
    }
    while(1){
        int cur=-1;
        for(int i=0; i<n; i++){
            if(!exist[i] && has[i] && o[i]){
                cur = i;
                break;
            }
        }
        if(cur == -1)
            break;
        ans += candies[cur];
        for(int z=0;z<containedBoxes0sz[cur];z++){int j = containedBoxes[cur][z];
            has[j] = true;
        }
        for(int z=0;z<keys0sz[cur];z++){int j = keys[cur][z];
            o[j] = true;
        }
        exist[cur] = 1;
    }
    return ans;
}
