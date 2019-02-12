#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char buff[100000];

int main(){
  int n;
  scanf("%d", &n);
  int day, month;
  int days[n]; memset(days, 0, sizeof(days));
  for(int i=0; i<n; i++){
    scanf("%s", &buff);
    scanf("%d-%d", &month, &day);
    days[i] = day - 1;
    for(int j = 0; j + 1 < month; j++)
      days[i] += months[j];
  }
  qsort(days, n, sizeof(int), cmp);
  int oct_28th = 27;
  for(int i = 0; i < 9; i++)
    oct_28th += months[i];
  int birthday = (days[0] + 364) % 365;
  if(n > 1){
    int longest_gap = (days[0] - days[n-1] + 365) % 365;
    for(int i = 0; i + 1 < n; i++){
      if(days[i+1] - days[i] > longest_gap || (days[i+1] - days[i] == longest_gap && (days[i+1] - 1 - oct_28th + 365) % 365 < (birthday - oct_28th + 365) % 365)){
        longest_gap = days[i+1] - days[i];
        birthday = (days[i+1] + 364) % 365;
      }
    }
  }
  int birthmonth = 0;
  while(months[birthmonth] <= birthday){
    birthday -= months[birthmonth];
    birthmonth++;
  }
  birthmonth++;
  birthday++;
  printf("%02d-%02d\n", birthmonth, birthday);
  return 0;
}
