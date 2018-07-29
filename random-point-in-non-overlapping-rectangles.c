typedef struct{
    int rectsSize;
    int **rects;
    double *distribution;
}Solution;
Solution*solutionCreate(int**rects, int rectsSize){
    double*distribution = malloc(rectsSize * sizeof(double));
    double*areas        = malloc(rectsSize * sizeof(double));
    double sum = 0;
    for(int i=0; i<rectsSize; i++){
        areas[i] = (rects[i][2] - rects[i][0] + 1) * (rects[i][3] - rects[i][1] + 1);
        sum += areas[i];
    }
    for(int i=0; i<rectsSize; i++){
        distribution[i] = 0;
        for (int j = 0; j <= i; j++)
            distribution[i] += areas[j] / sum;
    }
    Solution*obj      = malloc(sizeof(Solution));
    obj->rectsSize    = rectsSize;
    obj->rects        = rects;
    obj->distribution = distribution;
    free(areas);
    return obj;
}
int*solutionPick(Solution*obj, int*returnSz){
    double pickRect = (double) rand() / RAND_MAX;
    int i;
    for(i=0; pickRect>obj->distribution[i]; i++);
    double x = (obj->rects)[i][0] + (double) rand() / RAND_MAX * ((obj->rects)[i][2] - (obj->rects)[i][0] + 1) - 0.5;
    double y = (obj->rects)[i][1] + (double) rand() / RAND_MAX * ((obj->rects)[i][3] - (obj->rects)[i][1] + 1) - 0.5;
    int *ret = malloc(2 * sizeof(int));
    ret[0]   = round(x);
    ret[1]   = round(y);
   *returnSz = 2;
    return ret;
}
void solutionFree(Solution* obj) {
    free(obj);
}
