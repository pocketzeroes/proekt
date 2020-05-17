#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

int*peopleIndexes(char***favoriteCompanies, int favoriteCompaniesSz, int*favoriteCompanies0sz, int*rsz){
    vec ans=newVec();
    for(int i=0; i<favoriteCompaniesSz; ++i)
        qsort(favoriteCompanies[i], favoriteCompanies0sz[i], sizeof(char*), cmpstr);
    for(int i=0; i<favoriteCompaniesSz; ++i){
        int ok = 1;
        for(int q=0; q<favoriteCompaniesSz; ++q){
            if(i == q)
                continue;
            int itr = 0;
            for(int j=0; j<favoriteCompanies0sz[q]; ++j){
                if(itr<favoriteCompanies0sz[i] && strcmp(favoriteCompanies[i][itr], favoriteCompanies[q][j])==0)
                    itr++;
            }
            if(itr == favoriteCompanies0sz[i]){
                ok = 0;
                break;
            }
        }
        if(ok == 1)
           pb(ans, i);
    }
   *rsz=ans.sz;
    return ans.ptr;
}
