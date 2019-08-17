#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

unsigned countl(char *s){
   unsigned r;
   if (strlen(s) == 1) return 1;
   if (s[0] == '0') {
      sscanf(s+1, "%u", &r);
      return 1 + r + countl(s+1);
   }
   r = pow(10,strlen(s+1));
   r += (s[0]-'0') * strlen(s+1) * pow(10,strlen(s+1)-1);
   r += countl(s+1);
   return r;
}

unsigned count(char *s){
   unsigned r = 1; char tmp[20];
   if (strlen(s) == 1) return 1;
   for (r=0;r<strlen(s)-1;r++) tmp[r] = '9';
   tmp[r] = 0;
   r = count(tmp);
   r += (s[0]-'1') * strlen(s+1) * pow(10,strlen(s+1)-1);
   r += countl(s+1);
   return r;
}

char x[100], y[100];
unsigned u;

int main(){
   while (2 == scanf("%s%s",x,y) && x[0] != '-') {
      if (x[0] == '0') printf("%u\n",count(y));
      else {
         sscanf(x,"%u",&u);
         sprintf(x,"%u",u-1);
         printf("%u\n",count(y)-count(x));
      }
   }
   return 0;
}
