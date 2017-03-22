typedef struct Interval Interval;
int cmp(void*pa,void*pb){
    Interval*a=(Interval*)pa;
    Interval*b=(Interval*)pb;
    return a->end - b->end;
}
int eraseOverlapIntervals(Interval*intervals,int intSz){
    if (intSz == 0) 
        return 0;
    qsort(intervals,intSz,sizeof(Interval),cmp);
    Interval myi=intervals[0];
    int end = myi.end;
    int count = 1;
    for (int i = 1; i < intSz; i++) {
        Interval cur=intervals[i];
        if(cur.start >= end) {
            end = cur.end;
            count++;
        }
    }
    return intSz - count;
}
