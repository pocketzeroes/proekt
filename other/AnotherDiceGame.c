#include<math.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

static int factorial[9];
static double memo[41][9][1<<6];

static bool next_throw(int count[6]){
    int pos = 0;
    while (pos < 5 && count[pos] == 0) ++pos;
    if (pos == 5) return false;
    --count[pos];
    ++count[pos + 1];
    if (pos > 0) count[0] = count[pos], count[pos] = 0;
    return true;
}
static int permutations(int count[6]){
    int i, n = 0, f = 1;
    for (i = 0; i < 6; ++i){
        n += count[i];
        f *= factorial[count[i]];
    }
    return factorial[n]/f;
}
static double calc(int goal, int dice, int used){
    double *m = &memo[goal > 0 ? goal : 0][dice][used];
    int count[6] = { 0 };
    double sum = 0;
    if (*m == *m) return *m;
    if (goal <= 0 && used >> 5) return *m = 1.0;
    count[0] = dice;
    do {
        double best_prob = 0;
        int i;
        for (i = 0; i < 6; ++i)
        {
            if (count[i] > 0 && !(used & 1<<i))
            {
                int points = count[i]*(i < 5 ? i + 1 : 5);
                double prob = calc(goal - points, dice - count[i], used | 1<<i);
                if (prob > best_prob) best_prob = prob;
            }
        }
        sum += best_prob*permutations(count);
    } while (next_throw(count));
    return *m = sum/pow(6, dice);
}
int main(){
    int i, cases = 0;
    factorial[0] = 1;
    for (i = 1; i <= 8; ++i) factorial[i] = i*factorial[i - 1];
    memset(memo, ~0, sizeof(memo));
    scanf("%d", &cases);
    while (cases-- > 0 && scanf("%d", &i) == 1)
        printf("%.12f\n", calc(i, 8, 0));
    return 0;
}
