#include<stdio.h>
int main(){
    int tc;
    scanf("%d", &tc);
    int  i, r, s, s0, c;
    char N[8], n[8];
    for(int z=0;z<tc;z++){
        scanf("%s", n);
        if (n[0] == 'E')
            break;
        s0 = 0;
        for (i = 0; n[i]; i++){
            n[i] -= '0';
            s0   += n[i];
        }
        s = s0;
        r = i;
        for (i = 0; i < r; i++)
            N[i] = n[r - i - 1];
        while (s != 0 && s + 1 != s0){
            for (i = 0; i < r; i++){
                if (N[i] > 0){
                    N[i] -= 1;
                    s    -= 1;
                    break;
                }
                else{
                    N[i] += 9;
                    s    += 9;
                }
            }
            r -= (N[r - 1] == 0);
        }
        for (i = 0; i < r; i++)
            n[r - i - 1] = N[i] + '0';
        n[r] = 0;
        printf("%s\n", (r == 0) ? "0" : n);
    }
    return 0;
}
