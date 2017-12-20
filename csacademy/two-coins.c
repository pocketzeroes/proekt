#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n;
    int cnt=0;
    int k=0;
    int arr[10];
    int sum[100]={0};
    int freq[100]={0};
    scanf("%d", &n);
    for(int i=0;i<n;i++)
      scanf("%d", &arr[i]);
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            sum[k++] = arr[i]+arr[j];
    for(int i=0;i<100;i++)
        freq[sum[i]]++;
    for(int i=0;i<100;i++){
        if(freq[i]>=1)
          cnt++;
    }
    printf("%d\n", cnt-1);
    return 0;
}
