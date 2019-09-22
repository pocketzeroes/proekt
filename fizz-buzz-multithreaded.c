typedef struct{
    int             n;
    int             counter;
    pthread_mutex_t m1_;
}FizzBuzz;

FizzBuzz*fizzBuzzCreate(int n){
    FizzBuzz*obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->counter = 1;
    pthread_mutex_init(&obj->m1_, NULL);
    return obj;
}
void fizz(FizzBuzz*obj){
    while(1){
        pthread_mutex_lock(&obj->m1_);
        if(obj->counter > obj->n){
            pthread_mutex_unlock(&obj->m1_);
            return;
        }
        if(obj->counter % 3 == 0 &&
           obj->counter % 5 != 0){
            printFizz();//puts("fizz");
            obj->counter++;
        }
        pthread_mutex_unlock(&obj->m1_);
    }
}
void buzz(FizzBuzz* obj) {
    while(1){
        pthread_mutex_lock(&obj->m1_);
        if(obj->counter > obj->n){
            pthread_mutex_unlock(&obj->m1_);
            return;
        }
        if(obj->counter % 3 != 0 &&
           obj->counter % 5 == 0){
            printBuzz();//puts("buzz");
            obj->counter++;
        }
        pthread_mutex_unlock(&obj->m1_);
    }
}
void fizzbuzz(FizzBuzz* obj) {
    while (1){
        pthread_mutex_lock(&obj->m1_);
        if(obj->counter > obj->n){
            pthread_mutex_unlock(&obj->m1_);
            return;
        }
        if(obj->counter % 3 == 0 &&
           obj->counter % 5 == 0){
            printFizzBuzz();//puts("fizzbuzz");
            obj->counter++;
        }
        pthread_mutex_unlock(&obj->m1_);
    }
}
void number(FizzBuzz* obj) {
    while(1){
        pthread_mutex_lock(&obj->m1_);
        if(obj->counter > obj->n){
            pthread_mutex_unlock(&obj->m1_);
            return;
        }
        if(obj->counter % 3 != 0 &&
           obj->counter % 5 != 0){
            printNumber(obj->counter);//printf("%d\n", obj->counter);
            obj->counter++;
        }
        pthread_mutex_unlock(&obj->m1_);
    }
}
void fizzBuzzFree(FizzBuzz* obj) {
    free(obj);
}
