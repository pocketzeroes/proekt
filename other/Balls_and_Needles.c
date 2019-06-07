#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<limits.h>
int max(int x, int y){  return x <= y ? y : x;}
int min(int x, int y){  return x <= y ? x : y;}
int int_get(void){
  int result;
  scanf("%d", &result);
  return result;
}
int ints_get(int *a){
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}
int ints_get_while_not(int *a, int z){
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF && x != z)
    a[result++] = x;
  return result;
}
int ints_get_two(int *a, int *b){
  int result = 0;
  int x, y;
  while (scanf("%d%d", &x, &y) != EOF){
    a[result] = x;
    b[result] = y;
    result++;
  }
  return result;
}
int ints_init(int x, int n, int *a){
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = x;
  return result;
}
int ints_id(int n, int *a){
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = i;
  return result;
}
int ints_count(const int *a, int n, int x){
  int result = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      result++;
  return result;
}
int ints_sum(const int *a, int n){
  int result = 0;
  for (int i = 0; i < n; i++)
    result += a[i];
  return result;
}
int ints_find(const int *a, int n, int x){
  for (int i = 0; i < n; i++)
    if (a[i] == x)
      return i;
  return -1;
}
int ints_max(const int *a, int n){
  int result = INT_MIN;
  for (int i = 0; i < n; i++)
    if (result < a[i])
      result = a[i];
  return result;
}
int ints_min(const int *a, int n){
  int result = INT_MAX;
  for (int i = 0; i < n; i++)
    if (result > a[i])
      result = a[i];
  return result;
}
int ints_argmax(const int *a, int n){
  int result = -1;
  int max = INT_MIN;
  for (int i = 0; i < n; i++){
    if (max < a[i]){
      max = a[i];
      result = i;
    }
  }
  return result;
}
int ints_argsmax(const int *a, int n, int *b){
  int result = 0;
  int max = INT_MIN;
  for (int i = 0; i < n; i++){
    if (max < a[i]){
      max = a[i];
      result = 0;
    }
    if (max <= a[i])
      b[result++] = i;
  }
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
void ints_println_basic_two(const int *a, const int *b, int n){
  assert(n > 0);
  for (int i = 0; i < n; i++)
    printf("%d %d\n", a[i], b[i]);
}
void ints_print(int *a, int n, char *separator){
  if (n > 0)
  {
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf("%s%d", separator, a[i]);
  }
}
void ints_println(int *a, int n, char *separator)
{
  ints_print(a, n, separator);
  printf("\n");
}
int *ints_new (int n)
{
  return (int *) malloc (n * sizeof(int));
}

int ints_is_sorted(int *a, int n)
{
  for (int i = 1; i < n; i++)
    if (a[i-1] > a[i])
      return 0;
  return 1;
}
int ints_rank(const int *a, int n, int x)
{
  int result = 0;
  while (n > 0)
  {
    int m = n / 2;
    if (x <= a[m])
      n = m;
    else
    {
      result += m+1;
      a += m+1;
      n -= m+1;
    }
  }
  return result;
}
int ints_bfind(const int *a, int n, int x)
{
  int r = ints_rank(a, n, x);
  return r < n && a[r] == x ? r : -1;
}
int ints_bfind_classic(const int *a, int n, int x)
{
  int i = 0;
  int j = n-1;
  while (i <= j)
  {
    int m = i + (j-i) / 2;
    if (x < a[m])
      j = m-1;
    else if (x > a[m])
      i = m+1;
    else
      return m;
  }
  return -1;
}

void ints_exchange(int *a, int x, int y)
{
  int m = a[x];
  a[x] = a[y];
  a[y] = m;
}
void ints_sort_last(int *a, int n)
{
  int i = n-1;
  while (i > 0 && a[i-1] > a[i])
  {
    ints_exchange(a, i-1, i);
    i--;
  }
}
int ints_insert(int *a, int n, int x)
{
  int result = n;
  a[result++] = x;
  ints_sort_last(a, result);
  return result;
}
void ints_isort(int *a, int n)
{
  for (int i = 2; i <= n; i++)
    ints_sort_last(a, i);
}
int ints_copy(const int *a, int n, int *b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(int)); 
  return n;
}
int ints_merge(const int *a, int n, const int *b, int m, int *c)
{
  int result = 0;
  int i = 0;
  int j = 0;
  while (i < n && j < m)
    if (a[i] <= b[j])
      c[result++] = a[i++];
    else
      c[result++] = b[j++];
  result += ints_copy(a + i, n - i, c+result);
  result += ints_copy(b + j, m - j, c+result);
  return result;
}
void ints_msort_i(int *a, int n, int *b)
{
  if (n > 1)
  {
    int m = n / 2;
    ints_msort_i(a, m, b);
    ints_msort_i(a+m, n-m, b);
    ints_merge(a, m, a+m, n-m, b);
    ints_copy(b, n, a);
  }
}
void ints_msort(int *a, int n)
{
  int *b = ints_new(n);
  ints_msort_i(a, n, b);
}
int ints_hash(int *a, int n)
{
  unsigned int r = 0;
  for (int i = 0; i < n; i++)
  {
    r += a[i];
    r += r << 10;
    r ^= r >> 6;
  }
  r += r << 3;
  r ^= r >> 11;
  r += r << 15;
  return (int) r & ~(1 << 31);
}
int ints_find_duplicate(int *a, int n)
{
  for (int i = 1; i < n; i++)
    if (a[i-1] == a[i])
      return i-1;
  return -1;
}

