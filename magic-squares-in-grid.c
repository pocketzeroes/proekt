int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int numMagicSquaresInside(int**grid, int gridSz, int*grid0sz){
    int N = gridSz;
    if (N == 0)
        return 0;
    int M = grid0sz[0];
    int ans = 0;
    for(int i=0, i_len=(N-2); i<i_len; ++i){
        for(int j=0, j_len=(M-2); j<j_len; ++j){
            int A[3][3];
            vec v = newVec();
            for(int a=0, a_len=(3); a<a_len; ++a){
                for(int b=0, b_len=(3); b<b_len; ++b) {
                    A[a][b] = grid[i+a][j+b];
                    v.ptr = pushback(v.ptr, &v.sz, A[a][b]);
                }
            }
            bool ok = true;
            for(int a=0, a_len=(3); a<a_len; ++a) {
                int s = 0;
                for(int b=0, b_len=(3); b<b_len; ++b)
                    s += A[a][b];
                ok = (ok && s == 15);
            }
            for(int b=0, b_len=(3); b<b_len; ++b) {
                int s = 0;
                for(int a=0, a_len=(3); a<a_len; ++a)
                  s += A[a][b];
                ok = (ok && s == 15);
            }
            ok = (ok && A[0][0] + A[1][1] + A[2][2] == 15);
            ok = (ok && A[0][2] + A[1][1] + A[2][0] == 15);
            qsort(v.ptr, v.sz, sizeof(int), cmp);
            for(int t=0, t_len=(9); t<t_len; ++t)
                ok = (ok && v.ptr[t] == t+1);
            if (ok)
                ans++;
        }
    }
    return ans;
}
