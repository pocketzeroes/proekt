#include<stdio.h>
#include<math.h>
#include<string.h>

char*point[]={
  "N","NbE","NNE","NEbN","NE","NEbE","ENE","EbN",
  "E","EbS","ESE","SEbE","SE","SEbS","SSE","SbE",
  "S","SbW","SSW","SWbS","SW","SWbW","WSW","WbS",
  "W","WbN","WNW","NWbW","NW","NWbN","NNW","NbW"
};

double p[1000],s[1000],x,y,xx,yy,X,Y,d,dist;
int i,j,k,m,n;
char tmp[100];

int follow(double d){
  int i;
  double dd;
  dist = 0;
  x = 0;
  y = 0;
  dist = hypot(X,Y);
  for(i=0;i<n;i++){
    xx = x + s[i]*cos(p[i]-d);
    yy = y + s[i]*sin(p[i]-d);
    dd = hypot(X-xx,Y-yy);
    if(dd < dist)
      dist = dd;
    if((X-x)*(xx-x)+(Y-y)*(yy-y) > 0 && (X-xx)*(x-xx)+(Y-yy)*(y-yy) > 0){
      dd = fabs(((X-x)*(yy-y) - (Y-y)*(xx-x))/hypot(xx-x,yy-y));
      if(dd < dist)
        dist = dd;
    }
    x = xx;
    y = yy;
  }
}
int main(){
  while(1 == scanf("%d",&n) && n){
    for(i=0;i<n;i++){
      scanf("%s%lf",tmp,&s[i]);
      for(j=0;j<32 && strcmp(tmp,point[j]);j++);
      p[i] = M_PI*j/16;
    }
    scanf("%lf",&d);
    follow(0);
    X = x; Y = y;
    follow(M_PI*d/180);
    printf("%0.2lf\n",dist);
  }
  if(n)
    printf("missing delimter\n");
  return 0;
}
