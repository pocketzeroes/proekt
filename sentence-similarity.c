bool areSentencesSimilar(char**words1, int words1Sz, char**words2, int words2Sz, char***pairs, int pairsSz, int pairs0sz){
    if(words1Sz != words2Sz)
        return false;
    int n = words1Sz;
    for(int i = 0; i < n; i++){
        if(strcmp(words1[i], words2[i]) == 0)
            continue;
        bool ok = false;
        for(int z=0; z<pairsSz; z++){char**p = pairs[z];
            if(strcmp(words1[i], p[0]) == 0 && 
               strcmp(words2[i], p[1]) == 0   ){
                ok = true;
                break;
            }
            if(strcmp(words1[i], p[1]) ==0 && 
               strcmp(words2[i], p[0]) ==0   ){
                ok = true;
                break;
            }
        }
        if(!ok)
            return false;
    }
    return true;
}