typedef struct {
  int x;
  int y;
  int z;
} Point;
typedef struct {
  Point p1;
  Point p2;
} Needle;
Point point(int x, int y, int z)
{
  Point result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}
Point point_get()
{
  int x, y, z;
  scanf("%d%d%d", &x, &y, &z);
  return point(x, y, z);
}
int point_hash(Point p)
{
  int a[3] = {p.x, p.y, p.z};  
  return ints_hash(a, 3);
}
Point *point_dup(Point p)
{
  Point *result = (Point *)malloc(sizeof(Point));
  result->x = p.x;
  result->y = p.y;
  result->z = p.z;
  return result;
}
int point_cmp(Point p, Point q)
{
  int result = p.x - q.x;
  if (result == 0)
  {
    result = p.y - q.y;
    if (result == 0)
      result = p.z - q.z;
  }
  return result;
}
int point_cmp_v(const void *p, const void *q)
{
  const Point *xp = (const Point *)p;
  const Point *xq = (const Point *)q;
  return point_cmp(*xp, *xq);
}
Point point_project(Point p)
{
  return point(p.x, p.y, 0);
}
void point_printf(const char *fmt, Point p)
{
  printf(fmt, p.x, p.y, p.z);
}
void points_printf(const char *fmt, const Point *a, int n)
{
  for (int i = 0; i < n; i++)
    point_printf(fmt, a[i]);
}
void points_ref_printf(const char *fmt, Point **a, int n)
{
  for (int i = 0; i < n; i++)
    point_printf(fmt, *a[i]);
}
void points_qsort(Point *a, int n)
{
  qsort(a, n, sizeof(Point), point_cmp_v);
}
int points_count_while(const Point *a, int n, Point x)
{
  int result = 0;
  while (result < n && point_cmp(a[result], x) == 0)
    result++;
  return result;
}
int points_unique(const Point *a, int n, Point *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = points_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}
int points_from_needles(const Needle *a, int n, Point *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
  {
    b[result++] = a[i].p1;
    b[result++] = a[i].p2;
  }
  points_qsort(b, result);
  result = points_unique(b, result, b);
  return result;
}
Needle needle(Point p1, Point p2)
{
  Needle result;
  if (point_cmp(p1, p2) <= 0)
  {
    result.p1 = p1;
    result.p2 = p2;
  }
  else
  {
    result.p1 = p2;
    result.p2 = p1;
  }
  return result;
}
Needle needle_project(Needle ndl)
{
  return needle(point_project(ndl.p1), point_project(ndl.p2));
}
void needle_print(Needle ndl)
{
  point_printf("[%d %d %d]", ndl.p1);
  point_printf("[%d %d %d]\n", ndl.p2);
}
void needles_print(const Needle* a, int n)
{
  for (int i = 0; i < n; i++)
    needle_print(a[i]);
}
int needles_project(const Needle* a, int n, Needle *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    b[result++] = needle_project(a[i]);
  return result;
}
int needle_vertical(Needle a)
{
  return a.p1.x = a.p2.x && a.p1.y == a.p2.y;
}
int needles_get_some(int n, Needle *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
  {
    Point p1 = point_get();
    Point p2 = point_get();
    a[result++] = needle(p1, p2);
  }
  return result;
}
int needle_cmp(Needle a, Needle b)
{
  int result = point_cmp(a.p1, b.p1);
  if (result == 0)
    result = point_cmp(a.p2, b.p2);
  return result;
}
int needle_cmp_v(const void *a, const void *b)
{
  const Needle *ap = (const Needle *)a;
  const Needle *bp = (const Needle *)b;
  return needle_cmp(*ap, *bp);
}
void needles_qsort(Needle *a, int n)
{
  qsort(a, n, sizeof(Needle), needle_cmp_v);
}
int needles_count_while(const Needle *a, int n, Needle x)
{
  int result = 0;
  while (result < n && needle_cmp(a[result], x) == 0)
    result++;
  return result;
}
int needles_unique(const Needle *a, int n, Needle *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = needles_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}
int needles_remove_vertical(const Needle *a, int n, Needle *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    if (!needle_vertical(a[i]))
      b[result++] = a[i];
  return result;
}

