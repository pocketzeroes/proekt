#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int main(){
    while(true){
        int n;
        scanf("%d", &n);
        if(n == 0)
            break;
        int minutes[n]; memset(minutes, 0, sizeof(minutes));
        ll  money  [n]; memset(money  , 0, sizeof(money  ));
        ll totalProfit = 0;
        for(int i = 0; i < n; i++){
            int mins;
            scanf("%d", &mins);
            minutes[i] = mins;
            double mon;
            scanf("%lf", &mon);
            money  [i] = (int)round(mon * 100.);
            totalProfit += money[i];
        }
        ll totalCost = 8 * (minutes[n - 1] - minutes[0] + 1) - totalProfit;
        ll savedByCuttingUntil1[n]; memset(savedByCuttingUntil1, 0, sizeof(savedByCuttingUntil1));
        for(int i = 1; i < n; i++)
            savedByCuttingUntil1[i] = savedByCuttingUntil1[i - 1] + (minutes[i] - minutes[i - 1]) * 8 - money[i - 1];
        ll savedByCuttingUntil2[n]; memset(savedByCuttingUntil2, 0, sizeof(savedByCuttingUntil2));
        for(int i = n - 2; i >= 0; i--)
            savedByCuttingUntil2[i] = savedByCuttingUntil2[i + 1] + (minutes[i + 1] - minutes[i]) * 8 - money[i + 1];
        ll  bestSecondChoice [n]; memset(bestSecondChoice ,0,sizeof(bestSecondChoice ));
        int bestSecondChoiceJ[n]; memset(bestSecondChoiceJ,0,sizeof(bestSecondChoiceJ));
        bestSecondChoice [n - 1] = savedByCuttingUntil2[n - 1];
        bestSecondChoiceJ[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; i--){
            if (savedByCuttingUntil2[i] >= bestSecondChoice[i + 1]) {
                bestSecondChoice [i] = savedByCuttingUntil2[i];
                bestSecondChoiceJ[i] = i;
            }
            else {
                bestSecondChoice [i] = bestSecondChoice[i + 1];
                bestSecondChoiceJ[i] = bestSecondChoiceJ[i + 1];
            }
        }
        int bestI = 0;
        int bestJ = 0;
        int bestLength = INT_MIN;
        ll  bestValue  = INT_MIN;
        for (int i = 0; i < n; i++) {
            ll value = savedByCuttingUntil1[i] + bestSecondChoice[i];
            int length = minutes[bestSecondChoiceJ[i]] - minutes[i] + 1;
            if (i == 0 || value > bestValue || (value == bestValue && length < bestLength)) {
                bestI      = i;
                bestJ      = bestSecondChoiceJ[i];
                bestLength = length;
                bestValue  = value;
            }
        }
        ll profit = bestValue - totalCost;
        if (profit <= 0)
            puts("no profit\n");
        else
            printf("%.2lf %d %d\n", (profit / 100. + 0.000000001), minutes[bestI], minutes[bestJ]);
    }
    return 0;
}
