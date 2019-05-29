#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>
int min(int x, int y){ return x <= y ? x : y;}
int max(int x, int y){ return x <= y ? y : x;}
int int_get(void){
  int result;
  scanf("%d", &result);
  return result;
}
void ints_println_basic(const int *a, int n){
  if (n > 0){
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)
      printf(" %d", a[i]);
  }
  printf("\n");
}
int ints_get(int *a){
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}
void ints_print(int *a, int n, char *separator){
  if (n > 0){
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)
      printf("%s%d", separator, a[i]);
  }
}
void ints_println(int *a, int n, char *separator){
  ints_print(a, n, separator);
  printf("\n");
}
int *ints_new (int n){
  return (int *) calloc(n, sizeof(int));
}
void ints_clear(int *a, int n){
  memset(a, 0, n * sizeof(int));
}
int ints_naturals(int *a, int n){
  for (int i = 0; i < n; i++)
    a[i] = i;
  return n;
}
void ints_exchange(int *a, int x, int y){
  int m = a[x];
  a[x] = a[y];
  a[y] = m;
}
int ints_insert(int *a, int n, int x){
  a[n] = x;
  int i = n;
  while (i > 0 && a[i-1] > a[i]){
    ints_exchange(a, i-1, i);
    i--;
  }
  return n+1;
}
void ints_isort_to(const int *a, int n, int *b){
  for (int i = 0; i < n; i++)
    ints_insert(b, i, a[i]);
}
void ints_isort(int *a, int n){
  ints_isort_to(a, n, a);
}
int ints_count_while(const int *a, int n, int x){
  int result = 0;
  while (result < n && a[result] == x)
    result++;
  return result;
}
int ints_unique(const int *a, int n, int *b){
  int result = 0;
  int i = 0;
  while (i < n){
    int z = ints_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}
int ints_copy(const int *a, int n, int *b){
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(int));
  return n;
}
void ints_quicksort(int *a, int n){
  int i = 0;
  int j = n-1;
  int p = a[n/2];
  assert(n>0);
  do{
    while (a[i] < p)
      i++;
    while (p < a[j])
      j--;
    if (i <= j)
      ints_exchange(a, i++, j--);
  }
  while (i <= j);
  if (j > 0)
    ints_quicksort(a, j+1);
  if (i < n-1)
    ints_quicksort(a+i, n-i);
}
typedef struct {
  int x1, y1, x2, y2;
} Rect;
int rect_valid(const Rect *r){
  return r->x1 <= r->x2 && r->y1 <= r->y2;
}
int rect_true(const Rect *r){
  return r->x1 < r->x2 && r->y1 < r->y2;
}
int rect_degenerate(const Rect *r){
  return rect_valid(r) && (r->x1 == r->x2 || r->y1 == r->y2);
}
int rect_area(const Rect *r){
  return (r->x2 - r->x1) * (r->y2 - r->y1);
}
int rect_intersection(const Rect *r, const Rect *s, Rect *z){
  z->x1 = max(r->x1, s->x1);
  z->y1 = max(r->y1, s->y1);
  z->x2 = min(r->x2, s->x2);
  z->y2 = min(r->y2, s->y2);
  return rect_valid(z);
}
int rect_equal(const Rect *r, const Rect *s){
  return r->x1 == s->x1 && r->y1 == s->y1 && r->x2 == s->x2 && r->y2 == s->y2;
}
int rect_cmp_by_x1(const Rect *r, const Rect *s){
  int result = r->x1 - s->x1;
  if (result == 0)
    result = r->y1 - s->y1;
  return result;
}
int rect_cmp_by_y1(const Rect *r, const Rect *s){
  int result = r->y1 - s->y1;
  if (result == 0)
    result = r->x1 - s->x1;
  return result;
}
int rect_cmp_by_x2(const Rect *r, const Rect *s){
  int result = r->x2 - s->x2;
  if (result == 0)
    result = r->y2 - s->y2;
  return result;
}
int rect_cmp_by_y2(const Rect *r, const Rect *s){
  int result = r->y2 - s->y2;
  if (result == 0)
    result = r->x2 - s->x2;
  return result;
}
int rect_adjacent(const Rect *r, const Rect *s){
  Rect z;
  rect_intersection(r, s, &z);
  return rect_degenerate(&z);
}
int rect_intersect_truly(const Rect *r, const Rect *s){
  Rect z;
  rect_intersection(r, s, &z);
  return rect_true(&z);
}
void rect_make(Rect *r, int x1, int y1, int x2, int y2){
  r->x1 = x1;
  r->y1 = y1;
  r->x2 = x2;
  r->y2 = y2;
}
void rect_make_from_dimensions(Rect *r, int x, int y, int w, int h){
  rect_make(r, x, y, x+w, y+h);
}
int rects_copy(const Rect *r, int n, Rect *s){
  {
    if (n < 0)
      n = 0;
    memmove(s, r, n * sizeof(Rect));
    return n;
  }
}
int rects_get_some(Rect *r, int n){
  for (int i = 0; i < n; i++)
  {
    int x, y, w, h;
    scanf("%d%d%d%d", &x, &y, &w, &h);
    rect_make_from_dimensions(r+i, x, y, w, h);
  }
  return n;
}
void rect_show(const Rect *r){
  printf("[%d %d %d %d]\n", r->x1, r->y1, r->x2, r->y2);
}
void rect_write(const Rect *r){
  printf("%d %d %d %d\n", r->x1, r->y1, r->x2, r->y2);
}
void rect_write_as_input(const Rect *r){
  printf("%d %d %d %d\n", r->x1, r->y1, r->x2 - r->x1, r->y2 - r->y1);
}
void rect_show_pair(const Rect *r, const Rect *s){
  printf("[%d %d %d %d]  ", r->x1, r->y1, r->x2, r->y2);
  printf("[%d %d %d %d]\n", s->x1, s->y1, s->x2, s->y2);
}
void rects_show(const Rect *r, int n){
  for (int i = 0; i < n; i++)
    rect_show(r+i);
}
void rects_write(const Rect *r, int n){
  for (int i = 0; i < n; i++)
    rect_write(r+i);
}
void rects_write_as_input(const Rect *r, int n){
  for (int i = 0; i < n; i++)
    rect_write_as_input(r+i);
}
void rects_show_indexed(const Rect *r, const int *a, int n){
  for (int i = 0; i < n; i++)
  {
    const Rect *p = r + a[i];
    printf("[%d %d %d %d]\n", p->x1, p->y1, p->x2, p->y2);
  }
}
int rects_find_intersection(const Rect *r, int n, Rect *s){
  for (int i = 0; i < n; i++)
    if (rect_intersect_truly(r+i, s))
      return i;
  return -1;
}
int rect_cmp_by_x1_v(const void *r, const void *s){
  Rect *x = (Rect *) r;
  Rect *y = (Rect *) s;
  return rect_cmp_by_x1(x, y);
}
int rect_cmp_by_y1_v(const void *r, const void *s){
  Rect *x = (Rect *) r;
  Rect *y = (Rect *) s;
  return rect_cmp_by_y1(x, y);
}
int rect_cmp_by_x2_v(const void *r, const void *s){
  Rect *x = (Rect *) r;
  Rect *y = (Rect *) s;
  return rect_cmp_by_x2(x, y);
}
int rect_cmp_by_y2_v(const void *r, const void *s){
  Rect *x = (Rect *) r;
  Rect *y = (Rect *) s;
  return rect_cmp_by_y2(x, y);
}
void rects_sort_by_x1(Rect *r, int n){
  qsort(r, n, sizeof(Rect), rect_cmp_by_x1_v);
}
void rects_sort_by_y1(Rect *r, int n){
  qsort(r, n, sizeof(Rect), rect_cmp_by_y1_v);
}
void rects_sort_by_x2(Rect *r, int n){
  qsort(r, n, sizeof(Rect), rect_cmp_by_x2_v);
}
void rects_sort_by_y2(Rect *r, int n){
  qsort(r, n, sizeof(Rect), rect_cmp_by_y2_v);
}
typedef int(*Rect_Cmp)(const Rect*, const Rect *);
void rects_quicksort_indirect(const Rect *r, Rect_Cmp cmp, int *a, int n){
  int i = 0;
  int j = n-1;
  int p = a[n/2];
  assert(n>0);
  do
  {
    while (cmp(r+a[i], r+p) < 0)
      i++;
    while (cmp(r+p, r+a[j]) < 0)
      j--;
    if (i <= j)
      ints_exchange(a, i++, j--);
  }
  while (i <= j);
  if (j > 0)
    rects_quicksort_indirect(r, cmp, a, j+1);
  if (i < n-1)
    rects_quicksort_indirect(r, cmp, a+i, n-i);
}
int rects_index(const Rect *r, Rect_Cmp cmp, int *a, int n){
  ints_naturals(a, n);
  rects_quicksort_indirect(r, cmp, a, n);
  return n;
}
void rects_paint(const Rect *r, int n, int w, int h){
  if (h > 1000)
    return; 
  int b[h][w];
  memset(b, -1, h * w * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    const Rect *p = r + i;
    for (int y = p->y1; y < p->y2; y++)
      for (int x = p->x1; x < p->x2; x++)
        b[y][x] = i;
  }
  for (int i = h-1; i >= 0; i--)
  {
    for (int j = 0; j < w; j++)
    {
      int z = b[i][j];
      printf("%c", z == -1 ? ' ' : 'a'+ (z % 26));
    }
    printf("\n");
  }
}
void rects_paint_by_area(const Rect *r, int n, int w, int h){
  if (h > 1000)
    return; 
  int b[h][w];
  memset(b, -1, h * w * sizeof(int));
  for (int i = 0; i < n; i++)
  {
    const Rect *p = r + i;
    int a = rect_area(p) - 1;
    for (int y = p->y1; y < p->y2; y++)
      for (int x = p->x1; x < p->x2; x++)
        b[y][x] = a;
  }
  for (int i = h-1; i >= 0; i--)
  {
    for (int j = 0; j < w; j++)
    {
      int z = b[i][j];
      printf("%c", z == -1 ? ' ' : 'a'+ (z % 26));
    }
    printf("\n");
  }
}

