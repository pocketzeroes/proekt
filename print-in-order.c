typedef struct {
    int a;
    int b;
} Foo;
Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    obj->a = obj->b = 0;
    return obj;
}
void first(Foo* obj) {
    printFirst();
    obj -> a = 1;
}
void second(Foo* obj) {
    while (!obj->a)
        ;
    printSecond();
    obj->b = 1;
}
void third(Foo* obj) {
    while (!obj->b)
        ;
    printThird();
}
void fooFree(Foo* obj) {
  ;    
}
