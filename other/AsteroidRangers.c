#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
typedef struct{
  double first;
  int    second;
}pdi;
pdi newPdi(double a, int b){
  pdi rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpPdi(pdi a, pdi b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
pdi minPdi(pdi a, pdi b){return cmpPdi(a,b)<0?a:b;}
////////////////////////////////
enum{ N = 55};
int n , ca;
int X[N] , Y[N] , Z[N] , Vx[N] , Vy[N] , Vz[N];
#define square(x) ((x)*(x))

typedef struct{
    double t;
    pair A , B;
}Event;
Event newEvent(double _t , int i , int j , int x , int y){
    Event rez;
    rez.t = _t;
    rez.A = newPair(i , j);
    rez.B = newPair(x , y);
    return rez;
}
int cmpE(const void*pa, const void*pb){
    Event*a=(Event*)pa;
    Event*b=(Event*)pb;
    return(a->t < b->t)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Event*pushbackE(Event*array, int *size, Event value){
  Event*output = resizeArray(array, Event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Event*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

inline double dis(double t , int x , int y){
    return sqrt(square(X[x] - X[y] + t * (Vx[x] - Vx[y])) + square(Y[x] - Y[y] + t * (Vy[x] - Vy[y])) + square(Z[x] - Z[y] + t * (Vz[x] - Vz[y])));
}
int f[N] , tree[N][N];
int getf(int x){
    if(x == f[x])
        return x;
    else{
        f[x] = getf(f[x]);
        return f[x];
    }
}
pdi d[N];
double T;

int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  pair A = *a;
  pair B = *b;
  return(dis(T , A.first , A.second) < 
         dis(T , B.first , B.second))?-1:1;
}
void work(){
    int i , j , k , x , y;
    for(i = 1 ; i <= n ; ++ i)
        scanf("%d%d%d%d%d%d", &X[i] , &Y[i] , &Z[i] , &Vx[i] , &Vy[i] , &Vz[i]);
    vece E = newVecE();
    for (i = 1 ; i <= n ; ++ i){
        for (j = i + 1 ; j <= n ; ++ j){
            for (x = i ; x <= n ; ++ x){
                for (y = x == i ? j + 1 : x + 1 ; y <= n ; ++ y){
                    int a = square(Vx[j] - Vx[i]) + square(Vy[j] - Vy[i]) + square(Vz[j] - Vz[i]) -
                            square(Vx[y] - Vx[x]) - square(Vy[y] - Vy[x]) - square(Vz[y] - Vz[x]);
                    int b = (((Vx[j] - Vx[i]) * (X[j] - X[i]) + (Vy[j] - Vy[i]) * (Y[j] - Y[i]) + (Vz[j] - Vz[i]) * (Z[j] - Z[i])) -
                             ((Vx[y] - Vx[x]) * (X[y] - X[x]) + (Vy[y] - Vy[x]) * (Y[y] - Y[x]) + (Vz[y] - Vz[x]) * (Z[y] - Z[x]))) << 1;
                    int c = square(X[j] - X[i]) + square(Y[j] - Y[i]) + square(Z[j] - Z[i]) -
                            square(X[y] - X[x]) - square(Y[y] - Y[x]) - square(Z[y] - Z[x]);
                    if (a == 0) {
                        if (b != 0)
                            E.ptr = pushbackE(E.ptr, &E.sz, newEvent(-1.0 * c / b , i , j , x , y));
                        continue;
                    }
                    int delta = b * b - 4 * a * c;
                    if (delta == 0)
                        E.ptr = pushbackE(E.ptr, &E.sz, newEvent(-1.0 * b / (a + a) , i , j , x , y));
                    else if (delta > 0){
                        double tmp = sqrt(delta);
                        E.ptr = pushbackE(E.ptr, &E.sz, newEvent((-b + tmp) / (a + a) , i , j , x , y));
                        E.ptr = pushbackE(E.ptr, &E.sz, newEvent((-b - tmp) / (a + a) , i , j , x , y));
                    }
                }
            }
        }
    }
    qsort(E.ptr , E.sz, sizeof(Event), cmpE);
    memset(f , 0 , sizeof(f));
    memset(tree , 0 , sizeof(tree));
    for (i = 1 ; i <= n ; ++ i)
        d[i] = newPdi(1e30 , 0);
    d[1].first = 0;
    vecp edge = newVecP();
    while(1){
        x = -1;
        for(i = 1 ; i <= n ; ++ i)
            if(!f[i] && (!~x || cmpPdi(d[x], d[i])>0))
                x = i;
        if (!~x)
            break;
        f[x] = 1;
        tree[d[x].second][x] = tree[x][d[x].second] = 1;
        if (d[x].second)
            edge.ptr = pushbackP(edge.ptr, &edge.sz, newPair(d[x].second , x));
        for (i = 1 ; i <= n ; ++ i)
            if (!f[i])
                d[i] = minPdi(d[i], newPdi(dis(0 , x , i), x));
    }
    int ans = 1;
    for (int K = 0 ; K < E.sz; ++ K){
        if (E.ptr[K].t <= 1e-7)
            continue;
        T = E.ptr[K].t + 1e-6;
        pair A = E.ptr[K].A ,
             B = E.ptr[K].B;
        if ((tree[A.first][A.second] ^ tree[B.first][B.second]) == 0)
            continue;
        if (tree[A.first][A.second])
            edge.ptr = pushbackP(edge.ptr, &edge.sz, B);
        else
            edge.ptr = pushbackP(edge.ptr, &edge.sz, A);
        qsort(edge.ptr , edge.sz, sizeof(pair), cmpP);
        for(i = 1 ; i <= n ; ++i)
            f[i] = i;
        j = k = -1;
        for (i = 0 ; i < edge.sz; ++ i){
            x = edge.ptr[i].first,
            y = edge.ptr[i].second;
            if (!tree[x][y])
                k = i;
            if (getf(x) == getf(y)){
                if (tree[x][y]){
                    ++ ans;
                    j = i;
                    tree[x][y] = tree[y][x] = 0;
                }
            }
            else{
                f[getf(x)] = getf(y);
                if (!tree[x][y])
                    tree[x][y] = tree[y][x] = 1;
            }
        }
        if (~j){
            swap(edge.ptr[j] , edge.ptr[n - 1]);
            edge.sz--;
        }
        else{
            swap(edge.ptr[k] , edge.ptr[n - 1]);
            edge.sz--;
        }
    }
    printf("Case %d: %d\n" , ++ ca , ans);
}
int main(){
    while (~scanf("%d",&n))
        work();
    return 0;
}
