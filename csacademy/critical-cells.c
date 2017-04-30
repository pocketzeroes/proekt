#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmpP(const void*pa, const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

pair arr[100005];
int L[100005],R[100005],ans[100005];

int upper_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}


int main(){
    int i,j,n,m,k,idx,s,c=0;
    scanf("%d %d %d",&k,&m,&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&arr[i].first,&arr[i].second);
    qsort(arr, n, sizeof(pair), cmpP);
    int*lis=NULL;int lisSz=0;
    for(i=0;i<n;i++){
        idx = upper_bound(lis, lisSz, arr[i].second);
        R[i] = idx+1;
        if(idx == lisSz)
            lis=pushback(lis, &lisSz, arr[i].second);
        else
            lis[idx] = arr[i].second;
    }
    lisSz=0;
    for(i=n-1;i>=0;i--){
        idx = upper_bound(lis, lisSz, -arr[i].second);
        L[i] = idx+1;
        if(idx == lisSz)
            lis=pushback(lis, &lisSz, -arr[i].second);
        else
            lis[idx] = -arr[i].second;
    }
    s = lisSz;
    for(i=0;i<n;i++)
        if(L[i]+R[i]-1 == s)
            ans[L[i]]++;
    for(i=0;i<100005;i++)
        if(ans[i]==1)
            c++;
    printf("%d\n", c);
    return 0;
}




