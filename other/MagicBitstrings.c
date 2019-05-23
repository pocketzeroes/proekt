#include<stdio.h>
#include<assert.h>
#include<math.h>

enum{MAXP = 100000};
char A[MAXP+10];

int isPrime(int a){
  if (a < 2) 
    return 0;
  for (int i = 2; i <= sqrt((double)a); i++) 
    if (!(a%i)) 
      return 0;
  return 1;
}
int main (){
  while (1){
    int p;
    scanf("%d", &p);
    if (!p) 
      break;
    assert(isPrime(p) && p <= MAXP);
    if (p == 2) {
      printf("Impossible\n");
      continue;
    }
    for (int i=1;i<p;i++)
      A[i] = '1';
    for (unsigned long long i=1;i<p;i++)
      A[(i*i)%p]='0';
    for (int i=1;i<p;i++)
      printf("%c",A[i]);
    printf("\n");
  }
  return 0;
}
