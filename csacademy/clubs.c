/*---------------------------------------------------------------------------------\
|    Жителите на град X много обичат да организират различни клубове. С течение на | 
| времето броят на клубовете в града толкова нараснал, че се появили много         |
| клубове, в които членували едни и същи хора. Ето защо градската управа се        |
| събрала и решила да сложи ред в клубовете в града. Било решено да се             |
| организира система от клубове, в която да се разпределят жителите на града,      |
| така че да се изпълнява следното условие:                                        |
| (А) за всеки двама жители на града съществува поне един клуб, в който единият    |
| членува, а другият – не.                                                         |
| Един жител може да не членува никъде, а може да  членува и в повече от един      |
| клуб.                                                                            |
|     Тъй като обслужването на всеки клуб изисква определени разходи от страна на  |
| общината, то броят на клубовете трябва да бъде минимален. Тъй като членовете     |
| на всеки клуб трябва да се събират някъде, а градът не разполага с много         |
| големи зали, то членовете на клубовете трябва да се определят така, че броят     |
| на хората в най-големия (с най-много членове) клуб да бъде минимален (разбира    |
| се, може да има повече от един „най-голям“ клуб с еднакъв брой членове).         |
|     Жителите на града са N на брой и са номерирани с числата от 1 до N.          |
| Напишете програма clubs, която намира минималния брой клубове,                   |
| удовлетворяващи условието (A), и определя членове за всеки клуб от това          |
| минимално множество така, че да се изпълнява условието за минимален брой         |
| членове в най-големия от тях. Ако членове на клубовете могат да се изберат по    |
| повече от един начин, то изведете кой да е от тях.                               |
\---------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int unique(int *a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
int max_element(int*arr,int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////
int n, m;
int binom[25][25];

void stampaj(vec sol){
    int b[m];
    for (int i=0; i<m; i++) {
        int br = 0;
        for(int z=0;z<sol.sz;z++){int x = sol.ptr[z];
            if (x & (1 << i))
                br++;
        }
        b[i] = br;
    }
    printf("%d %d\n", m, max_element(b, m));
    for(int i=0; i<m; i++){
        printf("%d", b[i]);
        int j = 0;
        for(int z=0;z<sol.sz;z++){int x = sol.ptr[z];
            j++;
            if (x & (1 << i))
                printf(" %d", j);
        }
        puts("");
    }
}
vec sverot(int x){
    vec a = newVec();
    for(int i=0; i<m; i++) {
        a.ptr = pushback(a.ptr, &a.sz, x);
        x = (x >> 1) | ((x & 1) << (m-1));
    }
    qsort(a.ptr, a.sz, sizeof(int), cmp);
    a.sz = unique(a.ptr, a.sz);
    return a;
}
void puni_brut_najveci(vec v, int biram, vec*sol){
    int bestval = 12313123, bestmask = -1;
    for(int mask=0; mask < (int)(1 << v.sz); mask++) {
        if (__builtin_popcount(mask) != biram)
            continue;
        int najgori = 0;
        for (int i=0; i<m; i++){
            int br = 0;
            for (int j=0; j<v.sz; j++){
                if ((1 << j) & mask)
                    br += 1 & (v.ptr[j] >> i);
            }
            najgori = max(najgori, br);
        }
        if (najgori < bestval){
            bestval = najgori;
            bestmask = mask;
        }
    }
    for (int j=0; j<v.sz; j++){
        if ((1 << j) & bestmask)
            sol->ptr = pushback(sol->ptr, &sol->sz, v.ptr[j]);
    }
}
vec resi(){
    vec sol = newVec();
    for (int i=0; i<25; i++)
        binom[i][0] = binom[0][i] = 1;
    for (int i=1; i<21; i++)
        for (int j=1; j<21; j++)
            if (i + j <= 20) 
                binom[i][j] = binom[i-1][j] + binom[i][j-1];
    int grupa  = 0;
    int ostalo = n;
    while (1){
        int brg = binom[grupa][m - grupa];
        if (brg <= ostalo){
            for (int x=0; x<(1<<m); x++) {
                if (__builtin_popcount(x) == grupa){
                    sol.ptr = pushback(sol.ptr, &sol.sz, x);
                    ostalo--;
                }
            }
            grupa++;
            if (ostalo == 0)
                return sol;
            continue;
        }
        bool used[1<<m]; memset(used, 0, sizeof(used));
        {
            vec v = sverot((1 << grupa) - 1);
            for(int z=0;z<v.sz;z++){int x = v.ptr[z];
                used[x] = true;
            }
        }
        {
            for(int x=0; x<(1<<m); x++) {
                if (used[x])
                    continue;
                if (__builtin_popcount(x) != grupa)
                    continue;
                vec v = sverot(x);
                if(v.sz > ostalo){
                    vec vv = sverot((1 << grupa) - 1);
                    puni_brut_najveci(vv, ostalo, &sol);
                    return sol;
                }
                for(int z=0;z<v.sz;z++){int y = v.ptr[z];
                    used[y] = true;
                    sol.ptr = pushback(sol.ptr, &sol.sz, y);
                    ostalo--;
                }
                if (ostalo == 0) return sol;
            }
            if (ostalo == 0) return sol;
            else {
                vec vv = sverot((1 << grupa) - 1);
                puni_brut_najveci(vv, ostalo, &sol);
                return sol;
            }
        }
        if (ostalo == 0) return sol;
    }
    if (ostalo == 0) return sol;
}
int main(){
    scanf("%d", &n);
    m = 32 - __builtin_clz(n-1);
    stampaj(resi());
}

