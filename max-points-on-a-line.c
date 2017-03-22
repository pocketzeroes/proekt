typedef struct Point Point ;

int cmp(Point* a,Point* b){
    return a->x < b->x || (a->x == b->x && a->y < b->y);
}
bool isOneLine(const Point* p1, const Point* p2, const Point* p3) {
    if ((p2->y - p1->y)*(p3->x - p1->x) == (p3->y - p1->y)*(p2->x - p1->x)) {
        if ((p2->y - p1->y) == 0 && (p3->y - p1->y) == 0)
            return true;
        if ((p3->x - p1->x) == 0 && (p2->x - p1->x) == 0)
            return true;
        if ((p2->y - p1->y) != 0 && (p3->y - p1->y) != 0 &&
            (p3->x - p1->x) != 0 && (p2->x - p1->x) != 0)
            return true;
    }
    return false;
}
bool equalPoint(Point* p1,Point* p2) {
    return p1->x == p2->x && p1->y == p2->y;
}
int maxPoints(struct Point* points, int pointsSize)
{
    if (pointsSize < 3)
        return pointsSize;
    qsort(points, pointsSize,sizeof(Point), cmp);
    int maxPoint = -1;
    for (int i = 0; i < pointsSize-2; ++i) {
        int samePointCount = 0;
        for (int j = i+1; j < pointsSize-1; ++j) {
            if (equalPoint(&points[i], &points[j])) {
                samePointCount ++;
                continue;
            }
            int current_point_numbers = 2;
            for (int k = j+1; k < pointsSize; ++k) {
                if (isOneLine(&points[i], &points[j], &points[k])) {
                    current_point_numbers ++;
                }
            }
            current_point_numbers += samePointCount;
            if (current_point_numbers > maxPoint) {
                maxPoint = current_point_numbers;
            }
        }
    }
    if (maxPoint == -1) {
        return pointsSize;
    }
    maxPoint = maxPoint > pointsSize ? pointsSize : maxPoint;
    return maxPoint;
}



