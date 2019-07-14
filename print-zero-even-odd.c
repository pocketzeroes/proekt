#include<pthread.h>
typedef struct{
    int n;
    int t;
    pthread_mutex_t m1;// = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t m2;// = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t m3;// = PTHREAD_MUTEX_INITIALIZER;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n) {
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    pthread_mutex_init(&obj->m1,NULL);
    pthread_mutex_init(&obj->m2,NULL);
    pthread_mutex_init(&obj->m3,NULL);
    
    pthread_mutex_lock(&obj->m1);
    pthread_mutex_lock(&obj->m2);
    pthread_mutex_lock(&obj->m3);
    obj->t = 0;
    return obj;
}
void zero(ZeroEvenOdd* obj) {
    pthread_mutex_unlock(&obj->m3);
    for(int i = 0; i < obj->n; i++){
        pthread_mutex_lock(&obj->m3);
        printNumber(0);
        if (obj->t == 0)  obj->t=1, pthread_mutex_unlock(&obj->m1);
        else         obj->t=0, pthread_mutex_unlock(&obj->m2);
    }
}
void even(ZeroEvenOdd* obj) {
    for (int i = 2; i <= obj->n; i+=2){
        pthread_mutex_lock  (&obj->m2);
        printNumber(i);        
        pthread_mutex_unlock(&obj->m3);            
    }
}
void odd(ZeroEvenOdd* obj) {
    for (int i = 1; i <= obj->n; i+=2){
        pthread_mutex_lock  (&obj->m1);
        printNumber(i);            
        pthread_mutex_unlock(&obj->m3);
    }
}
void zeroEvenOddFree(ZeroEvenOdd*obj){
    pthread_mutex_unlock(&obj->m1);
    pthread_mutex_unlock(&obj->m2);
    pthread_mutex_unlock(&obj->m3);
}
