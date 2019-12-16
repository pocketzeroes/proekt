typedef struct{
}CombinationIterator;
CombinationIterator*gptr;

int a[100],n,m,i;
char*s;
char*ans;

CombinationIterator*combinationIteratorCreate(char*characters, int combinationLength){
    s = strdup(characters);
    n = strlen(s);
    m = combinationLength;
    for(i=0;i<m;i++)
        a[i]=i;
    a[m]=n;
    return gptr;
}
char*combinationIteratorNext(CombinationIterator*obj){
    ans = calloc(m+1, sizeof(char));
    for(i=0; i<m; i++)
        ans[i] = s[a[i]];
    for(i=m-1;~i;i--)
        if(a[i]+1!=a[i+1])
            break;
    if(!~i)
        a[0]=-1;
    else{
        a[i]++;
        for(i++;i<m;i++)
            a[i]=a[i-1]+1;
    }
    return ans;
}
bool combinationIteratorHasNext(CombinationIterator*obj){
    return a[0]!=-1;
}
void combinationIteratorFree(CombinationIterator* obj){
    free(s);
    free(ans);
}
