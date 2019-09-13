#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE ((1<<20)+1)
#define HUGE_COST (1<<31-1)
#define NO_PRIO (-1)
#define MAX_OPER (32)
#define DEBUG (0)
#if DEBUG
#define ASSERT(x) if(!(x)) {printf("Assertion failed at %d.\n",__LINE__);exit(1);}
#define HEAPSANITY(x) heapSanity(x)
#else
#define ASSERT(x)
#define HEAPSANITY(x)
#endif
struct tOper{
  int cost;
  int mask;
  int flip;
  int set;
};
struct tMxElem{
  int cost;
  int prio;
};
struct tPrio{
  int cost;
  int who;
};
struct tMxElem Mx[MAX_SIZE];
struct tPrio Heap[MAX_SIZE];
struct tOper op  [MAX_OPER];
int nHeap;
int nop,nw,l;

void heapSanity();



void clearMx(int mag){
  int i;
  for (i=0;i<(1<<mag);i++){
    Mx[i].cost=HUGE_COST;
    Mx[i].prio=NO_PRIO;
  }
  nHeap = 0;
}
void heapBubbleDown(int who){
  int choice;
  struct tPrio dummy;
  while (2*who<=nHeap){
    choice = 2*who;
    if (2*who+1<=nHeap && Heap[choice].cost>Heap[choice+1].cost)
      choice++;
    if (Heap[choice].cost<Heap[who].cost){
      dummy=Heap[choice];
      Heap[choice]=Heap[who];
      Heap[who]=dummy;
      Mx[Heap[who].who].prio=who;
      Mx[Heap[choice].who].prio=choice;
      who=choice;
    }
    else
      break;
  }
}
int heapBubbleUp(int who){
  int choice;
  struct tPrio dummy;
  while (who>1){
    choice = who>>1;
    if (Heap[choice].cost>Heap[who].cost){
      dummy=Heap[choice];
      Heap[choice]=Heap[who];
      Heap[who]=dummy;
      Mx[Heap[who].who].prio=who;
      Mx[Heap[choice].who].prio=choice;
      who=choice;
    }
    else
      break;
  }
  return who;
}
int heapInsert(int who, int cost){
  nHeap++;
  Heap[nHeap].who = who;
  Heap[nHeap].cost = cost;
  who = heapBubbleUp(nHeap);
  HEAPSANITY("heapInsert");
  return who;
}
int heapDecrease(int who, int cost){
  if (Heap[who].cost>cost){
    Heap[who].cost = cost;
    who = heapBubbleUp(who);
    HEAPSANITY("heapDecrease");
    return who;
  }
  else
    return who;
}
int heapExtractMin(struct tPrio*pPrio){
  if (nHeap>0){
    *pPrio = Heap[1];
    Heap[1]=Heap[nHeap--];
    if (nHeap>0){
      Mx[Heap[1].who].prio=1;
      heapBubbleDown(1);
    }
    HEAPSANITY("heapExtractMin");
    return 1;
  }
  else
    return 0;
}
void heapSanity(char*pStr){
  int i=2,j;
  while (i<=nHeap){
    if (Heap[i].cost<Heap[i>>1].cost){
      printf("Heap inconsistent after %s: Size=%d!\n",pStr,nHeap);
      exit(1);
    }
    i++;
  }
}
int solveMx(int source, int dest){
  int i,which,ncost;
  struct tPrio myPrio;
  myPrio.cost = 0;
  myPrio.who = source;
  Mx[source].cost= 0;
  do{
    Mx[myPrio.who].prio=NO_PRIO;
    ASSERT(Mx[myPrio.who].cost == myPrio.cost);
    for (i=0;i<nop;i++){
      which = (((myPrio.who^op[i].flip) & op[i].mask) | op[i].set);
      ncost = myPrio.cost+op[i].cost;
      if (Mx[which].cost>ncost){
        ASSERT(!(Mx[which].prio==NO_PRIO && Mx[which].cost!=HUGE_COST));
        Mx[which].cost = ncost;
        if (Mx[which].prio==NO_PRIO){
          Mx[which].prio = heapInsert(which,ncost);
          ASSERT(Heap[Mx[which].prio].who==which);
        }
        else{
          ASSERT(Heap[Mx[which].prio].who==which);
          Mx[which].prio = heapDecrease(Mx[which].prio,ncost);
          ASSERT(Heap[Mx[which].prio].who==which);
        }
      }
    }
  } while (heapExtractMin(&myPrio) && myPrio.who!=dest);
  return Mx[dest].cost;
}
int main(){
  int n,i,j,k,flip,mask,set,cost,dest,src;
  char ch;
  scanf("%d",&n);
  for (i=0;i<n;i++){
    scanf("%d %d %d",&l,&nop,&nw);
    scanf("%c",&ch);
    for (j=0;j<nop;j++){
      flip = 0;
      mask = 0;
      set = 0;
      for (k=0;k<l;k++){
        scanf("%c",&ch);
        switch (ch){
          case 'N':
            flip = (flip<<1);
            mask = (mask<<1) | 1;
            set = (set<<1);
            break;
          case 'F':
            flip = (flip<<1) | 1;
            mask = (mask<<1) | 1;
            set = (set<<1);
            break;
          case 'S':
            flip = (flip<<1);
            mask = (mask<<1) | 1;
            set = (set<<1) | 1;
            break;
          case 'C':
            flip = (flip<<1);
            mask = (mask<<1);
            set = (set<<1);
            break;
        }
      }
      scanf("%d",&cost);
      scanf("%c",&ch);
      op[j].cost = cost;
      op[j].flip = flip;
      op[j].mask = mask;
      op[j].set = set;
    }
    for (j=0;j<nw;j++){
      src = 0;
      for (k=0;k<l;k++){
        scanf("%c",&ch);
        src = (src<<1) | (ch=='1');
      }
      scanf("%c",&ch);
      dest = 0;
      for (k=0;k<l;k++){
        scanf("%c",&ch);
        dest = (dest<<1) | (ch=='1');
      }
      clearMx(l);
      cost = solveMx(src,dest);
      if (cost==HUGE_COST)
        printf("NP");
      else
        printf("%d",cost);
      if (j!=nw-1)
        printf(" ");
      scanf("%c",&ch);
    }
    printf("\n");
  }
  return 0;
}
