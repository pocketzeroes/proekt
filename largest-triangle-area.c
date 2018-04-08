double d(int*a, int*b){
    int x = abs(a[0]-b[0]), 
        y = abs(a[1]-b[1]);
    return sqrt(x*x+y*y);
}
double ar(double a, double b, double c) {
    double p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
double largestTriangleArea(int**points, int pointsSz, int*pointsSzs){
    double ans = 0;
    int n = pointsSz;
    for (int i=0; i<n; ++i)
        for (int j=i+1; j<n; ++j)
            for (int k=j+1; k<n; ++k) {
                double l1=d(points[i], points[j]), 
                       l2=d(points[i], points[k]), 
                       l3=d(points[j], points[k]);
                double area = ar(l1, l2, l3);
                if (area>ans) 
                    ans = area;
            }
    return ans;
}
