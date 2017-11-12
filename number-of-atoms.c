#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>



char *strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);
  if (n < len)
    len = n;
  result = (char *) malloc (len + 1);
  if (!result)
    return 0;
  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 
char*concat(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
char*concatd(char*a, int b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%d", a, b);
  return ptr;
}


///////////////////////
typedef struct{
    int num;
    char name[3];
}mendel;
mendel newMendel(char*a, int b){
    mendel rez;
    strcpy(rez.name, a);
    rez.num=b;
    return rez;
}
mendel chem[120]={
0  ,"#", // Mo
1  ,"H" ,
2  ,"He",
3  ,"Li",
4  ,"Be",
5  ,"B" ,
6  ,"C" ,
7  ,"N" ,
8  ,"O" ,
9  ,"F" ,
10 ,"Ne",
11 ,"Na",
12 ,"Mg",
13 ,"Al",
14 ,"Si",
15 ,"P" ,
16 ,"S" ,
17 ,"Cl",
18 ,"Ar",
19 ,"K" ,
20 ,"Ca",
21 ,"Sc",
22 ,"Ti",
23 ,"V" ,
24 ,"Cr",
25 ,"Mn",
26 ,"Fe",
27 ,"Co",
28 ,"Ni",
29 ,"Cu",
30 ,"Zn",
31 ,"Ga",
32 ,"Ge",
33 ,"As",
34 ,"Se",
35 ,"Br",
36 ,"Kr",
37 ,"Rb",
38 ,"Sr",
39 ,"Y" ,
40 ,"Zr",
41 ,"Nb",
42 ,"Mo",
43 ,"Tc",
44 ,"Ru",
45 ,"Rh",
46 ,"Pd",
47 ,"Ag",
48 ,"Cd",
49 ,"In",
50 ,"Sn",
51 ,"Sb",
52 ,"Te",
53 ,"I" ,
54 ,"Xe",
55 ,"Cs",
56 ,"Ba",
57 ,"La",
58 ,"Ce",
59 ,"Pr",
60 ,"Nd",
61 ,"Pm",
62 ,"Sm",
63 ,"Eu",
64 ,"Gd",
65 ,"Tb",
66 ,"Dy",
67 ,"Ho",
68 ,"Er",
69 ,"Tm",
70 ,"Yb",
71 ,"Lu",
72 ,"Hf",
73 ,"Ta",
74 ,"W" ,
75 ,"Re",
76 ,"Os",
77 ,"Ir",
78 ,"Pt",
79 ,"Au",
80 ,"Hg",
81 ,"Tl",
82 ,"Pb",
83 ,"Bi",
84 ,"Po",
85 ,"At",
86 ,"Rn",
87 ,"Fr",
88 ,"Ra",
89 ,"Ac",
90 ,"Th",
91 ,"Pa",
92 ,"U" ,
93 ,"Np",
94 ,"Pu",
95 ,"Am",
96 ,"Cm",
97 ,"Bk",
98 ,"Cf",
99 ,"Es",
100,"Fm",
101,"Md",
102,"No",
103,"Lr",
104,"Rf",
105,"Db",
106,"Sg",
107,"Bh",
108,"Hs",
109,"Mt",
110,"Ds",
111,"Rg",
112,"Cn",
113,"Nh",
114,"Fl",
115,"Mc",
116,"Lv",
117,"Ts",
118,"Og"
};



int getOffbyEl(char*el){
    int i;
    for(i=1; i<=118; i++)
        if(el[0]== chem[i].name[0] &&
           el[1]== chem[i].name[1] )
              break;
    return i;
}
char*getElByOff(int off){
    int i;
    for(i=1; i<=118; i++)
        if(chem[i].num==off)
            break;
    return chem[i].name;
}
bool is_digit(char c){
    return c>='0'&&c<='9';
}
bool is_big(char c){
    return c>='A'&&c<='Z';
}
bool is_small(char c){
    return c>='a'&&c<='z';
}
int*solve(char*s){
    int ssize = strlen(s);
    int*res = calloc(120, sizeof(int));
    for(int i=0,j; i<ssize; i=j){
        if(s[i]=='('){
            int cnt=1;
            for(j=i+1; cnt>0; j++){
                if(s[j]==')') cnt--;
                else if(s[j]=='(') cnt++;
            }
            int*nxt = solve(substr(s, i+1, j-i-2));
            int mul = 1;
            if(j<ssize && is_digit(s[j])){
                int v = 0;
                for(;j<ssize && is_digit(s[j]);j++){
                    v *= 10;
                    v += s[j]-'0';
                }
                mul = v;
            }
            for(int z=1; z<=118; z++){
                if(nxt[z]>0)
                  res[z] += nxt[z]*mul;
            }
        }
        else{
            int k;
            for(k=i+1; k<ssize && is_small(s[k]); k++);
            int mul=1;
            int v=0;
            for(j=k; k<ssize && is_digit(s[j]); j++){
                v *= 10;
                v += s[j]-'0';
            }
            if(v) mul = v;
            res[getOffbyEl(substr(s, i, k-i))] += mul;
        }
    }
    return res;
}

int cmpM(const void*pa, const void*pb){
    mendel*a=(mendel*)pa;
    mendel*b=(mendel*)pb;
    return strcmp(a->name, b->name);
}
char*countOfAtoms(char*s){
    int*res = solve(s);
    char*an = strdup("");
    mendel arr[188];
    int arrSz = 0;
    for(int i=1; i<=118; i++){
        if(res[i]>0)
          arr[arrSz++]=newMendel(getElByOff(i), res[i]);
    }
    qsort(arr, arrSz, sizeof(mendel), cmpM);
    for(int i=0;i<arrSz;i++){
        an = concat (an, arr[i].name);
        if(arr[i].num>1)
            an = concatd(an, arr[i].num);
    }
    return an;
}
//////////////////////
#ifdef _WIN32
int main(){
    puts(countOfAtoms("Mg(OH)2"));
    return 0;
}
#endif



























