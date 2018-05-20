
void fill(int*arr, int sz, int val){
    for(int i=0; i<sz; i++)
        arr[i] = val;
}
bool ok(char*a, char*b){
    int diff = 0;
    for(int i=0; a[i]; i++){
        if(a[i] != b[i]){
            diff++;
        }
    }
    return diff <= 2;
}

int*upper;
int upperSz;
void newDJSet(int n){
    upperSz = n;
    upper = calloc(n, sizeof(int));
    fill(upper, n, -1);
}
int root(int x){
    return upper[x] < 0 ? x : (upper[x] = root(upper[x]));
}
bool equiv(int x, int y){
    return root(x) == root(y);
}
bool ds_union(int x, int y){
    x = root(x);
    y = root(y);
    if (x != y) {
        if (upper[y] < upper[x]) {
            int d = x;
            x = y;
            y = d;
        }
        upper[x] += upper[y];
        upper[y] = x;
    }
    return x == y;
}
int count(){
    int ct = 0;
    for(int z=0;z<upperSz;z++){int u = upper[z];
        if (u < 0)
            ct++;
    }
    return ct;
}

int numSimilarGroups(char**A, int Asz){
    int n = Asz;
    newDJSet(n);
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(ok(A[i], A[j])){
                ds_union(i, j);
            }
        }
    }
    return count();
}
