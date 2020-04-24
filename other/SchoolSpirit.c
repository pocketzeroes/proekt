#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int cmpLLr(const void*pb, const void*pa){//rev
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

int main(){
    ll i, j, k, students;
    scanf("%lld\n", &students);
    ll scores[students];
    ll score;
    for(i=0; i<students; i++){
    	scanf("%lld", &score);
    	scores[i] = score;
    }
    qsort(scores, students, sizeof(ll), cmpLLr);//rev
    double initialVal=0.;
    for(i=0; i<students; i++)
    	initialVal += scores[i]*pow(4./5.0, i);
    initialVal /= 5.0;
    double avg = 0.;
    for(i=0; i<students; i++){
    	double thisTot = 0.;
    	ll used=0ll;
    	for(j=0; j<students; j++){
    		if(i != j){
	    		thisTot += scores[j]*pow(4./5.0, used);
	    		used++;
	    	}
    	}
    	thisTot /= 5.0;
    	avg += thisTot;
    }
    avg /= students;
    printf("%.10lf\n%.10lf\n", initialVal, avg);
    return 0;
}
