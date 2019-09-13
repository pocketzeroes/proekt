#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum{ MAXNUM    = 20};
enum{ MAXPEOPLE = 9999};
int  n_val;
char *val_str[MAXNUM+1];
double val_f[MAXNUM+1];

int compute_decimals (char *s){
  char *p = strchr(s,'.');
  if (p == NULL)
    return 0;
  return (strlen(s) - (p-s) - 1);
}
long Round(double x){
  if (x < 0)
    return -Round(-x);
  return (long)(x+0.5);
}
void spr (char *s, double x, int deci){
  static double pow10[] = {1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0 };
  long v = Round(x*pow10[deci]);
  if (deci == 0)
    sprintf(s, "%ld", v);
  else {
    char buf[50], *p1 = s;
    int len, i;
    sprintf(buf, "%0*ld", deci+1, v);
    len = strlen(buf);
    for (i = 0;  i <= len; ++i){
      if (i+deci == len)
        *p1++ = '.';
      *p1++ = buf[i];
    }
  }
}
int ok_num (long x, long pop, int deci, char *res){
  double p = (double)x*100/(double)pop;
  char s[50];
  spr(s, p, deci);
  return (strcmp(res,s) == 0);
}
long compute_people (void){
  long people;
  int  n_deci = compute_decimals(val_str[1]);
  int  i;
  for (people = 1;  people <= MAXPEOPLE;  ++people) {
    int ok = 1;
    long min_sum = 0, max_sum = 0, n_min, n_max;
    for (i = 1;  i <= n_val;  ++i) {
      long n = Round(val_f[i]/100.0 * people);
      if (ok_num(n,people,n_deci,val_str[i]))
        ;
      else if (ok_num(n-1,people,n_deci,val_str[i]))
        n = n-1;
      else if (ok_num(n+1,people,n_deci,val_str[i]))
        n = n+1;
      else
        ok = 0;
      if (! ok)
        break;
      n_min = n_max = n;
      while (ok_num(n_min-1,people,n_deci,val_str[i]))
        --n_min;
      while (ok_num(n_max+1,people,n_deci,val_str[i]))
        ++n_max;
      min_sum += n_min;  max_sum += n_max;
    }
    if (ok && min_sum<=people && people<=max_sum)
      return people;
  }
  return 0;
}
int main (){
  int  n, i;
  long res;
  for (n = 1;  n <= MAXNUM;  ++n)
    val_str[n] = (char *) malloc(100);
  for (n = 1;  ;  ++n) {
    scanf("%d", &n_val);
    if (n_val == 0)
      break;
    for (i = 1;  i <= n_val;  ++i) {
      scanf("%s", val_str[i]);
      sscanf(val_str[i], "%lf", &val_f[i]);
    }
    res = compute_people();
    printf("Case %d: ", n);
    if (res == 0)
      printf("error\n");
    else
      printf("%ld\n", res);
  }
  return 0;
}
