#include<stdio.h>
#include<string.h>

char *x[] = {
"WET","0",
"UTC","0",
"GMT","0",
"BST","+1",
"IST","+1",
"WEST","+1",
"CET","+1",
"CEST","+2",
"EET","+2",
"EEST","+3",
"MSK","+3",
"MSD","+4",
"AST","-4",
"ADT","-3",
"NST","-3.5",
"NDT","-2.5",
"EST","-5",
"EDT","-4",
"CST","-6",
"CDT","-5",
"MST","-7",
"MDT","-6",
"PST","-8",
"PDT","-7",
"HST","-10",
"AKST","-9",
"AKDT","-8",
"AEST","+10",
"AEDT","+11",
"ACST","+9.5",
"ACDT","+10.5",
"AWST","+8",
"",""};

int i,j,k,h,m,n,N,time;
char buf[100];
double off;

int main(){
   scanf("%d",&N);
   while (N--) {
      scanf(" %s",buf);
      if (!strcmp(buf,"noon")) time = 12*60;
      else if (!strcmp(buf,"midnight")) time = 0;
      else {
         sscanf(buf,"%d:%d",&h,&m);
         if (h == 12) h = 0;
         time = h*60 + m;
         scanf(" %s",buf);
         if (!strcmp(buf,"p.m.")) time += 12*60;
      }
      scanf(" %s",buf);
      for (i=0;*x[i] && strcmp(x[i],buf);i++);
      if (strcmp(x[i],buf)) printf("oops:  <<<%s>>>\n",buf);
      sscanf(x[i+1],"%lf",&off);
      time -= 60 * off; 
      scanf(" %s",buf);
      for (i=0;*x[i] && strcmp(x[i],buf);i++);
      if (strcmp(x[i],buf)) printf("oops:  %s\n",buf);
      sscanf(x[i+1],"%lf",&off);
      time += 60 * off; 
      time = (time + 24*60) % (24*60);
      if (time == 0) printf("midnight\n");
      else if (time == 12 * 60) printf("noon\n");
      else {
         h = time/60%12;
         if (h == 0) h = 12;
         m = time%60;
         printf("%d:%02d %s\n",h,m,time>12*60?"p.m.":"a.m.");
      }
   }
   return 0;
}
