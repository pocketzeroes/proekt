#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>
#include<stddef.h>


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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef uint_least8_t  u8   ;
typedef int_least32_t  i32  ;
typedef uint_least32_t u32  ;
typedef ptrdiff_t      isize;
typedef size_t         usize;

isize input(vec*in){
    char c;
    isize cnt = 0;
    while(c = fgetc(stdin), c == '\n');
    do{
        if (c == '(') {
            in->ptr = pushback(in->ptr, &in->sz, 0);
            ++cnt;
        }
        else{
            in->ptr = pushback(in->ptr, &in->sz, 1);
            --cnt;
        }
    } 
    while(c = fgetc(stdin), c != '\n');
    return cnt;
}
bool is_valid(vec*s){
    usize st[2] = { 0,0 };
    u8 f[2] = { 1,1 };
    for(int z=0;z<s->sz;z++){char d = s->ptr[z];
        if (d & 2) {
            if (d & 1) {
                --st[0];
                --st[1];
            }
            else {
                ++st[0];
                ++st[1];
            }
        }
        else {
            if (d & 1) {
                --st[f[1] ^= 1];
            }
            else {
                ++st[f[0] ^= 1];
            }
        }
        if (!~st[0] || !~st[1])
            return false;
    }
    return true;
}
void output(vec*s){
    char c[2] = { 'R','R' };
    const char flip = 'R'^'B';
    for(int z=0;z<s->sz;z++){char d = s->ptr[z];
        if (d & 2) {
            fputc('G', stdout);
        }
        else {
            fputc(c[d] ^= flip, stdout);
        }
    }
    fputc('\n', stdout);
}
isize find_l(vec s, isize left) {
    isize len = s.sz;
    while (++left, left < len && s.ptr[left] & 1);
    return left;
}
isize find_r(vec s, isize right){
    while (--right, right >= 0 && !(s.ptr[right] & 1));
    return right;
}
int main(){
    u32 t;
    scanf("%u", &t);
    while(t--){
        vec s=newVec();
        isize cnt = input(&s);
        isize len = s.sz;
        isize left  = -1, 
              right = len;
        if (cnt < 0) {
            left  = find_l(s, left);
            right = find_r(s, right);
            while (left < len&&cnt < 0) {
                s.ptr[left] |= 2;
                ++cnt;
                left = find_l(s, left);
            }
            if (cnt < 0) {
                puts("impossible");
                continue;
            }
            while (left < right) {
                s.ptr[left] |= 2;
                s.ptr[right] |= 2;
                left  = find_l(s, left);
                right = find_r(s, right);
            }
        }
        else {
            left  = find_l(s, left);
            right = find_r(s, right);
            while (right >= 0 && cnt > 0) {
                s.ptr[right] |= 2;
                --cnt;
                right = find_r(s, right);
            }
            if (cnt > 0) {
                puts("impossible");
                continue;
            }
            while (left < right) {
                s.ptr[left ] |= 2;
                s.ptr[right] |= 2;
                left  = find_l(s, left);
                right = find_r(s, right);
            }
        }
        if (is_valid(&s))
            output(&s);
        else
            puts("impossible");
    }
    return 0;
}
