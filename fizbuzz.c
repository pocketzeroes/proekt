#include <stdio.h>

char** fizzBuzz(int n, int* returnSize)
{
  char**masiv=malloc(n*sizeof(char*));
  int   masivLen=0;
  char buff[32];
  for (int i = 1; i <= n; ++i) {
    if      (i % 15== 0) masiv[masivLen++]=strdup("FizzBuzz");
    else if (i % 3 == 0) masiv[masivLen++]=strdup("Fizz");
    else if (i % 5 == 0) masiv[masivLen++]=strdup("Buzz");
    else { sprintf(buff,"%d", i);masiv[masivLen++]=strdup(buff);}
  }
  
  *returnSize=masivLen;
  return masiv;
}
