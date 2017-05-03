#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int min_element(int*arr,int sz){
    int mine=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]<mine)
            mine=arr[i];
    return mine;
}
int max_element(int*arr,int sz){
    int maxe=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]>maxe)
            maxe=arr[i];
    return maxe;
}

///////////////
int n;
vec v;

void read(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        v.ptr=pushback(v.ptr, &v.sz, val);
    }
}
int main(){
    read();
    int minVal = min_element(v.ptr, v.sz);
    int maxVal = max_element(v.ptr, v.sz);
    if (maxVal == minVal) {
        puts("0");
        return 0;
    }
    double bucketSize = ((double)maxVal - minVal) / n;
    vec buckets[n];
    memset(buckets, 0, sizeof(buckets));
    for(int i=0;i<v.sz;i++){
        int val = v.ptr[i];
        int bucketIndex = (int)(((double)val - minVal) / bucketSize);
        if (bucketIndex == n) {
            --bucketIndex;
        }
        buckets[bucketIndex].ptr=pushback(buckets[bucketIndex].ptr, &buckets[bucketIndex].sz,val);
    }
    long long best = 0;
    int lastMaxVal;
    for (int i = 0; i < n; ++i) {
        if (buckets[i].sz==0){
            continue;
        }
        int bucketMinVal = min_element(buckets[i].ptr, buckets[i].sz);
        int bucketMaxVal = max_element(buckets[i].ptr, buckets[i].sz);
        if(i > 0){
            best = max(best, (long long)bucketMinVal - lastMaxVal);
        }
        lastMaxVal = bucketMaxVal;
    }
    printf("%lld\n", best);
}



























































