typedef struct {
}StockSpanner;
StockSpanner*gptr;

int*stack;
int*value;
int sp;
int gen = 0;

StockSpanner*stockSpannerCreate(){
    stack = calloc(11000, sizeof(int));
    value = calloc(11000, sizeof(int));
    sp    = 0;
    gen   = 0;
    return gptr;
}
int stockSpannerNext(StockSpanner* obj, int price) {
    while(sp > 0 && value[sp-1] <= price)
        sp--;
    int ret = gen - (sp == 0 ? -1 : stack[sp-1]);
    stack[sp] = gen++;
    value[sp] = price;
    sp++;
    return ret;
}
void stockSpannerFree(StockSpanner* obj){
    free(stack);
    free(value);
    return 0;
}
