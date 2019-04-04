#include <stdio.h>
#include <string.h>

enum{ MAXLEN = 200};

int n;
char buf[MAXLEN+1];

int compare(char *A,int alen,char *B, int blen){
  int j=0;  
  while (j<alen && j<blen && A[j]==B[j])
    j++;
  if (j==alen){
    if (j==blen)
      return 0;
    else
      return -1;
  }
  else if (j==blen)
    return 1;
  else if (A[j]<B[j])
    return -1;
  else
    return 1;
}
int isNecklace(char *streng, int len){
  int i,j;
  int who=0;
  for (i=1;i<len && !who;i++){
    int a,b;
    j=0;
    a=who;
    b=i;
    while (j<len && streng[a]==streng[b]){
      j++;
      a=(a+1) % len;
      b=(b+1) % len; 
    } 
    if (j<len && streng[a]>streng[b])
      who=i;
  }
  return who==0;
}
void recp(char* streng,int* who,int where){
  int j;
  if (who[where]==-1)
    return;
  recp(streng,who,who[where]);
  printf("(");
  for (j=who[where];j<where;j++){
    printf("%c",streng[j]);
  }  
  printf(")");
}
void factor(char *streng,int len){
  int i,j;
  int dyn[MAXLEN+1];
  dyn[0]=-1;
  for (i=1;i<=len;i++)
    dyn[i]=0;
  for (i=0;i<len;i++){
    for (j=i;j>=0;j--){
      if (isNecklace(&streng[j],i-j+1)){
        if (dyn[j]==-1 || compare(&streng[dyn[j]],j-dyn[j]+1,&streng[j],i-j+1)==1){
          dyn[i+1]=j;  
        }
      }
    }    
  }
  recp(streng,dyn,len);
}
int main(){
  scanf("%d",&n);
  while(n--){
    scanf("%s",buf);
    factor(buf,strlen(buf));
    printf("\n");
  }
  return 0;
}
