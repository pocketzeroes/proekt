#include<stdio.h>
#include<math.h>
#include<float.h>

enum{ N = 11000};
#define G 9.8
double A[N+100];

int main(){
    int CASES=1;
    while(CASES--){
        int i,j;
        double neginf = -DBL_MAX;
        for(i=1; i<N; i++){
            A[i] = neginf;
        }
        A[0] = 0;
        int stages;
        scanf("%d", &stages);
        int maxmass = 0;
        for(i=0;i<stages;i++){
            int ms, mf, th, fc;
            scanf("%d %d %d %d", &ms, &mf, &th, &fc);
            for(j=N; j>=0; j--) {
                int newm = j + ms;
                int totm = newm+mf;
                if(totm > 10000)
                    continue;
                if(th/totm < G)
                    continue;
                double time = 1.0*mf/fc;
                double acc = th*(log(newm+mf) - log(newm))/fc - time*G;
                acc = acc + A[j];
                if(acc <= A[newm+mf])
                    continue;
                A[newm+mf] = acc;
            }
            maxmass += ms+mf;
        }
        double mx = 0;
        for(i=0; i<N; i++) {
            if(A[i]>mx)
                mx = A[i];
        }
        printf("%.0lf\n", mx);
    }
    return 0;
}
