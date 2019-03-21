#include <stdio.h>
enum{ T = 5010};
int p_cur , p_h[T], p_x[T];
short height[T][T] ;
int nb_rect[T][T];
int X,Y,N,D,x1,x2,y_1,y2;

int main(){
  scanf("%d %d %d %d", &X, &Y, &N, &D);
  while(N--){
    scanf("%d %d %d %d", &x1, &x2, &y_1, &y2);
    for(int y = y_1; y < y2; y++)
      for(int x = x1; x < x2; x++)
        height[y][x] = -1;
  }
  for(int y = Y-1 ; y>=0 ; y--)
    for(int x = 0 ; x < X ; x++)
      if(height[y][x] < 0 )
        height[y][x] = 0 ;
      else
        height[y][x]=height[y+1][x]+1;
  p_h[0] = -1 ; 
  for(int y = 0 ; y < Y ; y++)
    for(int x = 0 ; x <= X ; x++){
      int h = height[y][x];
      int p_nxt = p_cur ;
      p_x[p_cur+1] = x ;
      while( h <= p_h[p_nxt] ){
        nb_rect[p_h[p_nxt]][x-p_x[p_nxt]]++;
        nb_rect[p_h[p_nxt]][x-p_x[p_nxt+1]]--;
        p_nxt--;
      }
      nb_rect[h][x-p_x[p_nxt+1]]--;
      p_nxt++;
      p_h[p_nxt] = h ;
      p_cur=p_nxt;
    }
  int dx = -1, dy = 0;
  for(int c = 0 ; c < 3 ; c++ ){
    for(int y = Y ; y > 0 ; y--)
      for(int x = X ; x > 0 ; x--)
        nb_rect[y+dy][x+dx] += nb_rect[y][x] ;
    dy = dx ;
    dx = -1 - dx;
  }
  while(D--){
    scanf("%d %d", &x1, &y_1);
    printf("%d\n", nb_rect[y_1][x1]);
  }
  return 0;
}
