typedef struct {
}BrowserHistory;
BrowserHistory*gptr;

int n,m;
char*a[5005];

BrowserHistory*browserHistoryCreate(char*homepage){
    n=m=0;
    a[0]=strdup(homepage);
    return gptr;
}
void browserHistoryVisit(BrowserHistory* obj, char * url) {
    a[n=m=m+1]=strdup(url);
}
char * browserHistoryBack(BrowserHistory* obj, int steps) {
    steps=fmin(steps,m);
    m-=steps;
    return a[m];
}
char * browserHistoryForward(BrowserHistory* obj, int steps) {
    steps=fmin(steps,n-m);
    m+=steps;
    return a[m];
}
void browserHistoryFree(BrowserHistory* obj) {
    ;
}
