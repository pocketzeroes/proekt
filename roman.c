#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int romanToInt(char* s){
    int*nums = malloc(strlen(s)*sizeof(int));
    for(int i=0; i<strlen(s) ;i++){
        switch ( s[i] ){
            case 'M':     nums[i]=1000; break;
            case 'D':     nums[i]= 500; break;
            case 'C':     nums[i]= 100; break;
            case 'L':     nums[i]=  50; break;
            case 'X':     nums[i]=  10; break;
            case 'V':     nums[i]=   5; break;
            case 'I':     nums[i]=   1; break;
        }
    }
    int sum=0;
    for(int i=0; i < strlen(s) - 1; i++){
        if(nums[i]<nums[i+1])
            sum-=nums[i];
        else
            sum+=nums[i];
    }
    return sum+nums[strlen(s)-1];
}

int main(){
  printf("result is [%d]\n", romanToInt ("MMXIV"));
  return 0;
}


