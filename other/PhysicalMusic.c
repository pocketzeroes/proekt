#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MaxN = 100000};
int posInDTN[MaxN+1];
int posInSTN[MaxN+1];
bool physical[MaxN+1];

bool IntegerInRange (const char *variable, int val, int minVal, int maxVal){
  if (val>=minVal && val<=maxVal)
    return true;
  else{
    fprintf(stderr, "<< variable << << val <<  but should be in [ minVal << "," << maxVal << ");
    return false;
  }
}

int main (){
  int nInst, inst;
  int N,
      i,
      p,
      notSeen,
      nrPhysical;
  bool OK,
       increase;
  scanf("%d", &nInst);
  for (inst=1;inst<=nInst;inst++){
    scanf("%d", &N);
    for (p=1;p<=N;p++)
      posInSTN[p] = 0;
    for (i=1;i<=N;i++){
      scanf("%d", &p);
      if(IntegerInRange ("p", p, 1, N)){
        posInDTN[i] = p;
        posInSTN[p] = i;
      }
    }
    OK = true;
    for (p=1;p<=N;p++)
      OK = OK && IntegerInRange ("posInSTN", posInSTN[p], 1, N);
    if (OK){
      notSeen = 1;
      nrPhysical = 0;
      for (i=1;i<=N;i++){
        p = posInDTN[i];
        if (p==notSeen){
          physical [p] = false;
          increase = true;
          do{
            if (posInSTN[notSeen]<=i)
              notSeen ++;
            else
              increase = false;
          }
          while (increase && notSeen<=N);
        }
        else{
          physical[p] = true;
          nrPhysical ++;
        }
      }
      printf("%d\n", nrPhysical);
      for(p=1;p<=N;p++)
        if(physical[p])
          printf("%d\n", p);
    }
  }
  return 0;
}
