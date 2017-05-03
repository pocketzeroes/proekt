#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int state[3][3];

int final( ) {
  int winner[] = {0, 0, 0};
  for(int i = 0; i < 3; i++) {
    if (state[i][0] == state[i][1] && state[i][1] == state[i][2])
      winner[state[i][1]]++;
    if (state[0][i] == state[1][i] && state[1][i] == state[2][i])
      winner[state[1][i]]++;
  }
  if (state[0][0] == state[1][1] && state[1][1] == state[2][2])
    winner[state[1][1]]++;
  if (state[0][2] == state[1][1] && state[1][1] == state[2][0])
    winner[state[1][1]]++;
  if (winner[1] > 0 && winner[2] > 0)
    return -1;
  else if (winner[1] > 0)
    return 1;
  else if (winner[2] > 0)
    return 2;
  else
    return 0;
}
int winner(int player) {
  int f = final(state);
  if (f == player)
    return -1;
  if (f != 0)
    return f;
  int moves = 0;
  int outcome[] = {0, 0, 0};
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if (state[i][j] == 0) {
        moves++;
        state[i][j] = player;
        outcome[winner( 3 - player)]++;
        state[i][j] = 0;
      }
  if (moves == 0)
    return 0;
  else if (outcome[player] > 0)
    return player;
  else if (outcome[0] > 0)
    return 0;
  else
    return 3 - player;
}
int ticTacToe(){
  int count[] = {0, 0, 0};
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if (0 <= state[i][j] && state[i][j] <= 2)
        count[state[i][j]]++;
      else
        return -1;
  if (count[1] == count[2])
    return winner( 1);
  else if (count[1] - 1 == count[2])
    return winner( 2);
  else
    return -1;
}
int main(){
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      scanf("%d", &state[i][j]);
    }
  }
  int rez = ticTacToe();
  printf("%d\n", rez);
  return 0;
}



























































