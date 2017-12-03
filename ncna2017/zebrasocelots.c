#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef long long ll;

int main(){
  ll bits = 0;
  ll mask;
  int N,i;  
  int line = 0;
  int ch;
  ll count;
  if(scanf("%d",&N)!=1){
    perror("error reading N:");
    exit(1);
  }
  ++line;
  for(i=0;i<N;i++){
    ++line;
    while(isspace(ch = getchar()));
    if(ch != 'O' && ch != 'Z'){
      fprintf(stderr,"Line %d: ",line);
      perror("error reading animal: ");
      exit(2);
    }
    if(ch == 'O')
      bits |= (1LL << (N-i-1));
  }
  printf("%lld\n",bits);
  return 0;
}
