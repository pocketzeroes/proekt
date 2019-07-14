#include<pthread.h>

typedef struct {
    int n;
} FooBar;
pthread_mutex_t f, b;

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    obj->n = n;
    pthread_mutex_lock(&b);
    return obj;
}

void foo(FooBar* obj) {
    
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&f);
      	printFoo();
        pthread_mutex_unlock(&b);
    }
}

void bar(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&b);
       	printBar();
        pthread_mutex_unlock(&f);
    }
}

void fooBarFree(FooBar* obj) {
    pthread_mutex_unlock(&f);
    pthread_mutex_unlock(&b);
}
