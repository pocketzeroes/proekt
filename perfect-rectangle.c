#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int pointCmp(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    for (int i = 0; i < 2; ++i) {
        if (pa[i] < pb[i]) {
            return -1;
        }
        if (pa[i] > pb[i]) {
            return 1;
        }
    }
    return 0;
}
int rectangleCmp(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    for (int i = 0; i < 4; ++i) {
        if (pa[i] < pb[i]) {
            return -1;
        }
        if (pa[i] > pb[i]) {
            return 1;
        }
    }
    return 0;
}
bool isRectangleCover(int** rectangles, int rectanglesRowSize, int rectanglesColSize) {
    qsort(rectangles, rectanglesRowSize, sizeof(int*), rectangleCmp);
    for (int i = 1; i < rectanglesRowSize; ++i) {
        if (rectangles[i][0] >= rectangles[i - 1][0] &&
            rectangles[i][1] >= rectangles[i - 1][1] &&
            rectangles[i][0] < rectangles[i - 1][2] &&
            rectangles[i][1] < rectangles[i - 1][3]) {
            return false;
        }
    }
    int** points;
    int pointCnt = rectanglesRowSize * 4;
    points = (int**)malloc(pointCnt * sizeof(int*));
    for (int i = 0; i < pointCnt; ++i) {
        points[i] = (int*)malloc(2 * sizeof(int));
    }
    int pointIndex = 0;
    for (int i = 0; i < rectanglesRowSize; ++i) {
        int lx = rectangles[i][0];
        int ly = rectangles[i][1];
        int rx = rectangles[i][2];
        int ry = rectangles[i][3];
        points[pointIndex][0] = lx;
        points[pointIndex++][1] = ly;
        points[pointIndex][0] = rx;
        points[pointIndex++][1] = ry;
        points[pointIndex][0] = lx;
        points[pointIndex++][1] = ry;
        points[pointIndex][0] = rx;
        points[pointIndex++][1] = ly;
    }
    qsort(points, pointCnt, 2 * sizeof(int), pointCmp);
    int leftPoint = pointCnt;
    for (int i = 1; i < pointCnt;) {
        if (points[i][0] == points[i - 1][0] &&
            points[i][1] == points[i - 1][1]) {
            leftPoint -= 2;
            i += 2;
        } 
        else {
            i += 1;
        }
    }
    for (int i = 0; i < pointCnt; ++i) {
        free(points[i]);
    }
    free(points);
    return leftPoint == 4;
}







































































