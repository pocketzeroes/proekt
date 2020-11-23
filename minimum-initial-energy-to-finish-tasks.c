int minimumEffort(int**tasks, int tasksSz, int*tasks0sz){
    int teng = 0;
    int mindiff = INT_MAX;
    int maxeng = 0;
    for(int z=0;z<tasksSz;z++){int*x = tasks[z];
        teng += x[0];
        mindiff = fmin(mindiff, (x[1]-x[0]));
        maxeng = fmax(maxeng, x[1]);
    }
    teng += mindiff;        
    return fmax(teng, maxeng);
}
