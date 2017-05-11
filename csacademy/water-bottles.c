#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll *pushback(ll *array, int *size, ll value) {
    ll *output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
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





ll* water_level  =NULL;
int water_levelSz=0;
int bottleSz;

ll MinWater(pair*bottle, int all_water_height){
    ll required_water = 0;
    water_levelSz=0;
    for(int i=0;i<bottleSz;i++){pair itr = bottle[i];
        int current = 0;
        if (itr.first >= all_water_height) 
            current = itr.first;
        else 
            current = min(itr.second, all_water_height);
        required_water += current;
        water_level=pushback(water_level, &water_levelSz, current);
    }
    return required_water;
}
int main(){
    int n;
    ll l;
    scanf("%d %lld", &n, &l);
    pair bottle[n];
    bottleSz = n;
    for(int i = 0; i < n; i += 1){
        scanf("%d %d", &bottle[i].first, &bottle[i].second);
    }
    int all_water_height = 0;
    for (int p = 29; p >= 0; p -= 1) {
        if (MinWater(bottle, all_water_height + (1 << p)) <= l) {
            all_water_height += (1 << p);
        }
    }
    ll remaining_water = l - MinWater(bottle, all_water_height);
    for (int i = 0; i < n; i += 1) {
        if (remaining_water && bottle[i].second > water_level[i]) {
            water_level[i]  += 1;
            remaining_water -= 1;
        }
    }
    ll mn = water_level[0];
    ll mx = water_level[0];
    for(int i=0;i<water_levelSz;i++){ll itr = water_level[i];
        mn = min(mn, itr);
        mx = max(mx, itr);
    }
    printf("%lld\n", mx - mn);
}


























































