#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXN (20)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MARGIN (1e-7)
#define SWEEPMARGIN (1e-10)
#define MIN(a,b) ((a)<(b)?(a):(b))

int x[MAXN][4];
int y[MAXN][4];
int n;
int len;
double xs, ys;

typedef struct{
  double a;
  int    p;
  int    s;
  int    id;
}event;
event rsweep[MAXN*8];

int cmp(const void *a, const void *b){
  double diff = ((event*)a)->a - ((event*)b)->a;
  if (diff < -MARGIN) return -1;
  if (diff > MARGIN) return 1;
  return ((event*)a)->s - ((event*)b)->s;
}
typedef struct{
  int id;
  double dist;
}pt;

pt gpt[2][MAXN];

int ptcmp(const void *a, const void *b){
  double da = ((pt*)a)->dist;
  double db = ((pt*)b)->dist;
  if (da < db)
    return -1;
  else if (da > db)
    return 1;
  else return 0;
}
double computedist(double angle, int who){
  int i;
  if (who == -1) 
    return 0.0;
  double best = 1e8;
  for (i = 0; i < 4; i++){
    double x1, y1;
    double dist = 1e8;
    if (i&1) {
      y1 = y[who][i];
      if (fabs(sin(angle)) > 1e-8){
        double t = (y1-ys)/sin(angle);
        x1 = xs + t * cos(angle);
        if (x1 >= MIN(x[who][i], x[who][(i+1) & 3]) &&
            x1 <= MAX(x[who][i], x[who][(i+1) & 3])) {
            dist = sqrt((x1-xs)*(x1-xs)+(y1-ys)*(y1-ys));
        }
      }
    }
    else {
      x1 = x[who][i];
      if (fabs(cos(angle)) > 1e-8) {
        double t = (x1-xs)/cos(angle);
        y1 = ys + t * sin(angle);
        if (y1 >= MIN(y[who][i], y[who][(i+1) & 3]) &&
            y1 <= MAX(y[who][i], y[who][(i+1) & 3])) {
            dist = sqrt((x1-xs)*(x1-xs)+(y1-ys)*(y1-ys));
        }
      }
    }
    if (dist < best)
      best = dist;
  }
  return best;
}
double search(int pid, int nid, double lo, double hi, double *dir){
  double mid = (lo + hi) / 2;
  if (hi - lo < SWEEPMARGIN) {
    *dir = mid;
    return computedist(mid, pid) + computedist(mid, nid);
  }
  else {
    double val = computedist(mid, pid) + computedist(mid, nid);
    double valf = computedist(mid + SWEEPMARGIN, pid) + computedist(mid + SWEEPMARGIN, nid); 
    if (valf > val)
      return search(pid, nid, lo, mid, dir);
    else 
      return search(pid, nid, mid, hi, dir);
  }  
}
int main(){
  int i, j, k, l, m;
  int best = 0;
  double bestx0 = 0;
  double besty0 = 0;
  double bestx1 = 0;
  double besty1 = 0;
  scanf("%d %d", &n, &len);
  best = n > 0 ? 1 : 0;
  for (i = 0; i < n; i++) {
    int xmin, xmax, ymin, ymax;
    scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);
    x[i][0] = xmin;
    y[i][0] = ymin;
    x[i][1] = xmin;
    y[i][1] = ymax;
    x[i][2] = xmax;
    y[i][2] = ymax;
    x[i][3] = xmax;
    y[i][3] = ymin;
  }
  for (i = 0; i < n; i++)
    for (j = 0; j < 4; j++) {
      double angle[4];
      xs = x[i][j];
      ys = y[i][j];
      #if DBG
      if (DBGP==i && DBGC==j)
        printf("Corner: %d:%d\n", i, j);
      #endif
      int nrs = 0;
      for (k = 0; k < n; k++) 
        if (k != i) {
          int secquad = 0;
          for (l = 0; l < 4; l++) {
            int x1 = x[k][l];
            int y1 = y[k][l];
            angle[l] = atan2(y1-ys, x1-xs);
            if (angle[l] < -M_PI/2) secquad = 1;
          }
          if (secquad)
            for (l = 0; l < 4; l++)
              if (angle[l] > M_PI/2) angle[l] -= 2 * M_PI;
          double mina = 4 * M_PI;
          double maxa = -4 * M_PI;
          for (l = 0; l < 4; l++) {
            if (angle[l] < mina) mina = angle[l];
            if (angle[l] > maxa) maxa = angle[l];
          }
        #if DBG
          if (DBGP==i && DBGC==j)
            printf("%d min %1.6lf max %1.6lf\n", k, mina, maxa);
        #endif
          for (m = 0; m < 4; m++) {
            rsweep[nrs].a = mina + M_PI * m;
            rsweep[nrs].p = (m+1)&1;
            rsweep[nrs].s = 0;
            rsweep[nrs++].id = k;
            rsweep[nrs].a = maxa + M_PI * m;
            rsweep[nrs].p = (m+1)&1;
            rsweep[nrs].s = 1;
            rsweep[nrs++].id = k;
          }
        }
      qsort(rsweep, nrs, sizeof(event), cmp);
      int pmask = 0, nmask = 0;
      for (k = 0; k < nrs - 1; k++) {
        double cang = rsweep[k].a;
        int pos = 0, neg = 0;
        gpt[0][neg].dist = 0;
        gpt[0][neg++].id = -1;
        gpt[1][pos].dist = 0;
        gpt[1][pos++].id = -1;
        if (rsweep[k].p)
          pmask ^= (1<<rsweep[k].id);
        else
          nmask ^= (1<<rsweep[k].id);
        for (l = 0; l < n; l++) {
          if (pmask & (1<<l)) {
            double dist = MIN(computedist(cang + MARGIN, l), computedist(cang - MARGIN, l));
            gpt[1][pos].dist = dist;
            gpt[1][pos++].id = l;
          } 
          if (nmask & (1<<l)) {
            double dist = MIN(computedist(cang + MARGIN, l), computedist(cang - MARGIN, l));
            gpt[0][neg].dist = dist;
            gpt[0][neg++].id = l;
          }      
        }
        qsort(gpt[0], neg, sizeof(pt), ptcmp);
        qsort(gpt[1], pos, sizeof(pt), ptcmp);
        for (l = 0; l < pos; l++) {
          for (m = 0; m < neg; m++) {
            if (l+m+1 > best) {
              double dir;
              double shortest = search(gpt[1][l].id, gpt[0][m].id, cang, rsweep[k+1].a, &dir);
            #if DBG
              if (DBGP==i && DBGC==j) {
                printf("shortest=%1.8lf\n", shortest);
              }
            #endif
              if (shortest <= len + MARGIN) {
                best = l+m+1;
                bestx0 = xs + cos(dir) * computedist(dir, gpt[1][l].id);
                besty0 = ys + sin(dir) * computedist(dir, gpt[1][l].id);
                bestx1 = xs - cos(dir) * computedist(dir, gpt[0][m].id);
                besty1 = ys - sin(dir) * computedist(dir, gpt[0][m].id);
              }
            }  
          }
        }  
      }
   }
  printf("%d\n", best);
#if DBG
  printf("%1.6lf %1.6lf %1.6lf %1.6lf\n", bestx0, bestx1, besty0, besty1);
#endif
  return 0;
}