typedef struct {
  int length;
  int count;
  int *id;
  int *size;
} Quick_Union; 
void qu_create(Quick_Union *q, int n){
  q->count = q->length = n;
  q->id = ints_new(n);
  for (int i = 0; i < n; i++)
    q->id[i] = i;
  q->size = ints_new(n);
  for (int i = 0; i < n; i++)
    q->size[i] = 1;
}
int qu_find(Quick_Union *q, int x){
  while (x != q->id[x])
    x = q->id[x];
  return x;
}
void qu_union(Quick_Union *q, int x, int y){
  int ix = qu_find(q, x);
  int iy = qu_find(q, y);
  if (ix != iy)
  {
    if (q->size[ix] < q->size[iy])
    {
      q->id[ix] = iy;
      q->size[iy] += q->size[ix];
    }
    else
    {
      q->id[iy] = ix;
      q->size[ix] += q->size[iy];
    }
    q->count--;
  }
}
void qu_flatten(Quick_Union *q){
  for (int i = 0; i < q->length; i++)
    q->id[i] = qu_find(q, q->id[i]);
}
int qu_size(Quick_Union *q, int x){
  return q->size[qu_find(q, x)];
}
void qu_show(Quick_Union *q){
  ints_println_basic(q->id, q->length);
  int a[q->length];
  int n = ints_copy(q->id, q->length, a);
  ints_isort(a, n);
  n = ints_unique(a, n, a);
  printf("%d\n", q->count);
  for (int i = 0; i < n; i++)
    printf ("%d %d\n", a[i], q->size[a[i]]);
}
void find_groups(Rect* a, int n, Quick_Union *q){
  for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++)
      if (rect_adjacent(a+i, a+j))
        qu_union(q, i, j);
  qu_flatten(q);
}
int group_areas(Rect *a, int n, Quick_Union *q, int *b){
  ints_clear(b, n);
  for (int i = 0; i < n; i++)
  {
    int z = q->id[i];
    b[z] += rect_area(a+i);
  }
  return n;
}
int group_areas_complete(int *a, int n, Quick_Union *q, int *b){
  for (int i = 0; i < n; i++)
    b[i] = a[q->id[i]];
  return n;
}
void find_groups_smarter_horizontally(const Rect* a, int n, Quick_Union *q){
  int left[n];
  rects_index(a, rect_cmp_by_x2, left, n);
  int right[n];
  rects_index(a, rect_cmp_by_x1, right, n);
  int i = 0;
  int j = 0;
  while (i < n && j < n)
  {
    int ii = left[i];
    int jj = right[j];
    if (a[ii].x2 < a[jj].x1)
      i++;
    else if (a[ii].x2 > a[jj].x1)
      j++;
    else
    {
      assert(a[ii].x2 == a[jj].x1);
      if (rect_adjacent(a+ii, a+jj))
      {
        qu_union(q, ii, jj);
      }
      if (a[ii].y2 <= a[jj].y2)
        i++;
      else
        j++;
    }
  }
}
void find_groups_smarter_vertically(const Rect* a, int n, Quick_Union *q){
  int bottom[n];
  rects_index(a, rect_cmp_by_y2, bottom, n);
  int top[n];
  rects_index(a, rect_cmp_by_y1, top, n);
  int i = 0;
  int j = 0;
  while (i < n && j < n)
  {
    int ii = bottom[i];
    int jj = top[j];
    if (a[ii].y2 < a[jj].y1)
      i++;
    else if (a[ii].y2 > a[jj].y1)
      j++;
    else
    {
      assert(a[ii].y2 == a[jj].y1);
      if (rect_adjacent(a+ii, a+jj))
      {
        qu_union(q, ii, jj);
      }
      if (a[ii].x2 <= a[jj].x2)
        i++;
      else
        j++;
    }
  }
}
void find_groups_smarter(const Rect* a, int n, Quick_Union *q){
  find_groups_smarter_horizontally(a, n, q);
  find_groups_smarter_vertically(a, n, q);
  qu_flatten(q);
}
typedef struct {
  int id;
  int area;
  Rect *r;
} Group;
void group_make(Group *x, int id, int area, Rect *r){
  x -> id = id;
  x -> area = area;
  x -> r = r;
}
void group_show(Group *x){
  printf("<%d %d %d %d>\n", x->id, x->area, x->r->x1, x->r->y1);
}
void groups_show(Group *x, int n){
  for (int i = 0; i < n; i++)
    group_show(x + i);
}
void group_print(Group *x){
  printf("%d %d %d\n", x->r->x1, x->r->y1, x->area);
}
void group_print_area(Group *x){
  printf("%d\n", x->area);
}
void groups_print(Group *x, int n){
  for (int i = 0; i < n; i++)
    group_print(x + i);
}
void groups_print_area(Group *x, int n){
  for (int i = 0; i < n; i++)
    group_print_area(x + i);
}
int groups_from_areas(Rect *a, int n, Quick_Union *q, int *areas, Group *b){
  for (int i = 0; i < n; i++)
    group_make(b+i, q->id[i], areas[i], a+i);
  return n;
}
int group_cmp_by_group(const Group *x, const Group *y){
  int result = x->id - y->id;
  if (result == 0)
    result = rect_cmp_by_y1(x->r, y->r);
  return result;
}
int group_cmp_by_group_v(const void *x, const void *y){
  Group *px = (Group *) x;
  Group *py = (Group *) y;
  return group_cmp_by_group(px, py);
}
int group_cmp_by_area(const Group *x, const Group *y){
  int result = -(x->area - y->area); 
  if (result == 0)
    result = rect_cmp_by_y1(x->r, y->r);
  return result;
}
int group_cmp_by_area_v(const void *x, const void *y){
  Group *px = (Group *) x;
  Group *py = (Group *) y;
  return group_cmp_by_area(px, py);
}
int groups_unique(Group *a, int n){
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int k = a[i].id;
    a[result++] = a[i];
    do
      i++;
    while (i < n && k == a[i].id);
  }
  return result;
}
int millisecs(clock_t x){
  return (int) round(x * 1000.0 / CLOCKS_PER_SEC);
}
int rand_to(int n){
  unsigned int m = (unsigned int) RAND_MAX + 1;
  unsigned int u_n = (unsigned int) n;
  unsigned int w = m / (u_n+1);
  unsigned int limit = (u_n+1) * w;
  int r;
  do
    r = rand();
  while ((unsigned int)r >= limit);
  return r / w;
}
enum{ MAX_STONES = 50000};
int main(){
  Rect r[MAX_STONES];
  int n = rects_get_some(r, int_get());
  Quick_Union q;
  qu_create(&q, n);
  find_groups_smarter(r, n, &q);
  int areas[n];
  int m = group_areas(r, n, &q, areas);
  int areas_all[n];
  group_areas_complete(areas, m, &q, areas_all);
  Group g[n];
  groups_from_areas(r, n, &q, areas_all, g);
  qsort(g, n, sizeof(Group), group_cmp_by_group_v);
  int u = groups_unique(g, n);
  qsort(g, u, sizeof(Group), group_cmp_by_area_v);
  groups_print_area(g, 1);
  return 0;
}
