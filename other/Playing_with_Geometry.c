#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum { MAXVERTS  =  500 };
enum { MAXCOORDS = 3000 };
enum { FREELINE  =   -1 };

typedef struct{
  int x, y;
}Point;

int Hgrid[MAXCOORDS + 1], 
    Vgrid[MAXCOORDS + 1];

int read_polygon(Point*pol, int*box){
  int n, i, maxX, maxY, horizontal;
  scanf ("%d", &n);
  scanf ("%d %d", &((pol[0]).x), &((pol[0]).y));
  box[0] = 0;
  if (((pol[0]).x) == 0)
    box[3] = n - 1;
  maxX = 0;
  maxY = 0;
  horizontal = 1;
  for (i = 1; i < n; i++){
    scanf ("%d %d", &((pol[i]).x), &((pol[i]).y));
    if (horizontal == 1){
      if (((pol[i]).y) > maxY){
        maxY = ((pol[i]).y);
        box[2] = i - 1;
      }
    }
    else{
      if (((pol[i]).x) == 0)
        box[3] = i - 1;
      else if (((pol[i]).x) > maxX){
        maxX = ((pol[i]).x);
        box[1] = i - 1;
      }
    }
    horizontal = -horizontal;
  }
  return n;
}
void polygon2permutomino (Point * pol, int n, int*box){
  int i, j;
  if (((pol[box[1]]).x) != (n - 2) / 2 || ((pol[box[2]]).y) != (n - 2) / 2){
    for (i = 0; i < MAXCOORDS + 1; i++)
      Hgrid[i] = Vgrid[i] = FREELINE;
    for (i = 0; i < n; i = i + 2){
      Hgrid[((pol[i]).y)] = i;
      Vgrid[((pol[i + 1]).x)] = i + 1;
    }
    if (((pol[box[2]]).y) != (n - 2) / 2){
      for (i = j = 0; i < n / 2; j++){
        if (Hgrid[j] != FREELINE){
          ((pol[Hgrid[j]]).y) = i;
          ((pol[(Hgrid[j] + 1) % n]).y) = i;
          i++;
        }
      }
    }
    if (((pol[box[1]]).x) != (n - 2) / 2){
      for (i = j = 0; i < n / 2; j++){
        if (Vgrid[j] != FREELINE){
          ((pol[Vgrid[j]]).x) = i;
          ((pol[(Vgrid[j] + 1) % n]).x) = i;
          i++;
        }
      }
    }
  }
}
Point rotate_point (int rot, int c, Point p){
  Point pf;
  switch (rot){
    case 1:
      ((pf).x) = c - ((p).y);
      ((pf).y) = ((p).x);
      break;
    case 2:
      ((pf).x) = -((p).x) + c;
      ((pf).y) = -((p).y) + c;
      break;
    default:
      ((pf).x) = ((p).y);
      ((pf).y) = -((p).x) + c;
  }
  return pf;
}
int is_equal (int n, Point*p1, Point*p2, int*box1, int*box2){
  int i, j, k;
  for (i = 0; i < 4; i++){
    if (((p1[box1[i]]).x) != ((p2[box2[i]]).x) || ((p1[box1[i]]).y) != ((p2[box2[i]]).y))
      return 0;
    j = (1 + box1[i]) % n;
    k = (1 + box2[i]) % n;
    if (((p1[j]).x) != ((p2[k]).x)
         || ((p1[j]).y) != ((p2[k]).y))
      return 0;
  }
  for (i = 0; i < n; i++)
    if (((p1[i]).x) != ((p2[i]).x) || ((p1[i]).y) != ((p2[i]).y))
      return 0;
  return 1;
}
int is_rotation (int rot, int n, Point*p1, Point*p2, int*box1, int*box2){
  int i, j, c = n / 2 - 1;
  Point v;
  for (i = 0; i < 4; i++){
    v = rotate_point (rot, c, p1[box1[i]]);
    j = box2[(i + rot) % 4];
    if (((p2[j]).x) != ((v).x) || ((p2[j]).y) != ((v).y))
      return 0;
    v = rotate_point (rot, c, p1[(1 + box1[i]) % n]);
    j = (j + 1) % n;
    if (((p2[j]).x) != ((v).x) || ((p2[j]).y) != ((v).y))
      return 0;
  }
  for (i = 0; i < n; i++){
    v = rotate_point (rot, c, p1[i]);
    j = (i + box2[rot]) % n;
    if (((p2[j]).x) != ((v).x) || ((p2[j]).y) != ((v).y))
      return 0;
  }
  return 1;
}
int main(){
  int n1, n2, okrot = 0, rot;
  Point p1[MAXVERTS], 
        p2[MAXVERTS];
  int box1[4], 
      box2[4];
  n1 = read_polygon (p1, box1);
  n2 = read_polygon (p2, box2);
  if (n1 == n2){
    polygon2permutomino (p1, n1, box1);
    polygon2permutomino (p2, n2, box2);
    okrot = is_equal (n1, p1, p2, box1, box2);
    for (rot = 1; rot < 4 && !okrot; rot++)
      okrot = is_rotation (rot, n1, p1, p2, box1, box2);
  }
  if (okrot)
    puts("yes");
  else
    puts("no");
  return 0;
}


