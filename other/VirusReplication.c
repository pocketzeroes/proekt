#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAX = 200000};

int main(){
 char b1[MAX], b2[MAX];
 gets(b1); gets(b2);
 int n1=strlen(b1),n2=strlen(b2);
 int mn,mx,p,r;
 for(mn=0;((mn<n1) && (mn<n2));mn++) if (b1[mn]!=b2[mn]) break;
    for(mx=0; ((mx<n1) && (mx<n2));mx++) if (b1[n1-1-mx]!=b2[n2-1-mx]) break;
 p=(mn+mx>n1)?n1:(mn+mx);
  if (p>=n2) r=0; else r=n2-p;
 printf("%d\n",r);
 return 0;
}
