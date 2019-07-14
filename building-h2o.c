typedef struct {
    pthread_mutex_t h1_to_o;
    pthread_mutex_t h2_to_o;
    pthread_mutex_t h1;
    pthread_mutex_t h2;
    pthread_mutex_t m;
    int count;
}H2O;

H2O* h2oCreate() {
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    obj->count=(0);
    pthread_mutex_init(&obj->h1_to_o, NULL);
    pthread_mutex_init(&obj->h2_to_o, NULL);
    pthread_mutex_init(&obj->h1, NULL);
    pthread_mutex_init(&obj->h2, NULL);
    pthread_mutex_init(&obj->m , NULL);
    pthread_mutex_lock(&obj->h1_to_o);
    pthread_mutex_lock(&obj->h2_to_o);
    return obj;
}
void hydrogen(H2O* obj) {
    pthread_mutex_lock(&obj->m);
    if(obj->count % 2 == 0)
        pthread_mutex_lock(&obj->h1);
    else
        pthread_mutex_lock(&obj->h2);
    releaseHydrogen();
    if (obj->count++ % 2 == 0)
        pthread_mutex_unlock(&obj->h1_to_o);
    else
        pthread_mutex_unlock(&obj->h2_to_o); 
    pthread_mutex_unlock(&obj->m);
}
void oxygen(H2O*obj){
    pthread_mutex_lock(&obj->h1_to_o);
    pthread_mutex_lock(&obj->h2_to_o);
    releaseOxygen();
    pthread_mutex_unlock(&obj->h1);
    pthread_mutex_unlock(&obj->h2);
}
void h2oFree(H2O* obj) {
  pthread_mutex_unlock(&obj->h1_to_o);
  pthread_mutex_unlock(&obj->h2_to_o);
  pthread_mutex_unlock(&obj->h1);
  pthread_mutex_unlock(&obj->h2);
  pthread_mutex_unlock(&obj->m);
}
