#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


int n;
int*v=NULL;int vSz=0;

void read(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        v = pushback(v, &vSz, val);
    }
}
int minValue(){
    int res = v[0];
    for(int i=0;i<vSz;i++){ int val = v[i];
        res = min(res, val);
    }
    return res;
}
int maxValue(){
    int res = v[0];
    for(int i=0;i<vSz;i++){ int val = v[i];
        res = max(res, val);
    }
    return res;
}
void solve() {
    int minVal = minValue();
    int maxVal = maxValue();
    int start, end = - 1;
    int minCount = 0, maxCount = 0;
    int best = -1;
    for (start = 0; start < n; ++start) {
        while ((end + 1 < n) && (minCount == 0 || maxCount == 0)) {
            ++end;
            if (v[end] == minVal) 
                ++minCount;
            if (v[end] == maxVal) 
                ++maxCount;
        }
        if (minCount && maxCount) {
            if (best == -1 || (end - start + 1 < best)) 
                best = end - start + 1;
        }
        if (v[start] == minVal) 
            --minCount;
        if (v[start] == maxVal) 
            --maxCount;
    }
    printf("%d\n", best);
}
int main() {
    read();
    solve();
}




























