#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
    int x1, y1;
    double angle;
}Point;


int main(){
    int points;
    while(scanf("%d", &points)==1 && points != 0){
        Point shape[points];
        bool stillGood = true;
        for(int i=0; i<points; ++i)
            scanf("%d %d", &shape[i].x1, &shape[i].y1);
        for(int i=0; i<points; i++){
            Point one    = shape[i % points],
                  center = shape[(i + 1) % points],
                  two    = shape[(i + 2) % points];
            int v1x = one.x1 - center.x1,
                v1y = one.y1 - center.y1,
                v2x = two.x1 - center.x1,
                v2y = two.y1 - center.y1;
            shape[(i + 1) % points].angle = atan2(v2y, v2x) - atan2(v1y, v1x);
            if(shape[(i + 1) % points].angle < 0)
               shape[(i + 1) % points].angle = 2 * M_PI + shape[(i + 1) % points].angle;
            shape[(i + 1) % points].angle *= 180 / M_PI;
        }
        while(stillGood && points >= 4){
            double smallest = 180;
            int    pos      = 0;
            double total    = 0;
            for (int i = 1; i <= points; ++i){
                if (smallest > shape[(i) % points].angle){
                    smallest = shape[(i) % points].angle;
                    pos = (i) % points;
                }
                total += shape[i % points].angle;
            }
            int oneN = pos - 1,
                oneP = pos + 1,
                twoN = pos - 2,
                twoP = pos + 2;
            if(pos == 0){
                oneN = points - 1;
                twoN = points - 2;
            }
            if(pos == 1)
                twoN = points - 1;
            int v1x = shape[oneN % points].x1 - shape[oneP % points].x1,
                v1y = shape[oneN % points].y1 - shape[oneP % points].y1,
                v2x = shape[twoP % points].x1 - shape[oneP % points].x1,
                v2y = shape[twoP % points].y1 - shape[oneP % points].y1,
                v3x = shape[twoN % points].x1 - shape[oneN % points].x1,
                v3y = shape[twoN % points].y1 - shape[oneN % points].y1,
                v4x = shape[oneP % points].x1 - shape[oneN % points].x1,
                v4y = shape[oneP % points].y1 - shape[oneN % points].y1;
            double angle2 = atan2(v2y, v2x) - atan2(v1y, v1x),
                   angle1 = atan2(v4y, v4x) - atan2(v3y, v3x);
            if(angle1 < 0)
               angle1 = 2 * M_PI + angle1;
            if(angle2 < 0)
               angle2 = 2 * M_PI + angle2;
            angle1 *= 180 / M_PI;
            angle2 *= 180 / M_PI;

void erase(Point*v, int poz){
    for(int i=poz; i < points-1; i++)
        v[i] = v[i+1];
    points--;
}

            if(angle1 > smallest && angle2 > smallest){
                shape[oneN % points].angle = angle1;
                shape[oneP % points].angle = angle2;
                erase(shape, pos);
            }
            else
                stillGood = false;
        }
        printf("%d ", points);
        for(int i=0; i<points; i++)
            printf("%d %d ", shape[i].x1, shape[i].y1);
        puts("");
    }
    return 0;
}
