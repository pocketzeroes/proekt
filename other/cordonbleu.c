#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
typedef long long ll;
int    nx;
int    ny;
ll**costs;

ll solve(){
  int  *xy = calloc(nx, sizeof(int ));
  ll   *lx = calloc(nx, sizeof(ll  ));
  bool *s  = calloc(nx, sizeof(bool));
  for(int x = 0; x < nx; x++)
    xy[x] = -1;
  int * yx         = calloc(ny, sizeof( int));
  ll  * ly         = calloc(ny, sizeof( ll ));
  int * augmenting = calloc(ny, sizeof( int));
  ll  * slack1     = calloc(ny, sizeof( ll ));
  int * slack2     = calloc(ny, sizeof( int));
  for(int y = 0; y < ny; y++){
    yx    [y] =-1;
    ly    [y] = 0;
    slack1[y] = 0;
    slack2[y] = 0;
  }
  for(int x = 0; x < nx; x++){
    ll max = 0;
    for(int y = 0; y < ny; y++){
      if(costs[x][y] > max)
        max = costs[x][y];
    }
    lx[x] = max;
  }
  for(int root = 0; root < nx; root++){
    for(int y = 0; y < ny; y++)
      augmenting[y] = -1;
    for(int x = 0; x < nx; x++)
      s[x] = false;
    s[root] = true;
    for(int y = 0; y < ny; y++){
      slack1[y] = lx[root] + ly[y] - costs[root][y];
      slack2[y] = root;
    }
    int y = -1;
    for(;;){
      ll delta = LLONG_MAX;
      int  x = -1;
      for(int yy = 0; yy < ny; yy++)
        if(augmenting[yy] == -1)
          if(slack1[yy] < delta){
            delta = slack1[yy];
            x = slack2[yy];
            y = yy;
          }
      if(delta > 0){
        for(int xx = 0; xx < nx; xx++)
          if(s[xx])
            lx[xx] -= delta;
        for(int yy = 0; yy < ny; yy++)
          if(augmenting[yy] > -1)
            ly[yy] += delta;
          else
            slack1[yy] -= delta;
      }
      augmenting[y] = x;
      x = yx[y];
      if(x == -1)
        break;
      s[x] = true;
      for(int yy = 0; yy < ny; yy++)
        if(augmenting[yy] == -1){
          ll first = lx[x] + ly[yy] - costs[x][yy];
          if(slack1[yy] > first) {
            slack1[yy] = first;
            slack2[yy] = x;
          }
        }
    }
    while(y > -1){
      int x = augmenting[y];
      int prec = xy[x];
      yx[y] = x;
      xy[x] = y;
      y     = prec;
    }
  }
  ll total = 0;
  for(int x = 0; x < nx; x++)
    total += lx[x];
  for(int y = 0; y < ny; y++)
    total += ly[y];
  return total;
}
void newCordonBleu(int p_nx, int p_ny){
  nx    = p_nx;
  ny    = p_ny;
  costs = calloc(nx, sizeof(ll*));
  for(int i=0; i<nx; i++)
    costs[i] = calloc(ny, sizeof(ll));
}
ll dist(ll x1, ll y1, ll x2, ll y2){
  return abs(x1 - x2) + abs(y1 - y2);
}
int main(){
  int nb_bottles  = in_nextInt();
  int nb_couriers = in_nextInt();
  ll*bottle_x  = calloc(nb_bottles , sizeof(ll));
  ll*bottle_y  = calloc(nb_bottles , sizeof(ll));
  ll*courier_x = calloc(nb_couriers, sizeof(ll));
  ll*courier_y = calloc(nb_couriers, sizeof(ll));
  for(int i=0; i < nb_bottles; i++){
    bottle_x[i] = in_nextInt();
    bottle_y[i] = in_nextInt();
  }
  for(int i=0; i < nb_couriers; i++){
    courier_x[i] = in_nextInt();
    courier_y[i] = in_nextInt();
  }
  ll lab_x   = in_nextInt();
  ll lab_y   = in_nextInt();
  int  n     = nb_couriers + nb_bottles - 1;
  newCordonBleu(nb_bottles, n);
  for(int j=0; j < nb_bottles; j++){
    ll d_bl = dist(bottle_x[j], bottle_y[j], lab_x, lab_y);
    for(int i=0; i<nb_couriers; i++){
      ll d_cb = dist(courier_x[i], courier_y[i], bottle_x[j], bottle_y[j]);
      costs[j][i] = - d_cb - d_bl;
    }
    for(int i=nb_couriers; i < n; i++){
      costs[j][i] = -2 * d_bl;
    }
  }
  printf("%lld\n", -solve());
  return 0;
}
