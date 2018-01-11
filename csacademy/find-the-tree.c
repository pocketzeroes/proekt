#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>




void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void erase(vec*v, int pos){
    for(int i=pos; i < v->sz-1; i++){
        v->ptr[i] = v->ptr[i+1];
    }
    (v->sz)--;
}

typedef long long ll;
enum{ MAXN=2000};
int n;
bool alive  [MAXN];
bool skip   [MAXN];
vec  adj    [MAXN];
int  prv    [MAXN];
int  path   [MAXN],npath;
int  pathidx[MAXN];
int  q      [MAXN],qhead,qtail;

int farthest(int s){
    for(int i=(0);i<(n);++i)
        prv[i]=-2;
    qhead=qtail=0;
    prv[s]=-1;
    q[qhead++]=s;
    while(qtail<qhead){
        int at=q[qtail++];
        for(int i=0; i<adj[at].sz; ++i){
            int to=adj[at].ptr[i];
            if(skip[to]||prv[to]!=-2)
                continue;
            prv[to]=at;
            q[qhead++]=to;
        }
    }
    return q[qtail-1];
}
int query(int a, int b, int c){
    printf("Q %d %d %d",a+1,b+1,c+1); fflush(stdout);
    int ret;
    scanf("%d",&ret);
    --ret;
    return ret;
}
void addedge(int a, int b){
    adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
    adj[b].ptr = pushback(adj[b].ptr, &adj[b].sz, a);
}
void remedge(int a, int b){
    bool afound=false;
    for(int i=0; i<adj[a].sz; ++i)
        if(adj[a].ptr[i]==b){
            erase(&adj[a], i);
            afound=true;
            break;
        }
    bool bfound=false;
    for(int i=0; i<adj[b].sz; ++i)
        if(adj[b].ptr[i]==a){
            erase(&adj[b], i);
            bfound=true;
            break;
        }
    assert(afound&&bfound);
}
int main(){
    scanf("%d",&n);
    for(int i=(0);i<(n);++i)
        alive[i]=false;
    addedge(0,1);
    alive[0]=alive[1]=true;
    for(int i=(2);i<(n);++i)
        if(!alive[i]){
        for(int j=(0);j<(n);++j)
            skip[j]=false;
        int at=0;
        while(true){
            int a=farthest(at),
                b=farthest(a);
            npath=0;
            for(int c=b;c!=-1;c=prv[c])
                path[npath++]=c;
            reverse(path, 0, npath-1);
            for(int j=(0);j<(n);++j)
                pathidx[j]=-1;
            for(int j=(0);j<(npath);++j)
                pathidx[path[j]]=j;
            if(npath==1) {
                alive[i]=true;
                addedge(path[0],i);
                break;
            }
            int d=query(a,b,i);
            if(alive[d]) {
                assert(pathidx[d]!=-1);
                if(pathidx[d]==0) {
                    alive[i]=true;
                    addedge(d,i);
                    break;
                }
                if(pathidx[d]==npath-1) {
                    alive[i]=true;
                    addedge(d,i);
                    break;
                }
                skip[path[pathidx[d]-1]]=skip[path[pathidx[d]+1]]=true;
                at=d;
                continue;
            }
            else{
                int l=0,h=npath-1;
                while(l+1<h){
                    int m=l+(h-l)/2;
                    int e=query(path[0],path[m],i);
                    assert(e==d||e==path[m]);
                    if(e==path[m])
                        l=m;
                    else
                        h=m;
                }
                alive[i]=alive[d]=true;
                remedge(path[h-1], path[h]);
                addedge(path[h-1],d);
                addedge(d,path[h]);
                addedge(d,i);
                break;
            }
        }
    }
    printf("A\n");
    for(int i=(0);i<(n);++i)
        for(int j=(0);j<adj[i].sz;++j){
            int k=adj[i].ptr[j];
            if(i<k)
                printf("%d %d\n", i+1, k+1);
        }
    return 0;
}