typedef struct {
  Point **keys;
  Point **values;
  int capacity;
  int count;
  Point **all_keys;
  int n_keys;
} Hashtable;
void hashtable_make(Hashtable *ht, int capacity)
{
  ht->keys = (Point**) calloc (capacity, sizeof(Point*));  // clears memory.
  ht->values = (Point**) calloc (capacity, sizeof(Point*));
  ht->capacity = capacity;
  ht->count = 0;
  ht->all_keys = (Point**) calloc (capacity, sizeof(Point*));
  ht->n_keys = 0;
}
int hash_find(Hashtable *ht, Point key)
{
  int result = point_hash(key) % ht->capacity;
  while (ht->keys[result] && point_cmp(*ht->keys[result], key))
    result = (result+1) % ht->capacity;
  return result;
}
Point *hash_get(Hashtable *ht, Point key)
{
  int z = hash_find(ht, key);
  return ht->keys[z] ? ht->values [z] : NULL;
}
int hash_put(Hashtable *ht, Point key, Point value)
{
  assert(ht->count < ht->capacity);
  int result = 0;
  int k = hash_find(ht, key);
  result = !ht->keys[k];
  if (result) 
  {
    ht->keys[k] = point_dup(key);
    ht->all_keys[ht->n_keys++] = ht->keys[k];
    ht->values[k] = point_dup(value);
    ht->count++;
  }
  else 
  {
    ht->values[k] = point_dup(value);
  }
  return result;
}
void hash_show(Hashtable *ht)
{
  for (int i = 0; i < ht->capacity; i++)
    if (ht->keys[i] != NULL)
    {
      printf("%d ", i);
      point_printf("[%d %d %d]", *ht->keys[i]);
      point_printf("[%d %d %d]", *ht->values[i]);
      printf("\n");
    }
  points_ref_printf("---[%d %d %d]\n", ht->all_keys, ht->n_keys);
}

int qf_init(Hashtable *ht, const Point *a, int n)
{
  for (int i = 0; i < n; i++)
    hash_put(ht, a[i], a[i]);
  return n;
}
int qf_union(Hashtable *ht, int count, Point x, Point y)
{
  int result = count;
  Point *ix = hash_get(ht, x);  
  Point *iy = hash_get(ht, y);
  if (point_cmp(*ix, *iy))
  {
    for (int i = 0; i < ht->n_keys; i++)
    {
      Point *b = hash_get(ht, *ht->all_keys[i]);
      if (point_cmp(*b, *ix) == 0)
        hash_put(ht, *ht->all_keys[i], *iy);
    }
    result--;
  }
  return result;
}
Point *qf_find(Hashtable *ht, Point x)
{
  return hash_get(ht, x);
}

