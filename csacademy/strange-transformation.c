#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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

typedef long long ll;
int myfun(int x, pair*arr){
   *arr = newPair(0,0);
    while(x%2 == 0){
        x/=2;
        arr->first++;
    }
    while(x%3 == 0){
        x/=3;
        arr->second++;
    }
    return x;
}
int compare(const void*pa, const void*pb){
    pair*a=(pair*)pa; 
    pair*b=(pair*)pb; 
    if(a->first == b->first)
        return(a->second < b->second)?-1:1;
    return(a->first > b->first)?-1:1;
}
int main(){
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    if(a==b){
        puts("-1");
        return 0;
    }
    pair start,end;
    int inival = myfun(a, &start);
    int temp1  = myfun(b, &end);
    if(inival != temp1)
        return puts("-1")*0;
    pair arr[n+1];
    for(int i=0; i<n; i++){
        int x;
        scanf("%d", &x);
        if( myfun(x, &arr[i]) != inival)
            return puts("-1")*0;
    }
    qsort(arr, n, sizeof(pair), compare);
    if(start.first < end.first || start.second > end.second)
        return puts("-1")*0;
    if( n > 0 && ( (arr[0].first > start.first || arr[0].second < start.second) || (arr[n-1].first < end.first || arr[0].second > end.second)))
        return puts("-1")*0;
    for(int i=1; i<n; i++){
        if(arr[i-1].second > arr[i].second)
            return puts("-1")*0;
    }
    arr[n] = end;
    pair temp = start;
    printf("%d ", a);
    for(int i=0; i<n+1; i++){
        pair curr = arr[i];
        ll val = (ll)((pow(2,temp.first)*pow(3,temp.second))*inival);
        while(curr.first < temp.first){
            temp.first--;
            val/=2;
            printf("%d ", val);
        }
        while(curr.second > temp.second){
            temp.second++;
            val*=3;
            printf("%d ", val);
        }
    }
    puts("");
    return 0;
}
