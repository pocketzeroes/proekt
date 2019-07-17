#include<stdio.h>
int coins, i, rc, result;
int runsum[1420];

int main(){
  runsum[1] = 2;
  for (i = 2; i < 1420; i++)
    runsum[i] = runsum[(i - 1)] + i + 1;
  while ((scanf ("%d", &coins)) == 1){
    if ((coins < 0)  ||  (coins > 1000000))
      fputs ("Coin input value out of range.\n", stderr);
    else if (!coins)
      break;
    else if (coins == 1)
      result = 0;
    else{
      result = 1;
      for (i = 2; runsum[i] <= coins; i++){
        if (!((coins - runsum[i]) % i))
          result++;
      }
    }
    printf ("%d\n", result);
  }
  return 0;
}
