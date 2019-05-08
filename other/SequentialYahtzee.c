#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
///////////////////////////////////////

int Category_Score(int*dice, int dice_sz, int category){
  int counts[7] = {0};
  int sum = 0;
  for(int i = 0; i < dice_sz; i++){
    sum = sum + dice[i];
    counts[dice[i]]++;
  }
  if(category < 6)
    return (category+1)* counts[category+1];
  if(category == 6){
    for(int i = 1; i <=6; i++)
      if(counts[i] >=3)
        return sum;
    return 0;
  }
  if(category == 7){
    for(int i = 1; i <=6; i++)
      if(counts[i] >=4)
        return sum;
    return 0;
  }
  if(category == 8){
    for(int i = 1; i <= 6; i++){
      for(int j = 1; j <=6; j++){
        if(i != j && counts[i] == 3 && counts[j] == 2)
          return 25;
      }
    }
    return 0;
  }
  if(category == 9){
    if((counts[1] > 0 && counts[2] > 0 && counts[3] > 0 && counts[4] > 0)||
       (counts[2] > 0 && counts[3] > 0 && counts[4] > 0 && counts[5] > 0)||
       (counts[3] > 0 && counts[4] > 0 && counts[5] > 0 && counts[6] > 0)  )
          return 30;
    else
      return 0;
  }
  if(category == 10){
    if((counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1)||
       (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1 && counts[6] == 1)  )
         return 40;
    else
      return 0;
  }
  if(category == 11)
    return sum;
  if(category == 12){
    for(int i = 0; i <=6; i++)
      if(counts[i] == 5)
        return 50;
    return 0;
  }
}
void Sort(int*v, int vsz){
  for(int i = 0; i < vsz; i++){
    for(int j = 0; j < vsz-1; j++){
      if(v[j] > v[j+1]){
        int temp = v[j];
        v[j] = v[j+1];
        v[j+1] = temp;
      }
    }
  }
}
int Locked_Combo(int*dice, int dice_sz, int which_combo){
  int result = 0;
  Sort(dice, dice_sz);
  int factor = 16;
  int pos = 4;
  while(factor > 0){
    if(which_combo > factor){
      which_combo = which_combo - factor;
      result = result*10 + dice[pos];
    }
    factor = factor/2;
    pos--;
  }
  return result;
}
int Play(int*rolls, int rolls_sz, int****Memo, int category, int num_reroll, int next_die, int locked_dice){
  if(category >= 13)
    return 0;
  if(next_die >= rolls_sz)
     return -2;
  if(Memo[category][num_reroll][next_die][locked_dice] != -1)
    return Memo[category][num_reroll][next_die][locked_dice];
  int cur_next_die = next_die;
  int dice[5];
  if(num_reroll == 0){
    if(next_die+4 >= rolls_sz)
      return -2;
    for(int i = 0; i < 5; i++){
      dice[i] = rolls[next_die+i];
    }
    cur_next_die = next_die + 5;
  }
  else{
    int i = 0;
    int temp = locked_dice;
    while(temp > 0){
      dice[i] = temp%10;
      i++;
      temp = temp/10;
    }
    while(i < 5){
      if(cur_next_die >= rolls_sz)
        return -2;
      dice[i] = rolls[cur_next_die];
      cur_next_die++;
      i++;
    }
  }
  int cur_score = Category_Score(dice, 5, category);
  int rest_score = Play(rolls, rolls_sz, Memo, category+1, 0, cur_next_die, 0);
  int best_score;
  if(rest_score < 0)
    best_score = -2;
  else
    best_score = cur_score + rest_score;
  if(num_reroll < 2){
    for(int i = 0; i < 32; i++){
      int new_locked = Locked_Combo(dice, 5, i);
      int new_score = Play(rolls, rolls_sz, Memo, category, num_reroll+1, cur_next_die, new_locked);
      if(new_score > 0 && new_score > best_score)
        best_score = new_score;
    }
  }
  Memo[category][num_reroll][next_die][locked_dice] = best_score;
  return best_score;
}
int main(){
  int num_dice;
  scanf("%d", &num_dice);
  int rolls[num_dice];
  for(int i = 0; i < num_dice; i++)
    scanf("%d", &rolls[i]);
  int max_score;
//int Memo[13][3][num_dice][6667];
  int****Memo = calloc(13,sizeof(int***));
  for(int i = 0; i < 13; i++){
    Memo[i] = calloc(3, sizeof(int**));
    for(int j = 0; j < 3; j++){
      Memo[i][j] = calloc(num_dice, sizeof(int*));
      for(int k = 0; k < num_dice; k++){
        Memo[i][j][k] = calloc(6667, sizeof(int));
        fill(Memo[i][j][k], 6667, -1);
      }
    }
  }
  max_score = Play(rolls, num_dice, Memo, 0, 0, 0, 0);
  printf("%d\n", max_score);
  return 0;
}
