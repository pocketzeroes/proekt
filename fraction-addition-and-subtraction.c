#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
int gcd(int x, int y) {
  if (!y) {
    return x;
  }
  return gcd(y, x % y);
}
typedef struct F_s {
  int x, y;
}F;

F newF(int x, int y){
  F rez;
  rez.x=x;
  rez.y=y;
  return rez;
}

F normal(F f){
  int d = gcd(f.x, f.y);
  return newF(f.x / d, f.y / d);
}
F operatorAdd(F a, F t){
  F s;
  s.x = a.x * t.y + a.y * t.x;
  s.y = a.y * t.y;
  s = normal(s);
  return s;
}

char*fractionAddition(char*expression){
  int expression_size=strlen(expression);
  F ans=newF(0, 1);
  for(int i = 0; i < expression_size; ){
    char ch = expression[i];
    int sgn = 1;
    if (ch == '+' || ch == '-') {
      if (ch == '-') {
        sgn = -1;
      }
      ++i;
    }
    int x = 0;
    while (i < expression_size && isdigit(expression[i])) {
      x *= 10;
      x += expression[i] - '0';
      ++i;
    }
    ++i;
    int y = 0;
    while (i < expression_size && isdigit(expression[i])) {
      y *= 10;
      y += expression[i] - '0';
      ++i;
    }
    F t=newF(x, y);
    t.x *= sgn;
    normal(t);
    ans = operatorAdd(ans , t);
  }
  if (ans.y < 0) {
    ans.x = -ans.x;
    ans.y = -ans.y;
  }
  char*ptr=NULL;
  asprintf(&ptr,"%d/%d",ans.x,ans.y);
  return ptr;
}

















































