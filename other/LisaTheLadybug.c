#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum{ RANGE =    1000};
enum{ INFTY = 1000000};
static unsigned numlen    [RANGE];
static unsigned to_process[RANGE];
static unsigned n_to_process;
static unsigned in_queue  [RANGE];
static unsigned curbest   [RANGE];
static unsigned what;
static unsigned whatbest;
static int      available[128];
const char      ops[4] = {'+', '-', '*', '/'};

static void record (unsigned sno, unsigned len){
  if (curbest[sno] <= len)
    return;
  curbest[sno] = len;
  if (!in_queue[sno]){
    in_queue[sno] = 1;
    to_process[n_to_process++] = sno;
  }
}
static int typable (unsigned num){
  if (num == 0)
    return available['0'];
  while (num){
    char dig = (num % 10) + '0';
    if (!available[(int) dig])
      return 0;
    num /= 10;
  }
  return 1;
}
static int operation (char op, unsigned n1, unsigned n2, unsigned *res){
  switch (op){
    case '+':
      if (n1 + n2 >= RANGE)
        return 0;
      *res = n1 + n2;
      return 1;
    case '-':
      if (n2 > n1)
        return 0;
      *res = n1 - n2;
      return 1;
    case '*':
      if (n1 * n2 >= RANGE)
        return 0;
      *res = n1 * n2;
      return 1;
    case '/':
      if (n2 == 0)
        return 0;
      *res = n1 / n2;
      return 1;
  }
  abort ();
}
static void progress (unsigned on_screen, unsigned len){
  int k;
  unsigned num, res;
  if (on_screen == what){
    if (whatbest > len + 1)
      whatbest = len + 1;
    return;
  }
  for (k = 0; k < 4; k++){
    if (!available[(int) ops[k]])
      continue;
    if (available['='] && operation (ops[k], on_screen, on_screen, &res)){
      record (res, len + 2);
      if (res == what && whatbest > len + 2)
        whatbest = len + 2;
    }
    for (num = 0; num < RANGE; num++)
      if (typable (num) && operation (ops[k], on_screen, num, &res))
        record (res, len + 1 + numlen[num]);
  }
}
static void progress_len (int len){
  unsigned sno;
  int i;
  for (i = 0; i < n_to_process; ){
    sno = to_process[i];
    if (curbest[sno] != len){
      i++;
      continue;
    }
    in_queue[sno] = 0;
    to_process[i] = to_process[--n_to_process];
    progress (sno, len);
  }
}
int main(){
  char znaky[100], *p;
  int i;
  unsigned num;
  for (i = 0; i < 10; i++) numlen[i] = 1;
  for (; i < 100; i++)     numlen[i] = 2;
  for (; i < 1000; i++)    numlen[i] = 3;
  while (scanf ("%s%d", znaky, &what) == 2){
    if (what == 0){
      printf ("0\n");
      continue;
    }
    memset (available, 0, sizeof (available));
    for (p = znaky; *p; p++)
      available[(int) *p] = 1;
    if (typable (what)){
      printf ("%d\n", numlen[what]);
      continue;
    }
    for (i = 0; i < 4; i++)
      if (available[(int) ops[i]])
        break;
    if (i == 4){
      printf ("impossible\n");
      continue;
    }
    for (i = 0; i < RANGE; i++){
      curbest[i] = INFTY;
      in_queue[i] = 0;
    }
    whatbest = INFTY;
    n_to_process = 0;
    record (0, 0);
    for (num = 1; num < RANGE; num++)
      if (typable (num))
        record (num, numlen[num]);
    for (i = 0; n_to_process != 0 && i < whatbest; i++)
      progress_len (i);
    if (whatbest < INFTY)
      printf ("%d\n", whatbest);
    else
      printf ("impossible\n");
  }
  return 0;
}
