#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpVec(vec*a, vec*b){
  int msz = fmin(a->sz, b->sz);
  for(int i=0;i < msz; i++){
    if(a->ptr[i] != b->ptr[i]) 
        return (a->ptr[i] < b->ptr[i])?-1:1;
  }
  if(a->sz!=b->sz)
      return (a->sz < b->sz)?-1:1;
  return 0;
}
#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
vecs split(char*s){
  vecs rez=newVecS();
  while(1){
    sscanf(s, "%[a-z]", &buff);
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(buff));
    s = strchr(s, '-');
    if(s==NULL)break;
    s++;
  }
  return rez;
}
///////////////////////////////
typedef struct Person{
    char*name;
    vec  statusList;
}Person;

Person newPerson(char*name, vec statusList){
    return(Person){name, statusList};
}
int cmpP(const void*pa, const void*pb){
    Person*tva=(Person*)pa;
    Person*oth=(Person*)pb;
    int rv = cmpVec(&tva->statusList, &oth->statusList);
    if(rv!=0) return rv;
    return strcmp(tva->name, oth->name);
}
int statusToInteger(char*status){
    if     (strcmp(status, "upper")==0)
        return 1;
    else if(strcmp(status,"middle")==0)
        return 2;
    else
        return 3;
}
void trim(char*str){
    for(int i=0;str[i];i++)
        if(str[i]==':'){
           str[i]='\0';
           return;
        }
}
int main(){
    int numberOfTestCases = in_nextInt();
    for(int i=0; i<numberOfTestCases; i++){
        int numberOfPeople = in_nextInt();
        Person people[numberOfPeople];
        for(int j=0; j<numberOfPeople; j++){
            char*name = getstr();
            trim(name);// mahni :
            char*ionxt = getstr();
            vecs statuses = split(ionxt);
            getstr();
            vec statusList = newVec();
            for(int k = statuses.sz-1; k>=0; k--)
                pb(statusList, statusToInteger(statuses.ptr[k]));
            while(statusList.sz < 10)
                pb(statusList, 2);
            people[j] = newPerson(name, statusList);
        }
        qsort(people, numberOfPeople, sizeof(Person), cmpP);
        for(int j=0; j<numberOfPeople; j++)
            puts(people[j].name);
        puts("==============================");
    }
    return 0;
}
