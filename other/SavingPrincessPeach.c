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

int main(){
    int size = in_nextInt();
    int numvalues = in_nextInt();
    int index = 0;
    int source[size];
    for(int i = 0; i<size; i++)
        source[i] = -1;
    int maxNum = 0;
    while(index < numvalues){
        int storage = in_nextInt();
        source[storage] = storage;
        index++;
    }
    int iteration = 0;
    for (int i = 0; i < size; i++){
        if (source[i] != -1){
            maxNum++;
            iteration++;
        }
        else{
            printf("%d\n", iteration);
            iteration++;
        }
    }
    printf("Mario got %d of the dangerous obstacles.\n", maxNum);
    return 0;
}
