#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
/////////////////
enum{ kMaxN = 105};
int has[kMaxN][kMaxN * kMaxN];
vec elements  [kMaxN];
int points    [kMaxN];
int order     [kMaxN];

int cmp(const void*pa,const void*pb){
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int a=*ptra;
    int b=*ptrb;
    if(points[a] == points[b])
        return(&order[a] < &order[b])?-1:1;
    return (points[a] > points[b])?-1:1;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int p = 1; p <= n; p += 1) {
        for (int i = 0; i < n; i += 1) {
            int x;
            scanf("%d", &x);
            elements[p].ptr = pushback(elements[p].ptr, &elements[p].sz ,x);
            has[p][x] = true;
        }
    }
    for (int a = 1; a <= n; a += 1) {
        for (int b = a + 1; b <= n; b += 1) {
            int mx_element = 0;
            int mn_element = kMaxN * kMaxN;
            for(int z=0;z<elements[a].sz;z++){int el = elements[a].ptr[z];
                if (has[b][el]) {
                    mx_element = max(mx_element, el);
                    mn_element = min(mn_element, el);
                }
            }
            int num_a = 0;
            int num_b = 0;
            for(int z=0;z<elements[a].sz;z++){int el = elements[a].ptr[z];
                if (!(mn_element <= el && el <= mx_element)) {
                    num_a += 1;
                }
            }
            for(int z=0;z<elements[b].sz;z++){int el = elements[b].ptr[z];
                if (!(mn_element <= el && el <= mx_element)) {
                    num_b += 1;
                }
            }
            if (num_a == num_b) {
                points[a] += 1;
                points[b] += 1;
            } 
            else if (num_a > num_b) {
                points[a] += 2;
            } 
            else {
                points[b] += 2;
            }
        }
    }

    for (int i = 0; i < n; i += 1) {
        order[i] = i + 1;
    }
    qsort(order, n,sizeof(int),cmp);
    for(int i=0;i<n;i++) {
        printf("%d\n", order[i]);
    }
    return 0;
}


















































