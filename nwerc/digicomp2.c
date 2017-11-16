#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
bool state[1000005];
ll M, indeg[1000005], balls[1000005], cur, ende, succ[1000005][2], q[1000005];
char initial;

int main(){
  scanf("%lld %lld", &balls[1], &M);
  for(int i = (1); i < (M+1); i++){
    getchar();
    scanf("%c %lld %lld", &initial, &succ[i][0], &succ[i][1]);
    state[i] = initial == 'L';
    for(int j = (0); j < (2); j++)
      indeg[succ[i][j]]++;
  }
  for (int i = (1); i < (M+1); i++) 
    if (indeg[i] == 0) 
      q[ende++] = i;
  while (q[cur] != 0){
    int node = q[cur++];
    for (int j = (0); j < (2); j++){
      balls[succ[node][j]] += (balls[node] + (state[node] == 1-j))/2;
      indeg[succ[node][j]]--;
      if (indeg[succ[node][j]] == 0 && q[ende-1] != succ[node][j]) 
        q[ende++] = succ[node][j];
    }
    if (balls[node] % 2) 
      state[node] = !state[node];
  }
  for (int i = (1); i < (M+1); i++)
    printf("%c", (state[i] ? 'L' : 'R'));
  puts("");
  return 0;
}
