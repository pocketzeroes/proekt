#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

double chord_length(double x, double y, double z){
  return x*x + y*y + z*z;
}
typedef struct node{
  double x, y, z;
  double phi_deg;
  double gamma_deg;
  double max_distance;
}node;

int main(){
  unsigned n;
  while(scanf("%u", &n) == 1){
    node hub[n]; memset(hub, 0, sizeof(hub));
    for(unsigned i = 0; i < n; ++i){
      double phi, gamma;
      scanf("%lf %lf", &phi, &gamma);
      hub[i].phi_deg = phi;
      hub[i].gamma_deg = gamma;
      phi *= M_PI/180;
      gamma *= M_PI/180;
      hub[i].x = cos(phi) * cos(gamma);
      hub[i].y = cos(phi) * sin(gamma);
      hub[i].z = sin(phi);
      for(unsigned j = 0; j < i; ++j){
        double d = chord_length(fabs(hub[i].x - hub[j].x), fabs(hub[i].y - hub[j].y), fabs(hub[i].z - hub[j].z));
        if(d > hub[i].max_distance) 
          hub[i].max_distance = d;
        if(d > hub[j].max_distance) 
          hub[j].max_distance = d;
      }
    }
    double min_distance = 1e9;
    unsigned best_choice;
    for(unsigned i = 0; i < n; ++i){
      if(hub[i].max_distance <= min_distance){
        min_distance = hub[i].max_distance;
        best_choice = i;
      }
    }
    printf("%.2lf %.2lf\n", hub[best_choice].phi_deg, hub[best_choice].gamma_deg);
  }
  return 0;
}

