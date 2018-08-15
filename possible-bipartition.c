#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value){
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    int*ptr;
    int sz;
}vec;
vec newVec(){
    vec rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}

enum{ N =(int) 2e3 + 10};
vec a[N];
int c[N];

bool DFS(int u){
    for(int z=0;z<a[u].sz;z++){int v = a[u].ptr[z];
        if(c[v]){
            if(c[v] != -c[u])
                return true;
        }
        else{
            c[v] = -c[u];
            DFS(v);
        }
    }
    return false;
}
bool possibleBipartition(int n, int**dislikes, int dislikesSz, int*dislikes0szs){
    for(int i=0; i<n; ++i)
        a[i].sz=0;
    for(int z=0;z<dislikesSz;z++){int*it = dislikes[z];
        int x = it[0],
            y = it[1];
        --x, --y;
        a[x].ptr = pushback(a[x].ptr, &a[x].sz, y);
        a[y].ptr = pushback(a[y].ptr, &a[y].sz, x);
    }
    fill(c, n, 0);
    for(int i=0; i<n; ++i){
        if(c[i])
            continue;
        c[i] = 1;
        if(DFS(i))
            return false;
    }
    return true;
}
