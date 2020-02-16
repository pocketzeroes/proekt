#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef int* intp;
int cmpE(const void*pa, const void*pb){
    intp*pv1=(intp*)pa;
    intp*pv2=(intp*)pb;
    int*v1=*pv1;
    int*v2=*pv2;
    return(v1[1]==v2[1]?v1[0]<v2[0]:v1[1]<v2[1])?-1:1;
}
int maxEvents(int**events, int eventsSz, int*events0sz){
    qsort(events, eventsSz, sizeof(intp), cmpE);
    int res = 0;
    bool vis[100001]; clr(vis);
    for(int z=0; z<eventsSz; z++){intp v = events[z];
        for(int i=v[0]; i<=v[1]; i++){
            if(!vis[i]){
                vis[i]=true, res++;
                break;
            }
        }
    }
    return res;
}
