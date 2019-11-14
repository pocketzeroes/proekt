#include<stdio.h>
#include<string.h>
#include<ctype.h>

char a[1000],
     b[1000];
int na,nb,i,j,k,m,n,c;
char *pa, *pb, aa[100][100],
               bb[100][100];

int main(){
  scanf("%d ",&c);
  while (c--) {
    gets(a);
    gets(b);
    na = nb = 0;
    for (pa = strtok(a," ");pa;pa = strtok(NULL," ")){
      if (*pa == '<')
        *pa = '0';
      strcpy(aa[na++],pa);
    }
    for (pb = strtok(b," ");pb;pb = strtok(NULL," ")){
      if (*pb == '<')
        *pb = '1';
      strcpy(bb[nb++],pb);
    }
    if (na != nb) {
      printf("-\n");
      continue;
    }
    for (i=0;i<na;i++){
      if (isdigit(aa[i][0])){
        for (j=0;j<na;j++)
          if (!strcmp(bb[j],aa[i]))
            strcpy(bb[j],bb[i]);
        for (j=i+1;j<na;j++)
          if (!strcmp(aa[j],aa[i]))
            strcpy(aa[j],bb[i]);
        for (j=0;j<=i;j++)
          if (!strcmp(aa[j],aa[i]))
            strcpy(aa[j],bb[i]);
      }
      else if (isdigit(bb[i][0])) {
        for (j=0;j<na;j++)
          if (!strcmp(aa[j],bb[i]))
            strcpy(aa[j],aa[i]);
        for (j=i+1;j<na;j++)
          if (!strcmp(bb[j],bb[i]))
            strcpy(bb[j],aa[i]);
        for(j=0;j<=i;j++)
          if(!strcmp(bb[j],bb[i]))
            strcpy(bb[j],aa[i]);
      }
      else if (strcmp(aa[i],bb[i])){
        printf("-\n");
        goto dun;
      }
    }
    for (i=0;i<na;i++) {
      if (i)
        printf(" ");
      if (isdigit(aa[i][0]))
        printf("x");
      else
        printf("%s",aa[i]);
    }
    printf("\n");
  dun:;
  }
  if (gets(a))
    printf("Extra input!\n");
  return 0;
}
