#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  pair first, second;
}quad;
quad newquad(pair a, pair b){
  return(quad){a,b};
}

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define RFOR(i,b,a) for (int i = (b) - 1; i >= (a); i--)
#define ITER(it,a) for (__typeof(a.begin()) it = a.begin(); it != a.end(); it++)
#define FILL(a,value) memset(a, value, sizeof(a))
#define SZ(a) (int)a.size()
#define ALL(a) a.begin(), a.end()
#define MP newpair
typedef long long Int;
enum{ INF = 1000 * 1000 * 1000};
enum{ MAX = 774};
enum{ MOD = 998244353};
char s[MAX];
int mX[MAX][MAX];
int MX[MAX][MAX];
int mY[MAX][MAX];
int MY[MAX][MAX];
int mZ[MAX][MAX];
int MZ[MAX][MAX];
quad Q[6*MAX*MAX];//{pair,pair}
unsigned U[MAX][MAX][MAX / 32 + 7];
int L, R;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};


int encode(int x, int y, int z){
    return x * 1000000 + y * 1000 + z;
}
void try_update(int x, int y, int z, int d, int t){
    if (t == 1){
        swap(x, y);
    }
    if (t == 2){
        swap(x, y);
        swap(y, z);
    }
    if (!(U[x][y][z / 32] & (1 << (z % 32)))){
        U[x][y][z / 32] |= (1 << (z % 32));
        Q[R++] = newquad(newpair(x, d), newpair(y, z));
    }
}
void upX(int mX[][MAX], int x, int y, int z, int X, int Y, int Z, int d, int t){
    if (x < mX[y][z] && mX[y][z] < X){
        if (x + 1 == mX[y][z]){
            FOR(dir, 0, 4){
                int yy = y + dx[dir];
                int zz = z + dy[dir];
                if (yy < 0 || yy >= Y || zz < 0 || zz >= Z)
                    continue;
                if (mX[yy][zz] <= x || mX[yy][zz] > X)
                    continue;
                int xx = mX[yy][zz] - 1;
                try_update(xx, yy, zz, d + 1, t);
            }
        }
        else{
            int xx = mX[y][z] - 1;
            try_update(xx, y, z, d + 1, t);
        }
    }
}
void downX(int MX[][MAX], int x, int y, int z, int X, int Y, int Z, int d, int t){
    if (x > MX[y][z] && MX[y][z] >= 0){
        if (x - 1 == MX[y][z]){
            FOR(dir, 0, 4){
                int yy = y + dx[dir];
                int zz = z + dy[dir];
                if (yy < 0 || yy >= Y || zz < 0 || zz >= Z)
                    continue;
                if (MX[yy][zz] >= x || MX[yy][zz] < 0)
                    continue;
                int xx = MX[yy][zz] + 1;
                try_update(xx, yy, zz, d + 1, t);
            }
        }
        else{
            int xx = MX[y][z] + 1;
            try_update(xx, y, z, d + 1, t);
        }
    }
}
int main(){
    int X, Y, Z;
    scanf("%d %d %d", &X, &Y, &Z);
    swap(X, Z);
    int x1, y1, z1;
    int x2, y2, z2;
    FOR(i,0,MAX)
        FOR(j,0,MAX){
            mX[i][j] =  INF;
            MX[i][j] = -INF;
            mY[i][j] =  INF;
            MY[i][j] = -INF;
            mZ[i][j] =  INF;
            MZ[i][j] = -INF;
        }
    FOR(x,0,X)
        FOR(y,0,Y){
            scanf("%s", s);
            FOR(z,0,Z){
                if (s[z] == 'R'){
                    x1 = x;
                    y1 = y;
                    z1 = z;
                }
                if (s[z] == 'T'){
                    x2 = x;
                    y2 = y;
                    z2 = z;
                }
                if (s[z] == '*'){
                    mX[y][z] = fmin(mX[y][z], x);
                    MX[y][z] = fmax(MX[y][z], x);
                    mY[x][z] = fmin(mY[x][z], y);
                    MY[x][z] = fmax(MY[x][z], y);
                    mZ[x][y] = fmin(mZ[x][y], z);
                    MZ[x][y] = fmax(MZ[x][y], z);
                }
            }
        }
    L = 0;
    R = 0;
    Q[R ++] = newquad(newpair(x1, 0), newpair(y1, z1));
    U[x1][y1][z1 / 32] |= (1 << (z1 % 32));
    while (L < R){
        int x = Q[L].first.first;
        int d = Q[L].first.second;
        int y = Q[L].second.first;
        int z = Q[L].second.second;
        ++ L;
        if (x == x2 && y == y2 && z == z2){
            printf("%d\n", d);
            return 0;
        }
        upX(mX, x, y, z, X, Y, Z, d, 0);
        upX(mY, y, x, z, Y, X, Z, d, 1);
        upX(mZ, z, x, y, Z, X, Y, d, 2);
        downX(MX, x, y, z, X, Y, Z, d, 0);
        downX(MY, y, x, z, Y, X, Z, d, 1);
        downX(MZ, z, x, y, Z, X, Y, d, 2);
    }
    puts("-1");
    return 0;
}
