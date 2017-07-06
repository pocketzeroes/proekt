#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

int readInt(){
    int i;
    scanf("%d", &i);
    return i;
}


        
        
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int compP( pair a, pair b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    return a.second - b.second;
}


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define left left228
#define right right228
#define next next228
#define rank rank228
#define prev prev228
#define y1 y1228


void chkmax(pair*x, pair y){
   if(compP(*x, y) < 0)
      *x = y;
}










enum{ MAXN = 300001    };
enum{ INF  = 1000000000};
int n;
vec v[MAXN];
int jump[MAXN];
int c[MAXN];
pair optdown[MAXN];
int pr;
int mod;

void dfs(int u) {
    optdown[u] = newPair(-INF, -INF);
    for(int i=0;i<v[u].sz;i++){int h = v[u].ptr[i];
        if (h == pr) {
            continue;
        }
        int ppr = pr;
        pr = u;
        dfs(h);
        pr = ppr;
        pair nopt = optdown[h];
        nopt.second--;
        if (nopt.second < c[h] - 1) {
            nopt = newPair(h, c[h] - 1);
        } 
        else {
            if (nopt.second == c[h] - 1 && nopt.first > h) {
                nopt = newPair(h, c[h] - 1);
            }
        }
        if (optdown[u].second < nopt.second) {
            optdown[u] = nopt;
        } 
        else {
            if (nopt.second == optdown[u].second && optdown[u].first > nopt.first) {
                optdown[u] = nopt;
            }
        }
    }
}
void dfs1(int u, pair curmax){
    pair ropt = optdown[u];
    if (u) {
        pair kek = curmax;
        kek.second *= -1;
        swap(kek.first, kek.second);
        kek.second -= mod;
        if (kek.second > ropt.second) {
            ropt = kek;
        } 
        else {
            if (kek.second == ropt.second && kek.first < ropt.first) {
                ropt = kek;
            }
        }
    }
    jump[u] = ropt.first;
    chkmax(&curmax, newPair(c[u] + mod, -u));
    pair curmax1 = curmax;
    for(int i=0;i<v[u].sz;i++){int h = v[u].ptr[i];
        if (h == pr) {
            continue;
        }
        pair nopt = optdown[h];
        nopt.second--;
        if (nopt.second < c[h] - 1) {
            nopt = newPair(h, c[h] - 1);
        } 
        else {
            if (nopt.second == c[h] - 1 && nopt.first > h) {
                nopt = newPair(h, c[h] - 1);
            }
        }
        if(compP(curmax, newPair(nopt.second + mod, -nopt.first)) < 0){
            curmax1 = curmax;
            curmax = newPair(nopt.second + mod, -nopt.first);
        } 
        else {
            if(compP(curmax1, newPair(nopt.second + mod, -nopt.first))<0) {
                curmax1 = newPair(nopt.second + mod, -nopt.first);
            }
        }
    }
    for(int i=0;i<v[u].sz;i++){int h = v[u].ptr[i];
        if (h == pr) {
            continue;
        }
        pair nopt = optdown[h];
        nopt.second--;
        if (nopt.second < c[h] - 1) {
            nopt = newPair(h, c[h] - 1);
        } 
        else {
            if (nopt.second == c[h] - 1 && nopt.first > h) {
                nopt = newPair(h, c[h] - 1);
            }
        }
        pair nmax;
        if(compP(curmax, newPair(nopt.second + mod, -nopt.first))==0) {
            nmax = curmax1;
        } 
        else {
            nmax = curmax;
        }
        mod++;
        int ppr = pr;
        pr = u;
        dfs1(h, nmax);
        pr = ppr;
        mod--;
    }
}
int main() {
    long long k;
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++) {
        c[i] = readInt();
    }
    for (int i = 1; i < n; i++) {
        int a = readInt(), b = readInt();
        a--, b--;
        v[a].ptr=pushback(v[a].ptr, &v[a].sz ,b);
        v[b].ptr=pushback(v[b].ptr, &v[b].sz ,a);
    }
    pr = -1;
    dfs(0);
    dfs1(0, newPair(-INF, -INF));
    int startcycle = -1;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        optdown[i].first = 0;
    }
    for (long long i = 1; i <= k; i++) {
        if (optdown[cur].first) {
            startcycle = cur;
            k -= i - 1;
            break;
        }
        optdown[cur].first = 1;
        cur = jump[cur];
    }
    if (startcycle != -1 && k) {
        int len = 0;
        bool was = 1;
        for (long long i = 1; i <= k; i++) {
            c[len] = cur;
            len++;
            cur = jump[cur];
            if (cur == startcycle) {
                k -= i;
                was = 0;
                break;
            }
        }
        if (!was) {
            k %= len;
            cur = c[k];
        }
    }
    printf("%d\n", cur+1);
    return 0;   
}                                   





















































