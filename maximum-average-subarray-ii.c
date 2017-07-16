#define DBL_MAX    1.7976931348623157E+308
double min(double a,double b){return a<b?a:b;}
int nums_length;

bool ok(double h, int*nums, int k){
    int n = nums_length;
    double*cum = calloc(n+1, sizeof(double));
    for(int i = 0;i < n;i++){
        cum[i+1] = cum[i] + nums[i] - h;
    }
    double mn = DBL_MAX;
    for(int i = k-1;i < n;i++){
        mn = min(mn, cum[i-(k-1)]);
        if(cum[i+1] - mn >= 0){
            free(cum);
            return true;
        }
    }
    free(cum);
    return false;
}
double findMaxAverage(int* nums, int numsSz, int k){
    nums_length = numsSz;
    double low = -12345., high = 12345.;
    for(int rep = 0;rep < 100;rep++){
        double h = (low+high)/2.;
        if(ok(h, nums, k)){
            low = h;
        }
        else{
            high = h;
        }
    }
    return low;
}
