#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

const int inf = 0x3f3f3f3f;
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
int main() {
    int n;
    scanf("%d", &n);
    int elements[n];
    for (int i = 0; i < n; i += 1) {
        int x;
        scanf("%d ", &x);
        elements[i]= x;
    }
    int mn = min_element(elements, n);
    int mx = max_element(elements, n);
    int last_min = -inf, last_max = - inf / 2;
    int result = +inf;
    for (int i = 0; i < n; i ++) {
        if (elements[i] == mn) 
            last_min = i;
        if (elements[i] == mx) 
            last_max = i;
        result = min(result, abs(last_min - last_max) + 1);
    }
    printf("%d", result);
    return 0;
}
