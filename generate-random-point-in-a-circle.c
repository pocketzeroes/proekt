typedef struct{
    double radius;
    double x_center;
    double y_center;
}Solution;
Solution*solutionCreate(double radius, double x_center, double y_center){
    Solution *solution = malloc(sizeof(Solution));
    solution->radius   = radius;
    solution->x_center = x_center;
    solution->y_center = y_center;
    return solution;
}
double*solutionRandPoint(Solution*obj, int*returnSize){
    *returnSize = 2;
    double *ret = malloc(*returnSize * sizeof(double));
    double theta = (double) rand() / RAND_MAX * atan(1) * 8;
    double scale = (double) rand() / RAND_MAX;
    ret[0] = obj->x_center + obj->radius * sqrt(scale) * cos(theta);
    ret[1] = obj->y_center + obj->radius * sqrt(scale) * sin(theta);
    return ret;
}
void solutionFree(Solution* obj) {
    free(obj);
}
