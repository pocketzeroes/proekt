#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

int main(){
  int n, k;
  scanf("%d\n%d", &n, &k);
  int obvious_matches = 0;
  int matched_already = 0;
  int unknown_cards   = 0;
  int single_cards    = 0;
  char*cards[n+1]; memset(cards, 0, sizeof(cards));
  for(int i=0; i<k; i++){
    int c1, c2;
    char*s1;
    char*s2;
    scanf("%d %d", &c1, &c2);
    s1 = getstr();
    s2 = getstr();
    if(strcmp(s1, s2)==0)
      matched_already++;
    cards[c1] = s1;
    cards[c2] = s2;
  }
  for(int i=1; i<=n; i++){
    bool found_match = false;
    if(cards[i] == NULL){
      unknown_cards++;
      continue;
    }
    for(int j=i+1; j<=n; j++){
      if(cards[i]&&cards[j])
        if(strcmp(cards[i], cards[j])==0){
          obvious_matches++;        
          found_match = true;
        }
    }
    if(!found_match)
      single_cards++;
  }
  single_cards -= obvious_matches;
  printf("%d\n", obvious_matches - matched_already + (single_cards == unknown_cards ? single_cards : 0) + ((single_cards == 0 && unknown_cards == 2) ? 1 : 0) );
  return 0;
}
