#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int l;
int L[3];
int works = 0;

void backTrack(int index, int*count){
    if (index == 3){
        int total = 0;
        for (int i = 0; i < 3; i++)
            total += count[i] * L[i];
        if (total == l) {
            works++;
            for (int i = 0; i < 3; i++)
                printf("%d ", count[i]);
            puts("");
        }
    }
    else{
        for(int j = 0; j <= 250; j++){
            count[index] = j;
            backTrack(index + 1, count);
        }
    }

}
int main(){
    L[0] = in_nextInt();
    L[1] = in_nextInt();
    L[2] = in_nextInt();
    l    = in_nextInt();
    int count[3]={0};
    backTrack(0, count);
    if(works == 0)
        return puts("impossible")*0;
    return 0;
}
