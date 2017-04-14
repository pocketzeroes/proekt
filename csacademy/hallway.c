#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<xmmintrin.h>
#include<mmintrin.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

double min(double a,double b){return a<b?a:b;}
double max(double a,double b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}


double Djk(double**distance, int start, int finish){
    int distance_size = start+2;
    int n = distance_size;
    double min_answer[distance_size];
    for(int i=0;i<distance_size;i++)min_answer[i]=1e8;
    min_answer[start] = 0;
    bool selected[distance_size];
    memset(selected,0,sizeof(selected));
    while(!selected[finish]){
        double mn = 1e9;
        int index = -1;
        for (int itr = 0; itr < n; itr += 1) {
            if (selected[itr]) {
                continue;
            }
            if (min_answer[itr] < mn) {
                mn = min_answer[itr];
                index = itr;
            }
        }
        selected[index] = true;
        for (int itr = 0; itr < n; itr += 1) {
            double cost = max(min_answer[index], distance[index][itr]);
            if (cost < min_answer[itr]) {
                min_answer[itr] = cost;
            }
        }
    }
    return min_answer[finish];
}

double asmSqrt(double x) {
  __asm__ ("fsqrt" : "+t" (x));
  return x;
}
#define USE_FAST 1
double Distance(pair a, pair b) {
#if USE_FAST
    return asmSqrt(1.0 * (a.first  - b.first ) * (a.first  - b.first ) + 1.0 * (a.second - b.second) * (a.second - b.second));
#else
    return sqrt   (1.0 * (a.first  - b.first ) * (a.first  - b.first ) + 1.0 * (a.second - b.second) * (a.second - b.second));
#endif
}
double Solve(pair*coordinates,int sz, int h){
    int num_points = sz;
    double**distance=malloc((num_points+2)*sizeof(double*));//[num_points+2][num_points+2];
    for(int i=0;i<num_points+2;i++)distance[i]=malloc((num_points+2)*sizeof(double));
    for (int i = 0; i < num_points; i++){
        for (int j = 0; j < num_points; j++){
            distance[i][j] = Distance(coordinates[i], coordinates[j]);
        }
        distance[i][num_points]     = Distance(coordinates[i], newPair(coordinates[i].first, 0));
        distance[i][num_points + 1] = Distance(coordinates[i], newPair(coordinates[i].first, h));
        distance[num_points][i]     = distance[i][num_points];
        distance[num_points + 1][i] = distance[i][num_points + 1];
    }
    distance[num_points][num_points + 1] = h;
    distance[num_points + 1][num_points] = h;
    return Djk(distance, num_points, num_points + 1) / 2.0;    
}
int main() {
    int w, h, num_points; 
    scanf("%d %d %d", &w, &h, &num_points);
    assert(1 <= w);
    assert(w <= (int)1e6);
    assert(1 <= h);
    assert(h <= (int)1e6);
    assert(1 <= num_points);
    assert(num_points <= (int)5e3);
    pair*coordinates=NULL;int coordinatesSz=0;
    for (int i = 0; i < num_points; i += 1){
        int x, y; 
        scanf("%d %d", &x, &y);
        assert(1 <= x);
        assert(x < w);
        assert(1 <= y);
        assert(y < h);
        coordinates=pushbackP(coordinates, &coordinatesSz, newPair(x, y));
    }
    printf("%lf\n", Solve(coordinates, coordinatesSz, h));
    return 0;
}



























