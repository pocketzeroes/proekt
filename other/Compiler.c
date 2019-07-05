#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

char reVal(int num){
  if (num >= 0 && num <= 9)
    return (char)(num + '0');
  else
    return (char)(num - 10 + 'A');
}
void strev(char *str){
  int len = strlen(str);
  int i;
  for (i = 0; i < len/2; i++){
    char temp = str[i];
    str[i] = str[len-i-1];
    str[len-i-1] = temp;
  }
}
char*fromDeci(char res[], int base, int inputNum){
  int index = 0;
  while (inputNum > 0){
    res[index++] = reVal(inputNum % base);
    inputNum /= base;
  }
  res[index] = '\0';
  strev(res);
  return res;
}

void getInstructions(int n){
  char base3[100];
  fromDeci(base3, 3, n);
  if(n == 0)
    puts("ZE A");
  else if(base3[0] == '2'){
    bool first = true;
    puts("ST X");
    puts("PH X");
    puts("PH X");
    puts("AD");
    puts("PL Y");
    puts("PH Y");
    puts("PL A");
    for(int z=0; base3[z]; z++){char digit = base3[z];
      if(first)
        first = false;
      else{
        puts("PH A");
        puts("PH A");
        puts("PH A");
        puts("AD");
        puts("AD");
        if(digit == '1'){
          puts("PH X");
          puts("AD");
        }
        else if(digit == '2'){
          puts("PH Y");
          puts("AD");
        }
        puts("PL A");
      }
    }
  }
  else{
    bool yStored = false;
    bool first = true;
    puts("ST X");
    puts("ST A");
    for(int z=0; base3[z]; z++){char digit = base3[z];
      if(first)
        first = false;
      else{
        puts("PH A");
        puts("PH A");
        puts("PH A");
        puts("AD");
        if(!yStored){
          puts("PL Y");
          puts("PH Y");
          yStored = true;
        }
        puts("AD");
        if(digit == '1'){
          puts("PH X");
          puts("AD");
        }
        else if(digit == '2'){
          puts("PH Y");
          puts("AD");
        }
        puts("PL A");
      }
    }
  }    
  puts("DI A");
}
int main(){
  int n = in_nextInt();
  getInstructions(n);
  return 0;
}
