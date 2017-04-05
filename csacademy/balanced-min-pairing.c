#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
typedef struct pair {
	int first;
	int second;
}pair;
pair newPair(int a, int b) {
	pair rez;
	rez.first = a;
	rez.second = b;
	return rez;
}
int cmp (const void * pa, const void * pb)
{
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    int diff = a->first - b->first;
    if(diff!=0)return diff;
    return a->second - b->second;
}
int main() {
    int numTestcases;
    scanf("%d", &numTestcases);
    while (numTestcases--){
        int n;
        scanf("%d", &n);
        int n2 = n / 2;
        pair a[n];
        pair b[n];
        for (int i = 0; i < n; i++){
            int in;
            scanf("%d", &in);
            a[i].first  = in;
            a[i].second = i;
        }
        for (int i = 0; i < n; i++){
            int in;
            scanf("%d", &in);
            b[i].first  = in;
            b[i].second = i;
        }
        qsort(a, n,sizeof(pair), cmp);
        qsort(b, n,sizeof(pair), cmp);
        bool ok = true;
        for (int i = 0; i < n2; i++)
            if (a[i].first >= b[i + n2].first)
                ok = false;
        for (int i = 0; i < n2; i++)
            if (b[i].first >= a[i + n2].first)
                ok = false;
        if (!ok) {
            puts("-1");
            continue;
        }
        int solution[n];
        for (int i = 0; i < n2; i++){
            solution[a[i     ].second] = b[n2 + i].second;
            solution[a[n2 + i].second] = b[i     ].second;
        }
        for(int i=0;i<n;i++){
            int itr=solution[i];
            printf("%d ", 1 + itr);
        }
        printf("\n");
    }
    return 0;
}





