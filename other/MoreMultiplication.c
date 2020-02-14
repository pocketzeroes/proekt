#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void printChars(char c, int num2print){
  int i;
  for(i=0; i<num2print; i++)
    putchar(c);
}
void printLine(int numXdig){
  printf("| +");
  for(int j=0; j < numXdig; j++){
    printChars('-', 3);
    putchar('+');
  }
  printf(" |\n");
}
int main(){
  int X, Y, i, j, result, numXdigits, numYdigits, numRdigits;
  int Xdigits[5], Ydigits[5], Rdigits[10];
  bool firstDigitZero;
  scanf("%d %d", &X, &Y);
  while(X > 0){
    for(i=1, numXdigits=0; i<=X; i*=10)
      numXdigits++;
    for(i=1, numYdigits=0; i<=Y; i*=10)
      numYdigits++;
    for(i=0, j=X; j>0; i++){
      Xdigits[i] = j%10;
      j /= 10;
    }
    for (i=0, j=Y; j>0; i++){
      Ydigits[i] = j%10;
      j /= 10;
    }
    result = X*Y;
    for(i=1, numRdigits=0; i<=result; i*=10)
      numRdigits++;
    for(i=0, j=result; j>0; i++){
      Rdigits[i] = j%10;
      j /= 10;
    }
    putchar('+');
    printChars('-', 3+4*numXdigits);
    puts("+");
    printf("|   ");
    for(i=0; i<numXdigits; i++){
      printf("%d", Xdigits[numXdigits-i-1]);
      printChars(' ', 3);
    }
    puts("|");
    firstDigitZero = false;
    printLine(numXdigits);
    for(i=numYdigits-1; i>=0; i--){
      int topDigit, botDigit;
      if(i==numYdigits-1)
        if((Xdigits[numXdigits-1]*Ydigits[i]) /10 <= 0)
          firstDigitZero = true;
      if(i==numYdigits-1 || (i==numYdigits-2 && firstDigitZero))
        printf("| |");
      else
        printf("|/|");
      for(j=numXdigits-1; j>=0; j--){
        topDigit = Xdigits[j]*Ydigits[i] / 10;
        printf("%d /|", topDigit);
      }
      puts(" |");
      printf("| |");
      for(j=numXdigits-1; j>=0; j--)
        printf(" / |");
      printf("%d|\n", Ydigits[i]);
      putchar('|');
      if((i == numYdigits-1) && firstDigitZero)
        printf(" |");
      else
        printf("%d|", Rdigits[i+numXdigits]);
      for(j=numXdigits-1; j>=0; j--){
        botDigit = Xdigits[j]*Ydigits[i] % 10;
        printf("/ %d|", botDigit);
      }
      puts(" |");
      printLine(numXdigits);
    }
    putchar('|');
    for(i=0; i<numXdigits; i++){
      if(firstDigitZero && numYdigits == 1)
        printf("  ");
      else
        printf("/ ");
      printf("%d ", Rdigits[numXdigits-i-1]);
    }
    puts("   |");
    putchar('+');
    printChars('-', 3+4*numXdigits);
    puts("+");
    scanf("%d %d", &X, &Y);
  }
  return 0;
}
