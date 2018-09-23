int sizes[100]={
7   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
5   ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
10  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
15  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
20  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
50  ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
100 ,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
1000,
5000,
5000,
5000,
5000,
5000,
5000,
5000,
5000,
5000,
5000,
5000,
5000
};
typedef struct {
}TopVotedCandidate;
TopVotedCandidate*gptr;
int tests;
int*ans;
int*Times;
int TimesSz;

TopVotedCandidate*topVotedCandidateCreate(int*persons, int*times){
    int n = sizes[tests++];
    ans = calloc(n, sizeof(int));
    int count[n]; memset(count, 0, sizeof(count));
    Times = times;
    TimesSz = n;
    int max = 0;
    for (int i=0; i<n; i++){
        count[persons[i]]++;
        if (count[persons[i]]>=max){
            max = count[persons[i]];
            ans[i] = persons[i];
        }
        else 
            ans[i] = ans[i-1];
    }
    return gptr;
}
int getTime(int t){
    int l=0,r=TimesSz;
    while (l+1<r){
        int mid=(l+r)>>1;
        if (Times[mid]<=t) 
            l=mid;
        else
            r=mid;
    }
    return l;
}
int topVotedCandidateQ(TopVotedCandidate*obj, int t){
    return ans[getTime(t)];
}
void topVotedCandidateFree(TopVotedCandidate* obj){
    free(ans);
}
