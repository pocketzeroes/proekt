bool onSameLine(long ax, long ay, long bx, long by, long cx, long cy){
    return (cx-ax)*(by-ay)-(cy-ay)*(bx-ax)==0;
}
bool isBoomerang(int**points, int pointsSz, int*points0sz){
    for(int i = 0;i < 3;i++)
        for(int j = i+1;j < 3;j++)
            if(points[i][0] == points[j][0]&&
               points[i][1] == points[j][1]  )
                  return false;
    return!onSameLine(points[0][0], points[0][1], points[1][0], points[1][1], points[2][0], points[2][1]);
}
