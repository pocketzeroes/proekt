bool validSquare(int*p1, int _q, int*p2, int _w, int*p3, int _z, int*p4,int _x){
    int a[2] = {p1[0] - p2[0], p1[1] - p2[1]};
    int b[2] = {p1[0] - p3[0], p1[1] - p3[1]};
    if(a[0] * b[0] + a[1] * b[1])
    {
        if(a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1])
        {
            int*tt=p3; p3=p4; p4=tt;
            b[0] = p1[0] - p3[0]; 
            b[1] = p1[1] - p3[1];
        }
        else if(a[0] * a[0] + a[1] * a[1] > b[0] * b[0] + b[1] * b[1])
        {
            int*tt=p2; p2=p4; p4=tt;
            a[0] = p1[0] - p2[0]; 
            a[1] = p1[1] - p2[1];
        }
        else 
            return false;
        if(a[0] * b[0] + a[1] * b[1]) 
            return false;
    }
    if(a[0] * a[0] + a[1] * a[1] != b[0] * b[0] + b[1] * b[1]) 
        return false;
    if(a[0] == 0 && a[1] == 0) 
        return false;
    int c[2] = {p4[0] - p2[0], p4[1] - p2[1]};
    int d[2] = {p4[0] - p3[0], p4[1] - p3[1]};
    return c[0] * d[0] + c[1] * d[1] == 0 && c[0] * c[0] + c[1] * c[1] != 0 && d[0] * d[0] + d[1] * d[1] != 0;
}
