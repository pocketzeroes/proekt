#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#ifdef _WIN32
  #define inline static
#endif


typedef struct trip{
    int first;
    int second;
    int third;
}trip;
trip newTrip(int a, int b, int c){
    trip rez;
    rez.first =a;
    rez.second=b;
    rez.third =c;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

trip*pushback(trip*array, int *size, trip value){
    trip*output = resizeArray(array, trip, *size + 1);
    output[(*size)++] = value;
    return output;
}

enum{ N = 2010};
typedef struct PointS {
    int64_t x, y;
}Point; 
Point newPoint( int64_t a, int64_t b){
    Point rez;
    rez.x =a;
    rez.y =b;
    return rez;
}

Point polygon[ N ];

trip*tri=NULL;int triSz=0;
int n, m;

bool isLeft( Point a, Point b, Point p ){
    return ( p.x - a.x ) * ( p.y - b.y ) >= ( p.y - a.y ) * ( p.x - b.x );
}
bool inside( Point a, Point b, Point c, Point p ){
    return ( isLeft( a, b, p ) && isLeft( b, c, p ) && isLeft( c, a, p ) );
}

int main() {
    scanf("%d %d", &n, &m);
    for ( int i = 0 ; i < n ; ++i)
        scanf("%lld %lld", &polygon[i].x, &polygon[i].y);
    for ( int i = 0, j = n-1 ; i+1 < j ; ) {
        int c = i+1, d = j-1;
        if ( isLeft( polygon[ i ], polygon[ d ], polygon[ c ] ) ) 
             tri=pushback(tri,&triSz, newTrip( i, j-- , d ));
        else tri=pushback(tri,&triSz, newTrip( i++, j , c ));
    }
    int ans = 0;
    for ( int i = 0 ; i < m ; ++i ) {
        int64_t x, y;
        scanf("%lld %lld", &x, &y);
        Point point = newPoint( x, y );
        bool found = false;
        for(int z=0;z<triSz;z++){
            trip tr=tri[z];
            if ( inside( polygon[ tr.first  ],
                         polygon[ tr.second ],
                         polygon[ tr.third  ],
                         point ) ) {
                found = true;
                break;
            }
        }
        if ( found ) 
            ++ans;
    }
    printf("%d\n", ans);
    return 0;
}
























