typedef struct {
  Point **keys;
  Point **values;
  int *sizes;
  int capacity;
  int count;
  Point **all_keys;
  int n_keys;
} Hashtable2;
void hashtable2_make(Hashtable2 *ht, int capacity)
{
  ht->keys = (Point**) calloc (capacity, sizeof(Point*));  // clears memory.
  ht->values = (Point**) calloc (capacity, sizeof(Point*));
  ht->sizes = ints_new(capacity);
  ht->capacity = capacity;
  ht->count = 0;
  ht->all_keys = (Point**) calloc (capacity, sizeof(Point*));
  ht->n_keys = 0;
}
int hash2_find(Hashtable2 *ht, Point key)
{
  int result = point_hash(key) % ht->capacity;
  while (ht->keys[result] && point_cmp(*ht->keys[result], key))
    result = (result+1) % ht->capacity;
  return result;
}
Point *hash2_get(Hashtable2 *ht, Point key)
{
  Point *result = NULL;
  int z = hash2_find(ht, key);
  if (ht->keys[z] != NULL)
    result = ht->values[z];
  return result;
}
int hash2_get_size(Hashtable2 *ht, Point key)
{
  int z = hash2_find(ht, key);
  assert(ht->keys[z] != NULL);
  return ht->sizes[z];
}
int hash2_put(Hashtable2 *ht, Point key, Point value, int size)
{
  assert(ht->count < ht->capacity);
  int result = 0;
  int k = hash2_find(ht, key);
  result = !ht->keys[k];
  if (result)
  {
    ht->keys[k] = point_dup(key);
    ht->all_keys[ht->n_keys++] = ht->keys[k];
    ht->values[k] = point_dup(value);
    ht->sizes[k] = size;
    ht->count++;
  }
  else
  {
    ht->values[k] = point_dup(value);
    ht->sizes[k] = size;
  }
  return result;
}
void hash2_show(Hashtable2 *ht)
{
  for (int i = 0; i < ht->capacity; i++)
    if (ht->keys[i] != NULL)
    {
      printf("%d ", i);
      point_printf("[%d %d %d]", *ht->keys[i]);
      point_printf("[%d %d %d]", *ht->values[i]);
      printf(" %d\n", ht->sizes[i] );
    }
  points_ref_printf("---[%d %d %d]\n", ht->all_keys, ht->n_keys);
}
int quw_init(Hashtable2 *ht, const Point *a, int n){
  for (int i = 0; i < n; i++)
    hash2_put(ht, a[i], a[i], 1);
  return n;
}
int quw_union(Hashtable2 *ht, int count, Point x, Point y){
  int result = count;
  Point *ix = hash2_get(ht, x);
  Point *iy = hash2_get(ht, y);
  int sx = hash2_get_size(ht, *ix);
  int sy = hash2_get_size(ht, *iy);
  if (point_cmp(*ix, *iy))
  {
    if (sx < sy)
    {
      hash2_put(ht, x, *iy, sx);
      hash2_put(ht, *iy, *iy, sx + sy);
    }
    else
    {
      hash2_put(ht, y, *ix, sy);
      hash2_put(ht, *ix, *ix, sx + sy);
    }
    result--;
  }
  return result;
}
Point *quw_find(Hashtable2 *ht, Point x)
{
  return hash2_get(ht, x);
}
#define MAX_NEEDLES 50000
#define HASH_CAPACITY 200003

Needle ndl_a = {{12,12,2},{10,5,5}};
Needle ndl_b = {{12,12,2},{4,14,15}};
Needle ndl_c = {{12,12,2},{12,20,2}};
Needle ndl_d = {{4,14,15},{10,5,15}};

