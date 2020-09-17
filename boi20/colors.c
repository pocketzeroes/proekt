#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll n;
ll last;
ll plast;
bool lastAnswer;
ll mas[70];


int ask(ll x){
    printf("? %lld\n", x); fflush(stdout);
    int v;
    scanf("%d", &v);
    return v;
}
void ask4(ll x){
    plast = last;
    last = x;
    lastAnswer = ask(x);
}
void giveAnswer(ll x){
    printf("= %lld\n", x); fflush(stdout);
}
int main(){
    scanf("%lld", &n);
    int i = 0;
    mas[0] = n;
    if (mas[0] > 2){
        while (mas[i] > 4){
            i++;
            mas[i] = mas[i - 1] / 2 + mas[i - 1] % 2;
        }
        bool aug = true;
        ll f = 2;
        for (int j = i - 1; j >= 0; j--){
            aug = !aug;
            if (!aug){
                f = mas[j] + f - mas[j+1];
            }
        }
        ll add2 = 0;
        ask4(f);
        for (int j = 0; j < i; j++){
            ll g = mas[j] - mas[j+1] + add2;
            if (aug){
                ask4(last + g);
            }
            else{
                ask4( last - g);
            }
            if (!lastAnswer){
                add2 += mas[j] - mas[j+1];
            }
            aug = !aug;
        }
        if (mas[i] == 3){
            ask4(last + add2 + 1);
            if (!lastAnswer){
                ask4(last - add2 - 2);
                if (lastAnswer){
                    giveAnswer(add2 + 2);
                }
                else{
                    giveAnswer(add2 + 3);
                }
            }
            else{
                giveAnswer(add2+1);
            }
        }
        else if (mas[i] == 4){
            ask4(last + add2 + 2);
            if (lastAnswer){
                ask4(last - add2 - 1);
                if (lastAnswer){
                    giveAnswer(add2 + 1);
                }
                else{
                    giveAnswer(add2 + 2);
                }
            }
            else{
                ask4(last - add2 - 3);
                if (lastAnswer){
                    giveAnswer(add2+3);
                }
                else{
                    giveAnswer((add2 + 4));
                }
            }
        }
    }
    else{
        ask4(1);
        ask4(2);
        if (lastAnswer){
            giveAnswer(1);
        }
        else{
            giveAnswer(2);
        }
    }
    return 0;
}
