#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int n;
char*list;
int*cumfreq;
int*minfreq;

bool solve(){
  int min = cumfreq[0];
  for (int i=0; i<=n; i++)
    min = fmin(min, cumfreq[i]);
  if (min == 0 && cumfreq[n] == 0)
    return true;
  int curSum = cumfreq[n];
  for (int start=0; start<n; start++){
    if (cumfreq[start] <= -1) 
      break;
    if (cumfreq[start+1] <= 1 && list[start] == '(') 
      continue;
    int curChange = 0;
    for (int end=start; end<n; end++) {
      if (list[end] == '(')
        curChange -= 2;
      else
        curChange += 2;
      if (curChange+cumfreq[end+1] < 0) 
        break;
      if (2*(cumfreq[end+1]-cumfreq[start]) - curSum == 0) {
        if (minfreq[end+1]+curChange >= 0)
          return true;
      }
    }
  }
  return false;
}
int main(){
  list = getstr();
  n = strlen(list);
  cumfreq = calloc(n+1, sizeof(int));
  for(int i=1; i<=n; i++){
    if(list[i-1] == '(')
      cumfreq[i] = cumfreq[i-1] + 1;
    else
      cumfreq[i] = cumfreq[i-1] - 1;
  }
  minfreq = calloc(n+1, sizeof(int));
  minfreq[n] = cumfreq[n];
  for(int i=n-1; i>=0; i--)
    minfreq[i] = fmin(minfreq[i+1], cumfreq[i]);
  puts(solve()?"possible":"impossible");
  return 0;
}