int qf_connect_needles(Hashtable *ht, int count, Needle *a, int n, int *b){
  int result = 0;
  b[result++] = count;
  for (int i = 0;  i < n; i++){
    count = qf_union(ht, count, a[i].p1, a[i].p2);
    b[result++] = count;
  }
  return result;
}
int qf_chain(Needle *a, int n){
  Point pts[2 * n];
  int n_pts = points_from_needles(a, n, pts);
  points_qsort(pts, n_pts);
  n_pts = points_unique(pts, n_pts, pts);
  Hashtable ht;
  hashtable_make(&ht, HASH_CAPACITY);
  int qf_count = qf_init(&ht, pts, n_pts);
  int counts[n_pts];
  int n_counts = qf_connect_needles(&ht, qf_count, a, n, counts);
  int k = ints_find_duplicate(counts, n_counts);
  int result = k >= 0;
  return result;
}
int quw_connect_needles(Hashtable2 *ht, int count, Needle *a, int n, int *b){
  int result = 0;
  b[result++] = count;
  for (int i = 0;  i < n; i++){
    count = quw_union(ht, count, a[i].p1, a[i].p2);
    b[result++] = count;
  }
  return result;
}
int quw_chain(Needle *a, int n){
  Point pts[2 * n];
  int n_pts = points_from_needles(a, n, pts);
  points_qsort(pts, n_pts);
  n_pts = points_unique(pts, n_pts, pts);
  Hashtable2 ht;
  hashtable2_make(&ht, HASH_CAPACITY);
  int quw_count = quw_init(&ht, pts, n_pts);
  int counts[n_pts];
  int n_counts = quw_connect_needles(&ht, quw_count, a, n, counts);
  int k = ints_find_duplicate(counts, n_counts);
  int result = k >= 0;
  return result;
}
void test_points_from_needles(void){
  Needle ndls[4] = {ndl_a, ndl_b, ndl_c, ndl_d};
  Point pts[8];
  int n_pts = points_from_needles(ndls, 4, pts);
  points_qsort(pts, n_pts);
  n_pts = points_unique(pts, n_pts, pts);
  points_printf("%d %d %d\n", pts, n_pts);
}
void test_hash_table(void){
  Hashtable ht;
  hashtable_make(&ht, 19);
  Needle ndls[4] = {ndl_a, ndl_b, ndl_c, ndl_d};
  Point pts[8];
  int n_pts = points_from_needles(ndls, 4, pts);
  points_qsort(pts, n_pts);
  n_pts = points_unique(pts, n_pts, pts);
  qf_init(&ht, pts, n_pts);
  hash_show(&ht);
}
void test_connect_needles(void){
  Needle ndls[4] = {ndl_a, ndl_b, ndl_c, ndl_d};
  Point pts[8];
  int n_pts = points_from_needles(ndls, 4, pts);
  points_qsort(pts, n_pts);
  n_pts = points_unique(pts, n_pts, pts);
  Hashtable ht;
  hashtable_make(&ht, 19);
  int count = qf_init(&ht, pts, n_pts);
  hash_show(&ht);
  int counts[n_pts];
  int n_counts = qf_connect_needles(&ht, count, ndls, 4, counts);
  ints_println(counts, n_counts, ", ");
}
void test_needles(void){
  Needle ndls_air[MAX_NEEDLES];
  int n_ndls_air = needles_get_some(int_get(), ndls_air);
  printf("%d\n", n_ndls_air);
  needles_print(ndls_air, n_ndls_air);
  printf("----\n");
  Needle ndls_floor[MAX_NEEDLES];
  int n_ndls_floor = needles_project(ndls_air, n_ndls_air, ndls_floor);
  printf("%d\n", n_ndls_floor);
  needles_print(ndls_floor, n_ndls_floor);
  printf("----\n");
  n_ndls_floor = needles_remove_vertical(ndls_floor, n_ndls_floor, ndls_floor);
  printf("%d\n", n_ndls_floor);
  needles_print(ndls_floor, n_ndls_floor);
  printf("----\n");
  needles_qsort(ndls_floor, n_ndls_floor);
  printf("%d\n", n_ndls_floor);
  needles_print(ndls_floor, n_ndls_floor);
  printf("----\n");
  n_ndls_floor = needles_unique(ndls_floor, n_ndls_floor, ndls_floor);
  printf("%d\n", n_ndls_floor);
  needles_print(ndls_floor, n_ndls_floor);
  printf("----\n");
  printf("%d\n", n_ndls_floor);
}
#define m1Yes "True closed chains"
#define m1No  "No true closed chains"
#define m2Yes "Floor closed chains"
#define m2No  "No floor closed chains"

void task_qf(){
  Needle ndls_air[MAX_NEEDLES];
  int n_ndls_air = needles_get_some(int_get(), ndls_air);
  int b1 = qf_chain(ndls_air, n_ndls_air);
  printf("%s\n", (b1 ? m1Yes : m1No));
  Needle ndls_floor[MAX_NEEDLES];
  int n_ndls_floor = needles_project(ndls_air, n_ndls_air, ndls_floor);
  n_ndls_floor = needles_remove_vertical(ndls_floor, n_ndls_floor, ndls_floor);
  needles_qsort(ndls_floor, n_ndls_floor);
  n_ndls_floor = needles_unique(ndls_floor, n_ndls_floor, ndls_floor);
  int b2 = qf_chain(ndls_floor, n_ndls_floor);
  printf("%s\n", (b2 ? m2Yes : m2No));
}
void task_quw(){
  Needle ndls_air[MAX_NEEDLES];
  int n_ndls_air = needles_get_some(int_get(), ndls_air);
  int b1 = quw_chain(ndls_air, n_ndls_air);
  printf("%s\n", (b1 ? m1Yes : m1No));
  Needle ndls_floor[MAX_NEEDLES];
  int n_ndls_floor = needles_project(ndls_air, n_ndls_air, ndls_floor);
  n_ndls_floor = needles_remove_vertical(ndls_floor, n_ndls_floor, ndls_floor);
  needles_qsort(ndls_floor, n_ndls_floor);
  n_ndls_floor = needles_unique(ndls_floor, n_ndls_floor, ndls_floor);
  int b2 = quw_chain(ndls_floor, n_ndls_floor);
  printf("%s\n", (b2 ? m2Yes : m2No));
}
int main(int argc, char **argv){
  int x = 'E';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_points_from_needles();
  else if (x == 'B')
    test_hash_table();
  else if (x == 'C')
    test_connect_needles();
  else if (x == 'D')
    task_qf();
  else if (x == 'E')
    task_quw();
  else if (x == 'F')
    test_needles();
  else
    printf("%c Invalid option.\n", x);
  return 0;
}
