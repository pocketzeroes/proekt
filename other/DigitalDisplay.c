#include<stdio.h>
#include<string.h>
#include<ctype.h>
enum{DIGITW=5,
     DIGITH=7,
     GAPW=2,
     DOTW=1,
     SCREENW=4*DIGITW+4*GAPW+DOTW,
     DOT_COLUMN=DIGITW+GAPW+DIGITW+GAPW};
int cols[4]={0,
         DIGITW+GAPW,
         DIGITW+GAPW+DIGITW+GAPW+DOTW+GAPW,
         DIGITW+GAPW+DIGITW+GAPW+DOTW+GAPW+DIGITW+GAPW
      };
char screen[DIGITH][SCREENW+1];
char dot[DIGITH][DOTW+1]={" ",
                  " ",
                  "o",
                  " ",
                  "o",
                  " ",
                  " "};
char digits[10][DIGITH][DIGITW+1]=
 {{"+---+",
  "|   |",
  "|   |",
  "+   +",
  "|   |",
  "|   |",
  "+---+"},
  {"    +",
  "    |",
  "    |",
  "    +",
  "    |",
  "    |",
  "    +"},
  {"+---+",
  "    |",
  "    |",
  "+---+",
  "|    ",
  "|    ",
  "+---+"},
  {"+---+",
  "    |",
  "    |",
  "+---+",
  "    |",
  "    |",
  "+---+"},
  {"+   +",
  "|   |",
  "|   |",
  "+---+",
  "    |",
  "    |",
  "    +"},
  {"+---+",
  "|    ",
  "|    ",
  "+---+",
  "    |",
  "    |",
  "+---+"},
  {"+---+",
  "|    ",
  "|    ",
  "+---+",
  "|   |",
  "|   |",
  "+---+"},
  {"+---+",
  "    |",
  "    |",
  "    +",
  "    |",
  "    |",
  "    +"},
  {"+---+",
  "|   |",
  "|   |",
  "+---+",
  "|   |",
  "|   |",
  "+---+"},
  {"+---+",
  "|   |",
  "|   |",
  "+---+",
  "    |",
  "    |",
  "+---+"}};
void clear_screen(){
  for(int i=0;i<DIGITH;i++)
   for(int j=0;j<SCREENW;j++)
    screen[i][j]=' ';
}
void display_screen(){
  for(int i=0;i<DIGITH;i++){
   puts(screen[i]);
  }
}
void print_digit(int pos, int digit){
  for(int i=0;i<DIGITH;i++)
   for(int j=0;j<DIGITW;j++){
    screen[i][cols[pos]+j]=digits[digit][i][j];
   }
}
void print_dot(){
  for(int i=0;i<DIGITH;i++)
   for(int j=0;j<DOTW;j++){
    screen[i][j+DOT_COLUMN]=dot[i][j];
   }
}
void print_time(int h1, int h2, int m, int s){
  print_dot();
  print_digit(0,h1);
  print_digit(1,h2);
  print_digit(2,m);
  print_digit(3,s);
}
int main(){
  const int MAXBUF=255;
  char line[MAXBUF];
  int h1,h2,m,s;
  while(fgets(line,MAXBUF,stdin)&&
      (strcmp(line,"end")!=0)&&
      (strcmp(line,"end\n")!=0))
  {
   clear_screen();
   h1=line[0]-'0';
   h2=line[1]-'0';
   m=line[3]-'0';
   s=line[4]-'0';
   print_time(h1,h2,m,s);
   display_screen();
   puts("");puts("");
  }
  puts("end");
  return 0;
}
