inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
bool isRectangleOverlap(int*a, int rec1Size, int*b, int rec2Size){
    return max(a[0], b[0]) < min(a[2], b[2]) &&
           max(a[1], b[1]) < min(a[3], b[3]);
}
