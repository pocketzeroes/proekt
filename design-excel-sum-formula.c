#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


typedef struct {
} Excel;
Excel*ptr;

typedef struct {
  int first;
  int second;
}pii;
pii PII(int a, int b){
  pii rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

typedef struct {
  pii first;
  pii second;
}pair;
pair make_pair(pii a, pii b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair *pushback(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


///////////////
typedef long long ll;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))


int N, M;
int g[50][50], ss[50][50], hasFormula[50][50];
bool evaled = false;
vec formula[50][50];

void evaluate();

Excel* excelCreate(int H, char W) {
  N = H;
  M = W - 'A' + 1;
  FILL(g,0);
  FILL(hasFormula, 0);
  return ptr;
}
void update() {
  FILL(ss, 0);
  REP(i,1,N+1) {
    REP(j,1,M+1) {
      ss[i][j] = ss[i-1][j] + ss[i][j-1] - ss[i-1][j-1] + g[i][j];
    }
  }
}
void excelSet(Excel* obj, int r, char c, int v) {
  g[r][c-'A'+1] = v;
  hasFormula[r][c-'A'+1] = 0;
  evaled = false;
}
int excelGet(Excel* obj, int r, char c) {
  if (hasFormula[r][c-'A'+1]) {
    evaluate();
  }
  return g[r][c-'A'+1];
}
void evaluate() {
  if (evaled) return;
  bool change = true;
  while (change) {
    update();
    change = false;
    REP(x,1,N+1) {
      REP(y,1,M+1) {
        if (hasFormula[x][y]) {
          int oldval = g[x][y], sol = 0;
          REP(i,0,formula[x][y].sz) {
            pii p1 = formula[x][y].ptr[i].first, p2 = formula[x][y].ptr[i].second;
            int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
            if(x2>=0&&y2>=0)
              sol += ss[x2  ][y2  ];
            if(x1-1>=0 && y2 >= 0)
              sol -= ss[x1-1][y2  ];
            if(x2 >=0 && y1-1 >= 0)
              sol -= ss[x2  ][y1-1];
            if(x1-1>=0 && y1-1 >= 0)
              sol += ss[x1-1][y1-1];
          }
          g[x][y] = sol;
          if (sol != oldval) 
              change = true;
        }
      }
    }
  }
  evaled = true;
}

int excelSum(Excel* obj, int r, char c, char** strs){
  vec forms=newVec();

  for(int i=0; ; i++){
      if(strs[i] < 0x1b4)break;
      char*s = strs[i];
    char c, c2;
    int r, r2;
    if(strchr(s,':') == NULL){
      sscanf(s, "%c%d", &c, &r);
      forms.ptr=pushback(forms.ptr, &forms.sz ,make_pair(PII(r,c-'A'+1), PII(r,c-'A'+1)));
    } 
    else {
      sscanf(s, "%c%d:%c%d", &c, &r, &c2, &r2);
      int y = c-'A'+1, y2=c2-'A'+1;
      forms.ptr=pushback(forms.ptr, &forms.sz ,make_pair(PII(r,y), PII(r2,y2)));
    }
  }
  formula[r][c-'A'+1] = forms;
  hasFormula[r][c-'A'+1] = 1;
  evaled = false;
  evaluate();
  return g[r][c-'A'+1];
}

void excelFree(Excel* obj) {
  N=M=0;
  memset(formula, 0, sizeof(formula));
  memset(ss, 0, sizeof(ss));
  evaled = false;
}

#ifdef _WIN32
int main(){
  int rv;
  ptr = excelCreate(26,'Z');
  excelSet(ptr,1,'A',1);
  excelSet(ptr,1,'I',1);
  char*str1[3] = {"A1:D6", "A1:G3", "A1:C12"};
//  printf("count of str1 = %d\n", countof(str1));
  rv = excelSum(ptr,  7,'D', str1);
  char*str2[4] = {"A1:D7", "D1:F10", "D3:I8", "I1:I9"};
  rv = excelSum(ptr, 10, 'G', str2);
  excelFree(ptr);
  return 0;
}
#endif


























