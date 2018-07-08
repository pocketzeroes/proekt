#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;
bool*prm;
vec primes;

bool is_prm(ll x) {
    if (x < (1<<20))
        return prm[x];
    for(int i=0;i<primes.sz;i++){int y = primes.ptr[i];
        if (0 == x % y) 
            return false;
    }
    return true;
}
ll pal(int x, int i) {
    int y = x;
    if (!i) y /= 10;
    while (y) {
        x = x * 10 + y % 10;
        y /= 10;
    }
    return x;
}
int primePalindrome(int n) {
    prm = calloc(1<<20, sizeof(bool));
    for(int i=0; i<1<<20; i++)
        prm[i]=true;
    prm[0] = prm[1] = false;
    for (int x = 2; x < (1 << 20); ++x) {
        if (prm[x]) {
            primes.ptr = pushback(primes.ptr, &primes.sz, x);
            if (x < (1 << 20) / x) {
                for(int y = x * x; y < (1 << 20); y += x) 
                    prm[y] = false;
            }
        }
    }
    for (int p = 10; true; p *= 10) {
        for (int i = 0; i < 2; ++i) {
            for (int x = p / 10; x < p; ++x) {
                int y = pal(x, i);
                if (y >= n && is_prm(y)){
                    free(prm);
                    return y;
                }
            }
        }
    }
    free(prm);
    return -1;
}
