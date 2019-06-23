#define DBL_MAX    1.7976931348623157E+308
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}

double*sampleStats(int*count, int countSz, int*rsz){
    int n = countSz;
    double mn = DBL_MAX;
    double mx = -1.;
    double s = 0.;
    int all  = 0;
    int mode = -1;
    int best = -1;
    for(int i = 0;i < n;i++){
        if(count[i] > 0){
            mn = min(mn, i);
            mx = max(mx, i);
            s += (double)count[i] * i;
            all += count[i];
            if(count[i] > best){
                best = count[i];
                mode = i;
            }
        }
    }
    double med = 0.;
    if(all % 2 != 0){
        int u = 0;
        for(int i = 0;i < n;i++){
            u += count[i];
            if(u >= (all+1)/2){
                med = i;
                break;
            }
        }
    }
    else{
        int u = 0;
        for(int i = 0;i < n;i++){
            u += count[i];
            if(u >= all/2){
                med +=(double) i;
                break;
            }
        }
        u = 0;
        for(int i = 0;i < n;i++){
            u += count[i];
            if(u >= all/2+1){
                med +=(double) i;
                break;
            }
        }
        med /= 2.;
    }
    double*rv = calloc(5, sizeof(double));
    rv[0] = mn  ;  
    rv[1] = mx  ;  
    rv[2] = s/(double)all; 
    rv[3] = med ; 
    rv[4] = mode; 
   *rsz=5;
    return rv;
}
