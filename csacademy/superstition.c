/*------------ superstition ----------------------------------------------------
         Днес е дългоочакваният за всички ученици – първи НЕучебен ден за новата
учебна година. Нашата героиня Дени вече е в 10 клас.Тя се е подготвила за
днешния ден и е набелязала N магазина в града и планира да посети някои от
тях с приятелките си. Но за Дени и приятелките ѝ някои пътища са
непривлекателни и те не искат да минават оттам. Затова те са направили списък
от M двойки магазини, между които могат да се движат (разбира се двупосочно)
и са определили времето, за което може да се стигне от единия до другия
магазин. Разбира се в списъка няма двойка магазини с еднакви номера, както и
дублиращи се двойки.
Дени е много суеверна и едно от суеверията, в които вярва, е, че общото време
за извършване на дадена дейност трябва да се дели на D. Все пак Дени и
приятелките ѝ нямат неограничено време, затова максимално могат да отделят K
време. Като всички момичета те са много любопитни и започват да разглеждат
различните маршрути за минаване по някои от магазините (възможно е през
магазин да се мине повече от един път). За съжаление те се оказват прекалено
много, затова Дени се сеща, че познава Вас – много добри програмисти, и Ви
моли да ѝ напишете програма superstition, която да съобщава броя на
различните валидни маршрути. Един маршрут е валиден, ако използва връзките от
изготвения списък, общото време за изминаването се дели на D и то е ≤ на K.
Два маршрута са различни, ако има разлика в последователността на посетените
магазини. Вие веднага се досещате, че отговорът може да е наистина много
голям, затова Дени Ви казва, че би искала единствено остатъка му при деление
на 1 000 000 007.
------------------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


/////////////////////
int N, M, D, K;
int aux[335][335] ,T;
int DP[85][10005];
enum{ MOD = 1000000007};
int Buf[100005];
vecp G[100005];
int X[335][335]  , A[335][335]  , ret[335][335]  , pw[335][335]  , I[335][335] , Ans[335][335];
int sol[335][335];
int Aux[335][335];
int lim = 0;




void Add(int*x, int y)
{
    (*x) += y;
    if(*x >= MOD)
       (*x) -= MOD;
}
void add(int A[][335], int B[][335])
{
    for(int i = 1; i <= lim; i++)
        for(int j = 1; j <= lim; j++){
            Aux[i][j] = A[i][j];
            Add(&Aux[i][j], B[i][j]);
        }
}
void mul(int A[][335], int B[][335])
{
    memset(Aux, 0, sizeof(Aux));
    for(int i = 1; i <= lim; i++){
        for(int k = 1; k <= lim; k++){
            if(A[i][k] == 0)
                continue;
            for(int j = 1; j <= lim; j++)
                Add(&Aux[i][j], (1LL * A[i][k] * B[k][j]) % MOD);
        }
    }
}
void copy(int A[][335], int B[][335])
{
    for(int i = 1; i <= lim; i++)
        for(int j = 1; j <= lim; j++)
            A[i][j] = B[i][j];
}
void Read()
{
    scanf("%d %d %d %d", &N, &M, &D, &K);
    int Max = 0;
    for(int i = 1; i <= M; i++){
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        Max = max(Max, t);
        G[x].ptr = pushbackP(G[x].ptr, &G[x].sz, newPair(y, t));
        G[y].ptr = pushbackP(G[y].ptr, &G[y].sz, newPair(x, t));
    }
    lim = N * (Max + 1);
    T = Max;
}
inline int Code(int node, int time)
{
    return time * N + node;
}
void power(int A[][335], int p)
{

    for(int i = 1; i <= lim; i++)
        sol[i][i] = 1;
    while(p)
    {
        if(p & 1)
        {
            mul(sol, A);
            copy(sol, Aux);
        }
        p /= 2;
        copy(aux, A);
        mul(A, aux);
        copy(A, Aux);
    }
    copy(ret, sol);
}
void SolveTask2()
{
    int a;
    a = 0;
    for(int j = 1; j <= N; j++){
        for(int k = 0; k < G[j].sz; k++){
            int neighb = G[j].ptr[k].first, t = G[j].ptr[k].second;
            X[j][Code(neighb, t - 1)] = 1;
        }
    }
    for(int i = 0; i < T - 1; i++)
        for(int k = 1; k <= N; k++)
            X[Code(k, i + 1)][Code(k, i)] = 1;
    power(X, D);
    int nb = K / D;
    for(int i = 1; i <= lim; i++)
        pw[i][i] = I[i][i] = 1;
    for(int i = 30; i >= 0; i--){
        if((1 << i) > nb)
            continue;
        mul(Ans, pw);
        copy(aux, Aux);
        add(Ans, aux);
        copy(Ans, Aux);
        copy(aux, pw);
        mul(pw, aux);
        copy(pw, Aux);
        if((nb & (1 << i))){
            mul(Ans, ret);
            copy(Ans, Aux);
            add(Ans, I);
            copy(Ans, Aux);
            mul(pw, ret);
            copy(pw, Aux);
        }
    }
    mul(Ans, ret);
    copy(Ans, Aux);
    int ans = 0;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            Add(&ans, Ans[i][j]);
    printf("%d\n", ans);
}
int main()
{
    Read();
    if(N > 30){
        for(int i = 1; i <= N; i++)
            DP[i][0] = 1;
        int ans = 0;
        for(int j = 1; j <= K; j++){
            for(int i = 1; i <= N; i++){
                for(int k = 0; k < G[i].sz; k++){
                    int neighb = G[i].ptr[k].first, t = G[i].ptr[k].second;
                    if(t <= j)
                      Add(&DP[i][j], DP[neighb][j - t]);
                    
                }
                if(j %D == 0)
                    Add(&ans, DP[i][j]);
            }
        }
        printf("%d\n", ans);
        return 0;
    }
    SolveTask2();
    return 0;
}
