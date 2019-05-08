#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))



enum{ MAX_DSIZE  = 8 };
enum{ MAX_POINTS = 2 * MAX_DSIZE };
enum{ MAX_DIST   = 50 };

const double INF = 1e100;
double best[1 << (MAX_POINTS - 1)][MAX_POINTS];
int districts[MAX_DIST][MAX_DSIZE][2], dSizes[MAX_DIST], nDist;
int n, max_match;
double lx   [MAX_DIST / 2], ly[MAX_DIST / 2];
int xy      [MAX_DIST / 2];
int yx      [MAX_DIST / 2];
bool S      [MAX_DIST / 2], T[MAX_DIST / 2];
double slack[MAX_DIST / 2];
int slackx  [MAX_DIST / 2];
int pprev   [MAX_DIST / 2];
double cost [MAX_DIST / 2][MAX_DIST / 2];

double heldKarp (double distance[MAX_POINTS][MAX_POINTS], int nPoints){
  for (int i = 0; i < (1 << (nPoints - 1)); i++)
    for (int j = 0; j < nPoints; j++)
      best[i][j] = INF;
  for (int visited = 1; visited < (1 << (nPoints - 1)); visited++)
    {
      for (int last = 0; last < nPoints - 1; last++)
        {
          if (!(visited & (1 << last)))
            continue;
          if (visited == (1 << last))
            {
              best[visited][last] = distance[nPoints - 1][last];
            }
          else
            {
              int prev_visited = visited ^ (1 << last);
              for (int prev = 0; prev < nPoints - 1; prev++)
                {
                  if (!(prev_visited & (1 << prev)))
                    continue;
                  best[visited][last] = min (best[visited][last], distance[last][prev] + best[prev_visited][prev] );
                }
            }
        }
    }
  double answer = INF;
  for (int last = 0; last < nPoints - 1; last++)
    answer = min (answer, distance[last][nPoints - 1] + best[(1 << (nPoints - 1)) - 1][last]);
  return answer;
}
void   generateDistances (double dists[MAX_POINTS][MAX_POINTS], int points[][2], int nPoints){
  for (int r = 0; r < nPoints; r++)
    for (int c = 0; c < nPoints; c++)
      dists[r][c] = sqrt ((points[r][0] - points[c][0]) *
                          (points[r][0] - points[c][0]) +
                          (points[r][1] - points[c][1]) *
                          (points[r][1] - points[c][1]));
}
void   init_labels (){
  memset (lx, 0, sizeof (lx));
  memset (ly, 0, sizeof (ly));
  for (int x = 0; x < n; x++)
    for (int y = 0; y < n; y++)
      lx[x] = max (lx[x], cost[x][y]);
}
void   update_labels (){
  int x, y;
  double delta = INF;
  for (y = 0; y < n; y++)
    if (!T[y])
      delta = min (delta, slack[y]);
  for (x = 0; x < n; x++)
    if (S[x])
      lx[x] -= delta;
  for (y = 0; y < n; y++)
    if (T[y])
      ly[y] += delta;
  for (y = 0; y < n; y++)
    if (!T[y])
      slack[y] -= delta;
}
void   add_to_tree (int x, int prevx){
  S[x] = true;
  pprev[x] = prevx;
  for (int y = 0; y < n; y++)
    if (lx[x] + ly[y] - cost[x][y] < slack[y])
      {
        slack[y] = lx[x] + ly[y] - cost[x][y];
        slackx[y] = x;
      }
}
void   augment (){
  if (max_match == n)
    return;
  int x, y, root;
  int q[MAX_DIST / 2], wr = 0, rd = 0;
  memset (S, false, sizeof (S));
  memset (T, false, sizeof (T));
  memset (pprev, -1, sizeof (pprev));
  for (x = 0; x < n; x++)
    if (xy[x] == -1)
      {
        q[wr++] = root = x;
        pprev[x] = -2;
        S[x] = true;
        break;
      }
  for (y = 0; y < n; y++)
    {
      slack[y] = lx[root] + ly[y] - cost[root][y];
      slackx[y] = root;
    }
  while (true)
    {
      while (rd < wr)
        {
          x = q[rd++];
          for (y = 0; y < n; y++)
            if (cost[x][y] == lx[x] + ly[y] && !T[y])
              {
                if (yx[y] == -1)
                  break;
                T[y] = true;
                q[wr++] = yx[y];
                add_to_tree (yx[y], x);
              }
          if (y < n)
            break;
        }
      if (y < n)
        break;
      update_labels ();
      wr = rd = 0;
      for (y = 0; y < n; y++)
        if (!T[y] && slack[y] == 0)
          {
            if (yx[y] == -1)
              {
                x = slackx[y];
                break;
              }
            else
              {
                T[y] = true;
                if (!S[yx[y]])
                  {
                    q[wr++] = yx[y];
                    add_to_tree (yx[y], slackx[y]);
                  }
              }
          }
      if (y < n)
        break;
    }
  if (y < n)
    {
      max_match++;
      for (int cx = x, cy = y, ty; cx != -2; cx = pprev[cx], cy = ty)
        {
          ty = xy[cx];
          yx[cy] = cx;
          xy[cx] = cy;
        }
      augment ();
    }
}
double hungarian (){
  double ret = 0;
  max_match = 0;
  memset (xy, -1, sizeof (xy));
  memset (yx, -1, sizeof (yx));
  init_labels ();
  augment ();
  for (int x = 0; x < n; x++)
    ret += cost[x][xy[x]];
  return ret;
}
double stableMarriage (double dists[MAX_DIST / 2][MAX_DIST / 2], int nDist){
  int rOrder [MAX_DIST / 2][MAX_DIST / 2],
      cOrder [MAX_DIST / 2][MAX_DIST / 2], rChoice[MAX_DIST / 2],
      cChoice[MAX_DIST / 2],
      q      [MAX_DIST / 2], qH = -1, qT = 0, qC = 0, i, j, k, tmp;
  double total = 0;
  for (i = 0; i < nDist; i++)
    for (j = 0; j < nDist; j++)
      rOrder[i][j] = cOrder[i][j] = j;
  for (i = 0; i < nDist; i++){
    for (j = 1; j < nDist; j++){
      tmp = rOrder[i][j];
      for (k = j - 1;  k >= 0 && dists[i][rOrder[i][k]] > dists[i][rOrder[i][tmp]];  k--)
        rOrder[i][k + 1] = rOrder[i][k];
      rOrder[i][k + 1] = tmp;
    }
  }
  for (i = 0; i < nDist; i++)
    {
      for (j = 1; j < nDist; j++)
        {
          tmp = cOrder[i][j];
          for (k = j - 1;  k >= 0 && dists[cOrder[i][k]][i] > dists[cOrder[i][tmp]][i];  k--)
            cOrder[i][k + 1] = cOrder[i][k];
          cOrder[i][k + 1] = tmp;
        }
    }
  for (i = 0; i < nDist; i++)
    rChoice[i] = cChoice[i] = -1;
  for (i = 0; i < nDist; i++)
    q[i] = i;
  qC = nDist;
  while (qC > 0)
    {
      qH = ++qH % (MAX_DIST / 2);
      qC--;
      tmp = q[qH];
      rChoice[tmp]++;
      if (cChoice[rOrder[tmp][rChoice[tmp]]] == -1)
          cChoice[rOrder[tmp][rChoice[tmp]]] = tmp;
      else
        {
          for (i = 0; cOrder[rOrder[tmp][rChoice[tmp]]][i] != tmp; i++);
          for (j = 0; cOrder[rOrder[tmp][rChoice[tmp]]][j] != cChoice[rOrder[tmp][rChoice[tmp]]]; j++);
          if (i < j)
            {
              q[qT] = cChoice[rOrder[tmp][rChoice[tmp]]];
              cChoice[rOrder[tmp][rChoice[tmp]]] = tmp;
            }
          else
            q[qT] = tmp;
          qT = ++qT % (MAX_DIST / 2);
          qC++;
        }
    }
  for (i = 0; i < nDist; i++)
    total += dists[i][rOrder[i][rChoice[i]]];
  return total;
}
int    main(){
  double dists      [MAX_POINTS][MAX_POINTS] = {.0};
  double mergedDists[MAX_DIST/2][MAX_DIST/2] = {.0};
  double total     = .0;
  double totalAfter= .0;
  int    mergedPoints[MAX_POINTS][2]={0};
  scanf("%d", &nDist);
  for (int i = 0; i < nDist; i++){
    scanf("%d", &dSizes[i]);
    for(int j = 0; j < dSizes[i]; j++)
      scanf("%d %d", &districts[i][j][0], &districts[i][j][1]);
    generateDistances (dists, districts[i], dSizes[i]);
    total += heldKarp (dists, dSizes[i]);
  }
  for (int i = 0; i < nDist / 2; i++){
    for (int j = 0; j < dSizes[i]; j++){
      mergedPoints[j][0] = districts[i][j][0];
      mergedPoints[j][1] = districts[i][j][1];
    }
    for (int j = nDist / 2; j < nDist; j++){
      for (int k = 0; k < dSizes[j]; k++){
        mergedPoints[k + dSizes[i]][0] = districts[j][k][0];
        mergedPoints[k + dSizes[i]][1] = districts[j][k][1];
      }
      generateDistances (dists, mergedPoints, dSizes[i] + dSizes[j]);
      cost[i][j - nDist / 2] = heldKarp (dists, dSizes[i] + dSizes[j]);
    }
  }
  double mm = 0;
  for (int i = 0; i < nDist / 2; i++)
    for (int j = 0; j < nDist / 2; j++)
      mm = max (mm, cost[i][j]);
  for (int i = 0; i < nDist / 2; i++)
    for (int j = 0; j < nDist / 2; j++)
      cost[i][j] = mm - cost[i][j];
  n = nDist / 2;
  totalAfter = (mm * nDist) / 2 - hungarian ();
  printf("%.6lf %.6lf\n", total, totalAfter);
  return 0;
}


