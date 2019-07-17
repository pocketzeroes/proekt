#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MAX = 20};

typedef long long ll;

char in [7][MAX*6];
char out[7][MAX*6];

int codes[10] ={
  0b1110111,
  0b0100100,
  0b1011101,
  0b1101101,
  0b0101110,
  0b1101011,
  0b1111011,
  0b0100101,
  0b1111111,
  0b1101111
};

int GetCode(int c0){
  int code = 0;
  if (in[0][c0 + 2] == 'x') code |= 0b0000001;
  if (in[1][c0 + 0] == 'x') code |= 0b0000010;
  if (in[2][c0 + 4] == 'x') code |= 0b0000100;
  if (in[3][c0 + 2] == 'x') code |= 0b0001000;
  if (in[4][c0 + 0] == 'x') code |= 0b0010000;
  if (in[5][c0 + 4] == 'x') code |= 0b0100000;
  if (in[6][c0 + 2] == 'x') code |= 0b1000000;
  return code;
}
ll Input(){
  static int pos = 0;
  ll result = 0;
  for (;;){
    int code = GetCode(pos++ * 6);
    bool is_digit = false;
    for(int digit = 0; digit < 10; ++digit){
      if(codes[digit] == code){
        result = result * 10 + digit;
        is_digit = true;
      }
    }
    if (!is_digit)
      break;
  }
  return result;
}
void Draw(int code, int c0){
  for (int r = 0; r < 7; ++r){
    for (int c = 0; c < 5; ++c){
      out[r][c0 + c] = '.';
    }
  }
  if (code & 0b0000001) for (int c = 0; c < 5; ++c) out[0][c0 + c] = 'x';
  if (code & 0b0000010) for (int r = 0; r < 4; ++r) out[r][c0 + 0] = 'x';
  if (code & 0b0000100) for (int r = 0; r < 4; ++r) out[r][c0 + 4] = 'x';
  if (code & 0b0001000) for (int c = 0; c < 5; ++c) out[3][c0 + c] = 'x';
  if (code & 0b0010000) for (int r = 3; r < 7; ++r) out[r][c0 + 0] = 'x';
  if (code & 0b0100000) for (int r = 3; r < 7; ++r) out[r][c0 + 4] = 'x';
  if (code & 0b1000000) for (int c = 0; c < 5; ++c) out[6][c0 + c] = 'x';
}
void Output(ll number){
  vec digits = newVec();
  while(number){
    digits.ptr = pushback(digits.ptr, &digits.sz, number%10);
    number /= 10;
  }
  reverse(digits.ptr, 0, digits.sz-1);
  for (int i = 0; i < digits.sz; ++i){
    if (i){
      for (int r = 0; r < 7; ++r)
        out[r][i * 6 - 1] = '.';
    }
    Draw(codes[digits.ptr[i]], i * 6);
  }
  for (int r = 0; r < 7; ++r)
    printf("%s\n", out[r]);
}
int main(){
  for (int r = 0; r < 7; ++r)
    scanf("%s", in[r]);
  ll a = Input();
  ll b = Input();
  Output(a + b);
  return 0;
}
