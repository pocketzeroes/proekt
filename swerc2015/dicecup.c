#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int*hist;

int sc_nextInt(){
    int i;
    scanf("%d", &i);
    return i;
}
void dice(int n, int m){
    int maxFreq = 0;
    hist = calloc(n+m+1, sizeof(int));
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++){
            hist[i+j]++;
            if(hist[i+j] > maxFreq)
                maxFreq = hist[i+j];
        }
    for(int s=2; s<=n+m; s++){
        if(hist[s] == maxFreq) 
            printf("%d\n", s);
    }
    free(hist);
}
int main(){
    int n = sc_nextInt();
    int m = sc_nextInt();
    dice(n, m);
    return 0;
}
