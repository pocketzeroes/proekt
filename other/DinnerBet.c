#include<stdio.h>
#include<stdlib.h>

#define DEBUG
#define P 2
#define NMAX 50
#define KMAX 10
#define DRAWSIZE 10
#define MIN(X,Y) ((X) < (Y)? (X):(Y))
#define MAX(X,Y) ((X) > (Y)? (X):(Y))


int N, K, Draw;
double Time[KMAX+1][KMAX+1][KMAX+1];
double Comb[NMAX+1][DRAWSIZE+1];

void init_comb(){
  int i,j, r = MAX(Draw,K);
  Comb[0][0]=1;
  for(i=0; i<N;i++){
    Comb[i+1][0]=1;
    for(j=1; j<= r && j<=i;j++)
      Comb[i+1][j] = Comb[i][j-1] + Comb[i][j];
    if (i+1<= r)
      Comb[i+1][i+1] = 1;
  }
}
void init_time(){
  int a, b, c;
  for(b=0; b<=K; b++)
    Time[0][0][b] = Time[0][b][0] = 0;
  for(a=1; a<=K; a++)
    for(b=1; b<=a; b++)
      Time[0][a][b]= Time[0][b][a] = -1;
  for(c=1;c <= K;c++) {
    for(a=0; a<=K; a++)
      for(b=0; b<=a; b++)
        Time[c][a][b]= Time[c][b][a] = -1;
  }
}
double find_time(int c,int a, int b){
  int sc,sa,sb,sr;
  double p, p0, total = 0;
  if (Time[c][a][b] >= 0)
    return Time[c][a][b];
  Time[c][a][b] = 0;
  p0 = 0;
  for(sc=MAX(0,Draw-(N-c)); sc <= MIN(c,Draw); sc++){
    for(sa=MAX(0,(Draw-sc)-(N-c-a)); sa <= MIN(a,Draw-sc); sa++){
      for(sb=MAX(0,(Draw-sc-sa)-(N-c-a-b)); sb <= MIN(b,Draw-sc-sa); sb++){
        sr = Draw-sc-sa-sb;
        if (sc==0 && sa==0 && sb ==0)
          p = p0 = Comb[N-a-b-c][sr];
        else {
          p = Comb[c][sc]*Comb[a][sa]*Comb[b][sb]*Comb[N-a-b-c][sr];
          Time[c][a][b]  += p*find_time(c-sc,a-sa,b-sb);
        }
        total += p;
      }
    }
  }
  Time[c][a][b] += total;
  Time[c][a][b] /= (total-p0);
  Time[c][b][a] = Time[c][a][b];
  return Time[c][a][b];
}
int main(){
  int k,  i, c;
  int bet[NMAX+1]={0};
  scanf("%d %d %d", &N, &Draw, &K);
  c = 0;
  for(k=0; k<K; k++){
    scanf("%d", &i);
    bet[i] = 1;
  }
  for(k=0; k<K; k++){
    scanf("%d",&i);
    bet[i]++;
    if (bet[i] == 2)
      c++;
  }
  init_time();
  init_comb();
  printf("%.8lf\n", find_time(c,K-c,K-c));
  return 0;
}




