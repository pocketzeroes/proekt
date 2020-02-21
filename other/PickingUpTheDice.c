#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef long long ll;
int bestcount, dicecount, difference, i, iocount, j, k, mindice;
int targetnum, thrownsum;
ll  bestodds, diceways;
int die[25], selected[25];
ll  odds[25][150], power6[25];

void abend (char *message){
  fputs (message, stderr);
  fputc ('\n', stderr);
  exit (4);
}
void checkrange(int value, int minvalue, int maxvalue, char*fault){
  if((value < minvalue) || (value > maxvalue)){
    fputs(fault, stderr);
    fputs(":  ", stderr);
    abend("Input value out of range!");
  }
  return;
}
void processdice(int k){
  int needed, i;
  int totalselected = 0;
  ll  theseodds;
  for (i = 0; i < k; i++)
    totalselected += die[selected[i]];
  needed = targetnum - (thrownsum - totalselected);
  if ((needed < k) || (needed > (6 * k)))
    return;
  theseodds = odds[k][needed];
  if (theseodds > bestodds){
    bestcount = k;
    bestodds = theseodds;
  }
  return;
}
int next_comb(int comb[], int k, int n){
  int i = k - 1;
  ++comb[i];
  while ((i > 0) && (comb[i] >= n - k + 1 + i)){
    --i;
    ++comb[i];
  }
  if (comb[0] > n - k)
    return (0);
  for (i = i + 1; i < k; ++i)
    comb[i] = comb[i - 1] + 1;
  return (1);
}
int main(){
  power6[0] = 1LL;
  for (i = 1; i < 25; i++)
    power6[i] = 6LL * power6[(i - 1)];
  iocount = scanf ("%d %d", &dicecount, &targetnum);
  if (iocount != 2)
    abend ("Missing initial parameters.");
  checkrange (dicecount, 2, 24, "Dice count");
  checkrange (targetnum, dicecount, (dicecount * 6), "Target number");
  odds[1][1] = odds[1][2] = odds[1][3] = odds[1][4] = odds[1][5] = odds[1][6] = 1LL;
  for (i = 2; i <= dicecount; i++){
    for (j = i; j <= ((i * 7) / 2); j++){
      diceways = 0LL;
      for (k = j - 1; ((k >= (j - 6)) && (k >= (i - 1))); k--)
        diceways += odds[(i - 1)][k];
      odds[i][((i * 7) - j)] = odds[i][j] = diceways;
    }
  }
  for (i = 1; i <= dicecount; i++){
    for (j = i; j <= ((i * 7) / 2); j++){
      odds[i][((i * 7) - j)] = odds[i][j] = odds[i][j] * power6[(24 - i)];
    }
  }
  thrownsum = 0;
  for (i = 0; i < dicecount; i++){
    iocount = scanf ("%d", &(die[i]));
    if (iocount != 1)
      abend ("Missing die value.");
    thrownsum += die[i];
  }
  if (thrownsum == targetnum)
    bestcount = 0;
  else{
    bestcount = 0;
    bestodds = 0LL;
    difference = abs (targetnum - thrownsum);
    mindice = difference / 5;
    if ((mindice * 5) < difference)
      mindice++;
    for (k = mindice; k <= dicecount; k++){
      for (i = 0; i < k; ++i)
        selected[i] = i;
      processdice (k);
      while (next_comb (selected, k, dicecount))
        processdice (k);
    }
  }
  printf ("%d\n", bestcount);
  return 0;
}
