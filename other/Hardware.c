#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ndigits[10], sum_digits;
int debug = 0;

int count (int v1, int v2, int vincr){
  int v, sum = 0;
  for (v = v1;  v <= v2;  v += vincr) {
    int vx = v;
    ++sum;
    do {
      ++ndigits[vx%10];  ++sum_digits;
      vx /= 10;
    }
    while (vx > 0);
  }
  return sum;
}
int main(){
  char line[500];
  int n_orders, n;
  gets(line);
  n_orders = atoi(line);
  for (n = 1;  n <= n_orders;  ++n) {
    char address[500], addr_order[500];
    int done = 0, n_addr, i;
    for (i = 0;  i <= 9;  ++i)
      ndigits[i] = 0;
    sum_digits = 0;
    if (debug) 
      fprintf(stderr, "Order #%d:\n", n);
    gets(address);  
    gets(addr_order);
    n_addr = atoi(addr_order);
    while (done < n_addr) {
      gets(line);
      if (line[0] == '+') {
        int n1, n2, inc;
        sscanf(line+1, "%d%d%d", &n1, &n2, &inc);
        done += count(n1, n2, inc);
      }
      else {
        int n1 = atoi(line);
        done += count(n1, n1, 1);
      }
    } 
    printf("%s\n", address);
    printf("%s\n", addr_order);
    for (i = 0;  i <= 9;  ++i)
      printf("Make %d digit %d\n", ndigits[i], i);
    if (sum_digits!=1)
      printf("In total %d digits\n", sum_digits);
    else
      printf("In total %d digit\n", sum_digits);     
  }
  return 0;
}
