#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct RectS{
  int x1, y1, x2, y2;
}Rectangle;


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Rectangle *pushback(Rectangle *array, int *size, Rectangle value) {
    Rectangle *output = resizeArray(array, Rectangle, *size + 1);
    output[(*size)++] = value;
    return output;
}
  


int n;
Rectangle*rectangles=NULL;int rectanglesSz=0;

void read(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        Rectangle rect;
        scanf("%d %d %d %d", &rect.x1, &rect.y1, &rect.x2, &rect.y2);
        rectangles=pushback(rectangles, &rectanglesSz, rect);
    }
}
bool disjointSegments(int l1, int r1, int l2, int r2) {
    return r1 <= l2 || r2 <= l1;
}
bool disjointRectangles(Rectangle a, Rectangle b){
    return disjointSegments(a.x1, a.x2, b.x1, b.x2) || 
           disjointSegments(a.y1, a.y2, b.y1, b.y2);
}
int main() {
    read();
    int totalPairs = n * (n - 1) / 2;
    int disjointCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (disjointRectangles(rectangles[i], rectangles[j])) {
                disjointCount++;
            }
        }
    }
    printf("%d\n", (totalPairs - disjointCount) );
}













