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

int*asteroidCollision(int*asteroids, int asteroidsSz, int*rsz){
    vec a = newVec();
    for(int z=0; z<asteroidsSz; z++){int x = asteroids[z];
        if(x >= 0)
            a.ptr = pushback(a.ptr, &a.sz, x);
        else{
            bool bomb = false;
#define a_back a.ptr[a.sz-1]
            while(a.sz && a_back > 0){
                int t = abs(a_back), w = abs(x);
                if(t == w){
                    a.sz--;
                    bomb = true;
                    break;
                }
                else if(t > w){
                    bomb = true;
                    break;
                }
                else
                    a.sz--;
            }
            if(!bomb)
                a.ptr = pushback(a.ptr, &a.sz, x);
        }
    }
   *rsz=   a.sz;
    return a.ptr;
}
