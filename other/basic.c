#include <stdio.h>

int i,j,k,m,n;
char buf[1000];

int state;
double base, val;

int v[256];

#define check(x) if (!(x)) {printf("no\n");goto bad;}

#define DSTART 1
#define DEC 2
#define BSTART 3
#define BASE 4
#define BDONE 5

main(){
   for (i=0;i<255;i++) v[i] = -1;
   for (i=0;i<=9;i++) v[i+'0'] = i;
   for (i=0;i<=5;i++) v[i+'a'] = i+10;
   scanf("%d",&n);
   gets(buf);
   while (n--) {
      if (!gets(buf)) {
         printf("Error - short input!\n"); 
         exit(1);
      }
      state = DSTART;
      val = base = 0;
      for (i=0;buf[i];i++) {
         char c = buf[i];
         switch(state) {
            case DSTART: {
               check(v[c] >=0 && v[c] <= 9);
               val = v[c];
               state = DEC;
               break;
            }
            case DEC: {
               if (c == '#') {
                  check(val >= 2 && val <= 16);
                  base = val;
                  val = 0;
                  state = BSTART;
                  break;
               }
               check (v[c] >= 0 && v[c] <= 9);
               val = val * 10 + v[c];
               break;
            }
            case BSTART: {
               check (v[c] >= 0 && v[c] < base);
               val = v[c];
               state = BASE;
               break;
            }
            case BASE: {
               if (c == '#') {
                  state = BDONE;
                  break;
               }
               check (v[c] >= 0 && v[c] < base);
               val = val * base + v[c];
               break;
           }
           case BDONE: {
              check (c == '#');
              check (val >=2 && val <= 16);
              base = val;
              val = 0;
              state = BSTART;
              break;
           }
        }
      }
      check(state == DEC || state == BDONE);
      printf("yes\n");
      bad:;
   }
   if (gets(buf)) printf("Error - excessinput!\n");
}
