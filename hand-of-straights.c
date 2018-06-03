int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
typedef struct{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
//////////////////////
enum{ N = 10005};
pair s[N];

bool isNStraightHand(int*hand, int handSz, int W){
    qsort(hand, handSz, sizeof(int), cmp);
    int n = handSz;
    int k = 0;
    for(int i=0; i<n; i++){
        if(!i||hand[i] != hand[i-1])
            s[k++] = newPair(hand[i],1);
        else 
            s[k-1].second++;
    }
    for(int i=0;i<k;i++){
        while(s[i].second>0){
            if(i+W-1>=k)
                return false;
            for(int j=0; j<W; j++){
                if(s[i+j].first != s[i].first+j||s[i+j].second<=0)
                    return false;
                s[i+j].second--;
            }
        }
    }
    return true;
}
