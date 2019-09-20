#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<stddef.h>
#include<limits.h>
typedef struct _dtlink_s Dtlink_t;
typedef struct _dthold_s Dthold_t;
typedef struct _dtdisc_s Dtdisc_t;
typedef struct _dtmethod_s Dtmethod_t;
typedef struct _dtdata_s Dtdata_t;
typedef struct _dt_s Dt_t;
typedef struct _dt_s Dict_t;
typedef struct _dtstat_s Dtstat_t;
typedef void* (*Dtmemory_f)(Dt_t*,void*,size_t,Dtdisc_t*);
typedef void* (*Dtsearch_f)(Dt_t*,void*,int);
typedef void* (*Dtmake_f)(Dt_t*,void*,Dtdisc_t*);
typedef void (*Dtfree_f)(Dt_t*,void*,Dtdisc_t*);
typedef int (*Dtcompar_f)(Dt_t*,void*,void*,Dtdisc_t*);
typedef unsigned int (*Dthash_f)(Dt_t*,void*,Dtdisc_t*);
typedef int (*Dtevent_f)(Dt_t*,int,void*,Dtdisc_t*);
struct _dtlink_s
{ Dtlink_t* right;
  union
  { unsigned int _hash;
    Dtlink_t* _left;
  } hl;
};
struct _dthold_s
{ Dtlink_t hdr;
  void* obj;
};
struct _dtmethod_s
{ Dtsearch_f searchf;
  int type;
};
struct _dtdata_s
{ int type;
  Dtlink_t* here;
  union
  { Dtlink_t** _htab;
    Dtlink_t* _head;
  } hh;
  int ntab;
  int size;
  int loop;
  int minp;
};
struct _dtdisc_s
{ int key;
  int size;
  int link;
  Dtmake_f makef;
  Dtfree_f freef;
  Dtcompar_f comparf;
  Dthash_f hashf;
  Dtmemory_f memoryf;
  Dtevent_f eventf;
};
struct _dt_s
{ Dtsearch_f searchf;
  Dtdisc_t* disc;
  Dtdata_t* data;
  Dtmemory_f memoryf;
  Dtmethod_t* meth;
  int type;
  int nview;
  Dt_t* view;
  Dt_t* walk;
  void* user;
};
struct _dtstat_s
{ int dt_meth;
  int dt_size;
  int dt_n;
  int dt_max;
  int* dt_count;
};
 Dtmethod_t* Dtset;
 Dtmethod_t* Dtbag;
 Dtmethod_t* Dtoset;
 Dtmethod_t* Dtobag;
 Dtmethod_t* Dtlist;
 Dtmethod_t* Dtstack;
 Dtmethod_t* Dtqueue;
 Dtmethod_t* Dtdeque;
 Dtmethod_t* Dtorder;
 Dtmethod_t* Dttree;
 Dtmethod_t* Dthash;
 Dtmethod_t _Dttree;
 Dtmethod_t _Dthash;
 Dtmethod_t _Dtlist;
 Dtmethod_t _Dtqueue;
 Dtmethod_t _Dtstack;
 Dt_t* dtopen(Dtdisc_t*, Dtmethod_t*);
 int dtclose(Dt_t*);
 Dt_t* dtview(Dt_t*, Dt_t*);
 Dtdisc_t* dtdisc(Dt_t* dt, Dtdisc_t*, int);
 Dtmethod_t* dtmethod(Dt_t*, Dtmethod_t*);
 Dtlink_t* dtflatten(Dt_t*);
 Dtlink_t* dtextract(Dt_t*);
 int dtrestore(Dt_t*, Dtlink_t*);
 int dttreeset(Dt_t*, int, int);
 int dtwalk(Dt_t*, int(*)(Dt_t*,void*,void*), void*);
 void* dtrenew(Dt_t*, void*);
 int dtsize(Dt_t*);
 int dtstat(Dt_t*, Dtstat_t*, int);
 unsigned int dtstrhash(unsigned int, void*, int);
static compare(Dt_t * dt, void * o1, void * o2, Dtdisc_t * disc){
  return (int) o1 - (int) o2;
}
static rcompare(Dt_t * dt, void * o1, void * o2, Dtdisc_t * disc){
  return (int) o2 - (int) o1;
}
static void *newint(Dt_t * dt, void * o, Dtdisc_t * disc){
  return o;
}
static unsigned int hashint(Dt_t * dt, void * o, Dtdisc_t * disc){
  return (unsigned int) o;
}
void terror(char *s){
  printf("Error: %s\n", s);
  exit(-1);
}
int dtclose(register Dt_t* dt)
{
 Dtdisc_t *disc;
 int ev = 0;
 if(!dt || dt->nview > 0 )
  return -1;
 disc = dt->disc;
 if(disc->eventf &&
    (ev = (*disc->eventf)(dt,2,((void*)0),disc)) < 0)
  return -1;
 if(dt->view)
  dtview(dt,((Dt_t*)0));
 if(ev == 0)
 { (void)(*(dt->meth->searchf))(dt,((void*)0),0000100);
  if(dtsize(dt) > 0)
   return -1;
  if(dt->data->ntab > 0)
   (*dt->memoryf)(dt,(void*)dt->data->hh._htab,0,disc);
  (*dt->memoryf)(dt,(void*)dt->data,0,disc);
 }
 if(dt->type == 0)
  free((void*)dt);
 else if(ev == 0 && dt->type == 1)
  (*dt->memoryf)(dt, (void*)dt, 0, disc);
 if(disc->eventf)
  (void)(*disc->eventf)(dt, 6, ((void*)0), disc);
 return 0;
}
static void* dtmemory(Dt_t* dt,void* addr,size_t size,Dtdisc_t* disc)
{
 if(addr)
 { if(size == 0)
  { free(addr);
   return ((void*)0);
  }
  else return realloc(addr,size);
 }
 else return size > 0 ? malloc(size) : ((void*)0);
}
Dtdisc_t* dtdisc(Dt_t* dt, Dtdisc_t* disc, int type)
{
 register Dtsearch_f searchf;
 register Dtlink_t *r, *t;
 register char* k;
 register Dtdisc_t* old;
 if(!(old = dt->disc) )
 { dt->disc = disc;
  if(!(dt->memoryf = disc->memoryf) )
   dt->memoryf = dtmemory;
  return disc;
 }
 if(!disc)
  return old;
 searchf = dt->meth->searchf;
 ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
 if(old->eventf && (*old->eventf)(dt,3,(void*)disc,old) < 0)
  return ((Dtdisc_t*)0);
 dt->disc = disc;
 if(!(dt->memoryf = disc->memoryf) )
  dt->memoryf = dtmemory;
 if(dt->data->type&(0000040|0000100|0000020))
  goto done;
 else if(dt->data->type&0000002)
 { if(type&0000002)
   goto done;
  else goto dt_renew;
 }
 else if(dt->data->type&(0000001|0000002))
 { if((type&0000002) && (type&0000001))
   goto done;
  else goto dt_renew;
 }
 else
 { if(type&0000001)
   goto done;
 dt_renew:
  r = dtflatten(dt);
  dt->data->type &= ~010000;
  dt->data->here = ((Dtlink_t*)0);
  dt->data->size = 0;
  if(dt->data->type&(0000001|0000002))
  { register Dtlink_t **s, **ends;
   ends = (s = dt->data->hh._htab) + dt->data->ntab;
   while(s < ends)
    *s++ = ((Dtlink_t*)0);
  }
  while(r)
  { t = r->right;
   if(!(type&0000002))
   { k = (char*)(disc->link < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - disc->link) );
    k = (void*)(disc->size < 0 ? *((char**)((char*)((void*)k)+disc->key)) : ((char*)((void*)k)+disc->key));
    r->hl._hash = (disc->hashf ? (*disc->hashf)(dt,k,disc) : dtstrhash(0,k,disc->size) );
   }
   (void)(*searchf)(dt,(void*)r,0000040);
   r = t;
  }
 }
done:
 return old;
}
Dtlink_t* dtextract(register Dt_t* dt)
{
  register Dtlink_t *list, **s, **ends;
  if(dt->data->type&(0000004|0000010) )
    list = dt->data->here;
  else if(dt->data->type&(0000001|0000002))
  { list = dtflatten(dt);
    for(ends = (s = dt->data->hh._htab) + dt->data->ntab; s < ends; ++s)
      *s = ((Dtlink_t*)0);
  }
  else
  { list = dt->data->hh._head;
    dt->data->hh._head = ((Dtlink_t*)0);
  }
  dt->data->type &= ~010000;
  dt->data->size = 0;
  dt->data->here = ((Dtlink_t*)0);
  return list;
}
Dtlink_t* dtflatten(Dt_t* dt)
{
 register Dtlink_t *t, *r, *list, *last, **s, **ends;
 if(dt->data->type&010000 )
  return dt->data->here;
 list = last = ((Dtlink_t*)0);
 if(dt->data->type&(0000001|0000002))
 { for(ends = (s = dt->data->hh._htab) + dt->data->ntab; s < ends; ++s)
  { if((t = *s) )
   { if(last)
     last->right = t;
    else list = last = t;
    while(last->right)
     last = last->right;
    *s = last;
   }
  }
 }
 else if(dt->data->type&(0000020|0000040|0000100) )
  list = dt->data->hh._head;
 else if((r = dt->data->here) )
 { while((t = r->hl._left) )
   (((r)->hl._left = (t)->right, (t)->right = (r)), (r) = (t));
  for(list = last = r, r = r->right; r; last = r, r = r->right)
  { if((t = r->hl._left) )
   { do (((r)->hl._left = (t)->right, (t)->right = (r)), (r) = (t));
    while((t = r->hl._left) );
    last->right = r;
   }
  }
 }
 dt->data->here = list;
 dt->data->type |= 010000;
 return list;
}
static void dthtab(Dt_t* dt)
{
  register Dtlink_t *t, *r, *p, **s, **hs, **is, **olds;
  int n, k;
  if(dt->data->minp > 0 && dt->data->ntab > 0)
    return;
  dt->data->minp = 0;
  n = dt->data->ntab;
  if(dt->disc && dt->disc->eventf &&
     (*dt->disc->eventf)(dt, 7, &n, dt->disc) > 0 )
  { if(n < 0)
    { dt->data->minp = 1;
      if(dt->data->ntab > 0 )
        return;
    }
    else
    { for(k = 2; k < n; k *= 2)
        ;
      n = k;
    }
  }
  else n = 0;
  if(n <= 0)
  { if((n = dt->data->ntab) == 0)
      n = (256);
    while(dt->data->size > ((n) << 1))
      n = ((n) << 1);
  }
  if(n == dt->data->ntab)
    return;
  olds = dt->data->ntab == 0 ? ((Dtlink_t**)0) : dt->data->hh._htab;
  if(!(s = (Dtlink_t**)(*dt->memoryf)(dt,olds,n*sizeof(Dtlink_t*),dt->disc)) )
    return;
  olds = s + dt->data->ntab;
  dt->data->hh._htab = s;
  dt->data->ntab = n;
  for(hs = s+n-1; hs >= olds; --hs)
    *hs = ((Dtlink_t*)0);
  for(hs = s; hs < olds; ++hs)
  { for(p = ((Dtlink_t*)0), t = *hs; t; t = r)
    { r = t->right;
      if((is = s + ((t->hl._hash)&((n)-1))) == hs)
        p = t;
      else
      { if(p)
          p->right = r;
        else *hs = r;
        t->right = *is; *is = t;
      }
    }
  }
}
static void* dthash(Dt_t* dt, register void* obj, int type)
{
  register Dtlink_t *t, *r = NULL, *p;
  register void *k, *key;
  register unsigned int hsh;
  register int lk, sz, ky;
  register Dtcompar_f cmpf;
  register Dtdisc_t* disc;
  register Dtlink_t **s = NULL, **ends;
  ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
  disc = dt->disc; (ky = disc->key, sz = disc->size, lk = disc->link, cmpf = disc->comparf);
  dt->type &= ~0100000;
  if(!obj)
  { if(type&(0000010|0000020))
      goto end_walk;
    if(dt->data->size <= 0 || !(type&(0000100|0000200|0000400)) )
      return ((void*)0);
    ends = (s = dt->data->hh._htab) + dt->data->ntab;
    if(type&0000100)
    {
      for(; s < ends; ++s)
      { t = *s;
        *s = ((Dtlink_t*)0);
        if(!disc->freef && disc->link >= 0)
          continue;
        while(t)
        { r = t->right;
          if(disc->freef)
            (*disc->freef)(dt,(lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ),disc);
          if(disc->link < 0)
            (*dt->memoryf)(dt,(void*)t,0,disc);
          t = r;
        }
      }
      dt->data->here = ((Dtlink_t*)0);
      dt->data->size = 0;
      dt->data->loop = 0;
      return ((void*)0);
    }
    else
    { t = ((Dtlink_t*)0);
      while(s < ends && !t )
        t = (type&0000400) ? *--ends : *s++;
      if(t && (type&0000400))
        for(; t->right; t = t->right)
          ;
      dt->data->loop += 1;
      dt->data->here = t;
      return t ? (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ) : ((void*)0);
    }
  }
  if(dt->meth->type == 0000002 && (type&(0000002|0010000)) )
  { if(!(*(((Dt_t*)(dt))->searchf))((dt),(void*)(obj),0000004) )
      return ((void*)0);
    s = dt->data->hh._htab + ((dt->data->here->hl._hash)&((dt->data->ntab)-1));
    r = ((Dtlink_t*)0);
    for(p = ((Dtlink_t*)0), t = *s; t; p = t, t = t->right)
    { if((lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ) == obj)
        goto do_delete;
      if(t == dt->data->here)
        r = p;
    }
    p = r; t = dt->data->here;
    goto do_delete;
  }
  if(type&(0001000|0000004|0000001|0004000) )
  { key = (type&0001000) ? obj : (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
    hsh = (disc->hashf ? (*disc->hashf)(dt,key,disc) : dtstrhash(0,key,sz) );
    goto do_search;
  }
  else if(type&(0000040|0002000) )
  { r = (Dtlink_t*)obj;
    obj = (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) );
    key = (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
    hsh = r->hl._hash;
    goto do_search;
  }
  else
  { if((t = dt->data->here) && (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ) == obj)
    { hsh = t->hl._hash;
      s = dt->data->hh._htab + ((hsh)&((dt->data->ntab)-1));
      p = ((Dtlink_t*)0);
    }
    else
    { key = (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
      hsh = (disc->hashf ? (*disc->hashf)(dt,key,disc) : dtstrhash(0,key,sz) );
    do_search:
      t = dt->data->ntab <= 0 ? ((Dtlink_t*)0) :
        *(s = dt->data->hh._htab + ((hsh)&((dt->data->ntab)-1)));
      for(p = ((Dtlink_t*)0); t; p = t, t = t->right)
      { if(hsh == t->hl._hash)
        { k = (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
          if((cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) ) == 0)
            break;
        }
      }
    }
  }
  if(t)
    dt->type |= 0100000;
  if(type&(0001000|0000004|0002000))
  { if(!t)
      return ((void*)0);
    if(p && (dt->data->type&0000001) && dt->data->loop <= 0)
    {
      p->right = t->right;
      t->right = *s;
      *s = t;
    }
    dt->data->here = t;
    return (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) );
  }
  else if(type&(0000001|0004000))
  { if(t && (dt->data->type&0000001) )
    { dt->data->here = t;
      return (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) );
    }
    if(disc->makef && (type&0000001) &&
       !(obj = (*disc->makef)(dt,obj,disc)) )
      return ((void*)0);
    if(lk >= 0)
      r = ((Dtlink_t*)((char*)(obj) + lk) );
    else
    { r = (Dtlink_t*)(*dt->memoryf)
        (dt,((void*)0),sizeof(Dthold_t),disc);
      if(r)
        ((Dthold_t*)r)->obj = obj;
      else
      { if(disc->makef && disc->freef && (type&0000001))
          (*disc->freef)(dt,obj,disc);
        return ((void*)0);
      }
    }
    r->hl._hash = hsh;
  do_insert:
    if((dt->data->size += 1) > ((dt->data->ntab) << 1) && dt->data->loop <= 0 )
      dthtab(dt);
    if(dt->data->ntab == 0)
    { dt->data->size -= 1;
      if(disc->freef && (type&0000001))
        (*disc->freef)(dt,obj,disc);
      if(disc->link < 0)
        (*disc->memoryf)(dt,(void*)r,0,disc);
      return ((void*)0);
    }
    s = dt->data->hh._htab + ((hsh)&((dt->data->ntab)-1));
    if(t)
    { r->right = t->right;
      t->right = r;
    }
    else
    { r->right = *s;
      *s = r;
    }
    dt->data->here = r;
    return obj;
  }
  else if(type&0000010)
  { if(t && !(p = t->right) )
    { for(ends = dt->data->hh._htab+dt->data->ntab, s += 1; s < ends; ++s)
        if((p = *s) )
          break;
    }
    goto done_adj;
  }
  else if(type&0000020)
  { if(t && !p)
    { if((p = *s) != t)
      { while(p->right != t)
          p = p->right;
      }
      else
      { p = ((Dtlink_t*)0);
        for(s -= 1, ends = dt->data->hh._htab; s >= ends; --s)
        { if((p = *s) )
          { while(p->right)
              p = p->right;
            break;
          }
        }
      }
    }
  done_adj:
    if(!(dt->data->here = p) )
    { end_walk:
      if((dt->data->loop -= 1) < 0)
        dt->data->loop = 0;
      if(dt->data->size > ((dt->data->ntab) << 1) && dt->data->loop <= 0)
        dthtab(dt);
      return ((void*)0);
    }
    else
    { dt->data->type |= 020000;
      return (lk < 0 ? ((Dthold_t*)(p))->obj : (void*)((char*)(p) - lk) );
    }
  }
  else if(type&0000040)
  { if(!t || (dt->data->type&0000002) )
      goto do_insert;
    else
    { if(disc->freef)
        (*disc->freef)(dt,obj,disc);
      if(disc->link < 0)
        (*dt->memoryf)(dt,(void*)r,0,disc);
      return t ? (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ) : ((void*)0);
    }
  }
  else
  {
  do_delete:
    if(!t)
      return ((void*)0);
    else if(p)
      p->right = t->right;
    else if((p = *s) == t)
      p = *s = t->right;
    else
    { while(p->right != t)
        p = p->right;
      p->right = t->right;
    }
    obj = (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) );
    dt->data->size -= 1;
    dt->data->here = p;
    if(disc->freef && (type&0000002))
      (*disc->freef)(dt,obj,disc);
    if(disc->link < 0)
      (*dt->memoryf)(dt,(void*)t,0,disc);
    return obj;
  }
}
static Dtmethod_t _Dtset = { dthash, 0000001 };
static Dtmethod_t _Dtbag = { dthash, 0000002 };
Dtmethod_t* Dtset = &_Dtset;
Dtmethod_t* Dtbag = &_Dtbag;
Dtmethod_t _Dthash = { dthash, 0000001 };
Dtmethod_t* Dthash = &_Dthash;
static void* dtlist(register Dt_t* dt, register void* obj, register int type)
{
 register int lk, sz, ky;
 register Dtcompar_f cmpf;
 register Dtdisc_t* disc;
 register Dtlink_t *r, *t;
 register void *key, *k;
 ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
 disc = dt->disc; (ky = disc->key, sz = disc->size, lk = disc->link, cmpf = disc->comparf);
 dt->type &= ~0100000;
 if(!obj)
 { if(type&(0000400|0000200) )
  { if((r = dt->data->hh._head) )
   { if(type&0000400)
     r = r->hl._left;
    dt->data->here = r;
   }
   return r ? (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) ) : ((void*)0);
  }
  else if(type&(0000002|0010000))
  { if((dt->data->type&(0000020|0000200)) || !(r = dt->data->hh._head))
    return ((void*)0);
   else goto dt_delete;
  }
  else if(type&0000100)
  { if(disc->freef || disc->link < 0)
   { for(r = dt->data->hh._head; r; r = t)
    { t = r->right;
     if(disc->freef)
      (*disc->freef)(dt,(lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) ),disc);
     if(disc->link < 0)
      (*dt->memoryf)(dt,(void*)r,0,disc);
    }
   }
   dt->data->hh._head = dt->data->here = ((Dtlink_t*)0);
   dt->data->size = 0;
   return ((void*)0);
  }
  else return ((void*)0);
 }
 if(type&(0000001|0004000))
 { if(disc->makef && (type&0000001) &&
     !(obj = (*disc->makef)(dt,obj,disc)) )
   return ((void*)0);
  if(lk >= 0)
   r = ((Dtlink_t*)((char*)(obj) + lk) );
  else
  { r = (Dtlink_t*)(*dt->memoryf)
    (dt,((void*)0),sizeof(Dthold_t),disc);
   if(r)
    ((Dthold_t*)r)->obj = obj;
   else
   { if(disc->makef && disc->freef && (type&0000001))
     (*disc->freef)(dt,obj,disc);
    return ((void*)0);
   }
  }
  if(dt->data->type&0000200)
  { if(type&0020000)
    goto dt_queue;
   else goto dt_stack;
  }
  else if(dt->data->type&0000020)
  { if(type&0020000)
   { if(!(t = dt->data->here) || !t->right)
     goto dt_queue;
    r->right = t->right;
    r->right->hl._left = r;
    r->hl._left = t;
    r->hl._left->right = r;
   }
   else
   { if(!(t = dt->data->here) || t == dt->data->hh._head)
     goto dt_stack;
    r->hl._left = t->hl._left;
    r->hl._left->right = r;
    r->right = t;
    r->right->hl._left = r;
   }
  }
  else if(dt->data->type&0000040)
  { dt_stack:
   r->right = t = dt->data->hh._head;
   if(t)
   { r->hl._left = t->hl._left;
    t->hl._left = r;
   }
   else r->hl._left = r;
   dt->data->hh._head = r;
  }
  else
  { dt_queue:
   if((t = dt->data->hh._head) )
   { t->hl._left->right = r;
    r->hl._left = t->hl._left;
    t->hl._left = r;
   }
   else
   { dt->data->hh._head = r;
    r->hl._left = r;
   }
   r->right = ((Dtlink_t*)0);
  }
  if(dt->data->size >= 0)
   dt->data->size += 1;
  dt->data->here = r;
  return (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) );
 }
 if((type&0001000) || !(r = dt->data->here) || (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) ) != obj)
 { key = (type&0001000) ? obj : (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
  for(r = dt->data->hh._head; r; r = r->right)
  { k = (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
   if((cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) ) == 0)
    break;
  }
 }
 if(!r)
  return ((void*)0);
 dt->type |= 0100000;
 if(type&(0000002|0010000))
 { dt_delete:
  if(r->right)
   r->right->hl._left = r->hl._left;
  if(r == (t = dt->data->hh._head) )
  { dt->data->hh._head = r->right;
   if(dt->data->hh._head)
    dt->data->hh._head->hl._left = t->hl._left;
  }
  else
  { r->hl._left->right = r->right;
   if(r == t->hl._left)
    t->hl._left = r->hl._left;
  }
  dt->data->here = r == dt->data->here ? r->right : ((Dtlink_t*)0);
  dt->data->size -= 1;
  obj = (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) );
  if(disc->freef && (type&0000002))
   (*disc->freef)(dt,obj,disc);
  if(disc->link < 0)
   (*dt->memoryf)(dt,(void*)r,0,disc);
  return obj;
 }
 else if(type&0000010)
  r = r->right;
 else if(type&0000020)
  r = r == dt->data->hh._head ? ((Dtlink_t*)0) : r->hl._left;
 dt->data->here = r;
 return r ? (lk < 0 ? ((Dthold_t*)(r))->obj : (void*)((char*)(r) - lk) ) : ((void*)0);
}
 Dtmethod_t _Dtlist = { dtlist, 0000020 };
 Dtmethod_t _Dtdeque = { dtlist, 0000200 };
 Dtmethod_t _Dtstack = { dtlist, 0000040 };
 Dtmethod_t _Dtqueue = { dtlist, 0000100 };
Dtmethod_t* Dtlist = &_Dtlist;
Dtmethod_t* Dtdeque = &_Dtdeque;
Dtmethod_t* Dtstack = &_Dtstack;
Dtmethod_t* Dtqueue = &_Dtqueue;
Dtmethod_t* dtmethod(Dt_t* dt, Dtmethod_t* meth)
{
 register Dtlink_t *list, *r;
 register Dtdisc_t* disc = dt->disc;
 register Dtmethod_t* oldmeth = dt->meth;
 if(!meth || meth->type == oldmeth->type)
  return oldmeth;
 if(disc->eventf &&
    (*disc->eventf)(dt,4,(void*)meth,disc) < 0)
  return ((Dtmethod_t*)0);
 dt->data->minp = 0;
 list = dtflatten(dt);
 if(dt->data->type&(0000020|0000040|0000100) )
  dt->data->hh._head = ((Dtlink_t*)0);
 else if(dt->data->type&(0000001|0000002) )
 { if(dt->data->ntab > 0)
   (*dt->memoryf)(dt,(void*)dt->data->hh._htab,0,disc);
  dt->data->ntab = 0;
  dt->data->hh._htab = ((Dtlink_t**)0);
 }
 dt->data->here = ((Dtlink_t*)0);
 dt->data->type = (dt->data->type&~(0000377|010000)) | meth->type;
 dt->meth = meth;
 if(dt->searchf == oldmeth->searchf)
  dt->searchf = meth->searchf;
 if(meth->type&(0000020|0000040|0000100) )
 { if(!(oldmeth->type&(0000020|0000040|0000100)) )
  { if((r = list) )
   { register Dtlink_t* t;
    for(t = r->right; t; r = t, t = t->right )
     t->hl._left = r;
    list->hl._left = r;
   }
  }
  dt->data->hh._head = list;
 }
 else if(meth->type&(0000004|0000010))
 { dt->data->size = 0;
  while(list)
  { r = list->right;
   (*meth->searchf)(dt,(void*)list,0000040);
   list = r;
  }
 }
 else if(!((meth->type&0000002) && (oldmeth->type&0000001)) )
 { int rehash;
  if((meth->type&(0000001|0000002)) && !(oldmeth->type&(0000001|0000002)))
   rehash = 1;
  else rehash = 0;
  dt->data->size = dt->data->loop = 0;
  while(list)
  { r = list->right;
   if(rehash)
   { register void* key = (disc->link < 0 ? ((Dthold_t*)(list))->obj : (void*)((char*)(list) - disc->link) );
    key = (void*)(disc->size < 0 ? *((char**)((char*)(key)+disc->key)) : ((char*)(key)+disc->key));
    list->hl._hash = (disc->hashf ? (*disc->hashf)(dt,key,disc) : dtstrhash(0,key,disc->size) );
   }
   (void)(*meth->searchf)(dt,(void*)list,0000040);
   list = r;
  }
 }
 return oldmeth;
}
char* Version = "\n@(#)$Id$\0\n";
Dt_t* dtopen(Dtdisc_t* disc, Dtmethod_t* meth)
{
 Dt_t* dt = (Dt_t*)Version;
 register int e;
 Dtdata_t* data;
 if(!disc || !meth)
  return ((Dt_t*)0);
 if(!(dt = (Dt_t*) malloc(sizeof(Dt_t))))
  return ((Dt_t*)0);
 dt->searchf = ((Dtsearch_f)0);
 dt->meth = ((Dtmethod_t*)0);
 dt->disc = ((Dtdisc_t*)0);
 dtdisc(dt,disc,0);
 dt->type = 0;
 dt->nview = 0;
 dt->view = dt->walk = ((Dt_t*)0);
 dt->user = ((void*)0);
 if(disc->eventf)
 {
  data = ((Dtdata_t*)0);
  if((e = (*disc->eventf)(dt,1,(void*)(&data),disc)) < 0)
   goto err_open;
  else if(e > 0)
  { if(data)
   { if(data->type&meth->type)
     goto done;
    else goto err_open;
   }
   if(!disc->memoryf)
    goto err_open;
   free((void*)dt);
   if(!(dt = (*disc->memoryf)(0, 0, sizeof(Dt_t), disc)) )
    return ((Dt_t*)0);
   dt->searchf = ((Dtsearch_f)0);
   dt->meth = ((Dtmethod_t*)0);
   dt->disc = ((Dtdisc_t*)0);
   dtdisc(dt,disc,0);
   dt->type = 1;
   dt->nview = 0;
   dt->view = dt->walk = ((Dt_t*)0);
  }
 }
 if(!(data = (Dtdata_t*)(dt->memoryf)(dt,((void*)0),sizeof(Dtdata_t),disc)) )
 { err_open:
  free((void*)dt);
  return ((Dt_t*)0);
 }
 data->type = meth->type;
 data->here = ((Dtlink_t*)0);
 data->hh._htab = ((Dtlink_t**)0);
 data->ntab = data->size = data->loop = 0;
 data->minp = 0;
done:
 dt->data = data;
 dt->searchf = meth->searchf;
 dt->meth = meth;
 if(disc->eventf)
  (*disc->eventf)(dt, 5, (void*)dt, disc);
 return dt;
}
void* dtrenew(Dt_t* dt, register void* obj)
{
 register void* key;
 register Dtlink_t *e, *t, **s;
 register Dtdisc_t* disc = dt->disc;
 ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
 if(!(e = dt->data->here) || (disc->link < 0 ? ((Dthold_t*)(e))->obj : (void*)((char*)(e) - disc->link) ) != obj)
  return ((void*)0);
 if(dt->data->type&(0000040|0000100|0000020))
  return obj;
 else if(dt->data->type&(0000004|0000010) )
 { if(!e->right )
   dt->data->here = e->hl._left;
  else
  { dt->data->here = e->right;
   if(e->hl._left)
   { for(t = e->right; t->hl._left; t = t->hl._left)
     ;
    t->hl._left = e->hl._left;
   }
  }
 }
 else
 { s = dt->data->hh._htab + ((e->hl._hash)&((dt->data->ntab)-1));
  if((t = *s) == e)
   *s = e->right;
  else
  { for(; t->right != e; t = t->right)
    ;
   t->right = e->right;
  }
  key = (void*)(disc->size < 0 ? *((char**)((char*)(obj)+disc->key)) : ((char*)(obj)+disc->key));
  e->hl._hash = (disc->hashf ? (*disc->hashf)(dt,key,disc) : dtstrhash(0,key,disc->size) );
  dt->data->here = ((Dtlink_t*)0);
 }
 dt->data->size -= 1;
 return (*dt->meth->searchf)(dt,(void*)e,0000040) ? obj : ((void*)0);
}
int dtrestore(register Dt_t* dt, register Dtlink_t* list)
{
 register Dtlink_t *t, **s, **ends;
 register int type;
 register Dtsearch_f searchf = dt->meth->searchf;
 type = dt->data->type&010000;
 if(!list)
 { if(!type)
   return -1;
  list = dt->data->here;
 }
 else
 { if(dt->data->size != 0)
   return -1;
  type = 0;
 }
 dt->data->type &= ~010000;
 if(dt->data->type&(0000001|0000002))
 { dt->data->here = ((Dtlink_t*)0);
  if(type)
  { for(ends = (s = dt->data->hh._htab) + dt->data->ntab; s < ends; ++s)
   { if((t = *s) )
    { *s = list;
     list = t->right;
     t->right = ((Dtlink_t*)0);
    }
   }
  }
  else
  { dt->data->size = 0;
   while(list)
   { t = list->right;
    (*searchf)(dt,(void*)list,0000040);
    list = t;
   }
  }
 }
 else
 { if(dt->data->type&(0000004|0000010))
   dt->data->here = list;
  else
  { dt->data->here = ((Dtlink_t*)0);
   dt->data->hh._head = list;
  }
  if(!type)
   dt->data->size = -1;
 }
 return 0;
}
int treecount(register Dtlink_t* e)
{ return e ? treecount(e->hl._left) + treecount(e->right) + 1 : 0;
}
int dtsize(Dt_t* dt)
{
 register Dtlink_t* t;
 register int size;
 ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
 if(dt->data->size < 0)
 { if(dt->data->type&(0000004|0000010))
   dt->data->size = treecount(dt->data->here);
  else if(dt->data->type&(0000020|0000040|0000100))
  { for(size = 0, t = dt->data->hh._head; t; t = t->right)
    size += 1;
   dt->data->size = size;
  }
 }
 return dt->data->size;
}
 void dttstat(Dtstat_t* ds, Dtlink_t* root, int depth, int* level)
{
 if(root->hl._left)
  dttstat(ds,root->hl._left,depth+1,level);
 if(root->right)
  dttstat(ds,root->right,depth+1,level);
 if(depth > ds->dt_n)
  ds->dt_n = depth;
 if(level)
  level[depth] += 1;
}
 void dthstat(register Dtdata_t* data, Dtstat_t* ds, register int* count)
{
 register Dtlink_t* t;
 register int n, h;
 for(h = data->ntab-1; h >= 0; --h)
 { n = 0;
  for(t = data->hh._htab[h]; t; t = t->right)
   n += 1;
  if(count)
   count[n] += 1;
  else if(n > 0)
  { ds->dt_n += 1;
   if(n > ds->dt_max)
    ds->dt_max = n;
  }
 }
}
int dtstat(register Dt_t* dt, Dtstat_t* ds, int all)
{
 register int i;
 int *Count, Size;
 ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
 ds->dt_n = ds->dt_max = 0;
 ds->dt_count = ((int*)0);
 ds->dt_size = dtsize(dt);
 ds->dt_meth = dt->data->type&0000377;
 if(!all)
  return 0;
 if(dt->data->type&(0000001|0000002))
 { dthstat(dt->data,ds,((int*)0));
  if(ds->dt_max+1 > Size)
  { if(Size > 0)
    free(Count);
   if(!(Count = (int*)malloc((ds->dt_max+1)*sizeof(int))) )
    return -1;
   Size = ds->dt_max+1;
  }
  for(i = ds->dt_max; i >= 0; --i)
   Count[i] = 0;
  dthstat(dt->data,ds,Count);
 }
 else if(dt->data->type&(0000004|0000010))
 { if(dt->data->here)
  { dttstat(ds,dt->data->here,0,((int*)0));
   if(ds->dt_n+1 > Size)
   { if(Size > 0)
     free(Count);
    if(!(Count = (int*)malloc((ds->dt_n+1)*sizeof(int))) )
     return -1;
    Size = ds->dt_n+1;
   }
   for(i = ds->dt_n; i >= 0; --i)
    Count[i] = 0;
   dttstat(ds,dt->data->here,0,Count);
   for(i = ds->dt_n; i >= 0; --i)
    if(Count[i] > ds->dt_max)
     ds->dt_max = Count[i];
  }
 }
 ds->dt_count = Count;
 return 0;
}
unsigned int dtstrhash(register unsigned int h, void* args, register int n)
{
 register unsigned char* s = (unsigned char*)args;
 if(n <= 0)
 { for(; *s != 0; s += s[1] ? 2 : 1)
   h = (h + (s[0]<<8) + s[1])*17109811;
  n = s - (unsigned char*)args;
 }
 else
 { register unsigned char* ends;
  for(ends = s+n-1; s < ends; s += 2)
   h = (h + (s[0]<<8) + s[1])*17109811;
  if(s <= ends)
   h = (h + (s[0]<<8))*17109811;
 }
 return (h+n)*17109811;
}
 void* dttree(Dt_t* dt, void* obj, int type){
  Dtlink_t *root, *t;
  int cmp, lk, sz, ky;
  void *o, *k, *key;
  Dtlink_t *l, *r, *me = NULL, link;
  int n, minp, turn[(sizeof(size_t)*8 - 2)];
  Dtcompar_f cmpf;
  Dtdisc_t* disc;
  ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
  disc = dt->disc; (ky = disc->key, sz = disc->size, lk = disc->link, cmpf = disc->comparf);
  dt->type &= ~0100000;
  root = dt->data->here;
  if(!obj)
  { if(!root || !(type&(0000100|0000200|0000400)) )
      return ((void*)0);
    if(type&0000100)
    { if(disc->freef || disc->link < 0)
      { do
        { while((t = root->hl._left) )
            (((root)->hl._left = (t)->right, (t)->right = (root)), (root) = (t));
          t = root->right;
          if(disc->freef)
            (*disc->freef)(dt,(lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) ),disc);
          if(disc->link < 0)
            (*dt->memoryf)(dt,(void*)root,0,disc);
        } while((root = t) );
      }
      dt->data->size = 0;
      dt->data->here = ((Dtlink_t*)0);
      return ((void*)0);
    }
    else
    { if(type&0000400)
      { while((t = root->right) )
          (((root)->right = (t)->hl._left, (t)->hl._left = (root)), (root) = (t));
      }
      else
      { while((t = root->hl._left) )
          (((root)->hl._left = (t)->right, (t)->right = (root)), (root) = (t));
      }
      dt->data->here = root;
      return (lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) );
    }
  }
  l = r = &link;
  if(dt->meth->type == 0000010 && (type&(0000002|0010000)) )
  { key = (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
    for(o = (*(((Dt_t*)(dt))->searchf))((dt),(void*)(obj),0000004); o; o = (*(((Dt_t*)(dt))->searchf))((dt),(void*)(o),0000010) )
    { k = (void*)(sz < 0 ? *((char**)((char*)(o)+ky)) : ((char*)(o)+ky));
      if((cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) ) != 0)
        break;
      if(o == obj)
      { root = dt->data->here;
        l->right = root->hl._left;
        r->hl._left = root->right;
        goto dt_delete;
      }
    }
  }
  if(type&(0001000|0000004|0000001|0004000))
  { key = (type&0001000) ? obj : (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
    if(root)
      goto do_search;
  }
  else if(type&0000040)
  { me = (Dtlink_t*)obj;
    obj = (lk < 0 ? ((Dthold_t*)(me))->obj : (void*)((char*)(me) - lk) );
    key = (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
    if(root)
      goto do_search;
  }
  else if(root && (lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) ) != obj)
  { key = (void*)(sz < 0 ? *((char**)((char*)(obj)+ky)) : ((char*)(obj)+ky));
  do_search:
    if(dt->meth->type == 0000004 &&
       (minp = dt->data->minp) != 0 && (type&(0001000|0000004)) )
    {
      for(t = root, n = 0; n < minp; ++n)
      { k = (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
        if((cmp = (cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) )) == 0)
          return (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) );
        else
        { turn[n] = cmp;
          if(!(t = cmp < 0 ? t->hl._left : t->right) )
            return ((void*)0);
        }
      }
      for(n = 0; n < minp; n += 2)
      { if(turn[n] < 0)
        { t = root->hl._left;
          if(turn[n+1] < 0)
          { ((root)->hl._left = (t)->right, (t)->right = (root));
            ((r) = (r)->hl._left = (t) );
            root = t->hl._left;
          }
          else
          { ((l) = (l)->right = (t) );
            ((r) = (r)->hl._left = (root) );
            root = t->right;
          }
        }
        else
        { t = root->right;
          if(turn[n+1] > 0)
          { ((root)->right = (t)->hl._left, (t)->hl._left = (root));
            ((l) = (l)->right = (t) );
            root = t->right;
          }
          else
          { ((r) = (r)->hl._left = (t) );
            ((l) = (l)->right = (root) );
            root = t->hl._left;
          }
        }
      }
    }
    while(1)
    { k = (lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
      if((cmp = (cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) )) == 0)
        break;
      else if(cmp < 0)
      { if((t = root->hl._left) )
        { k = (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
          if((cmp = (cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) )) < 0)
          { ((root)->hl._left = (t)->right, (t)->right = (root));
            ((r) = (r)->hl._left = (t) );
            if(!(root = t->hl._left) )
              break;
          }
          else if(cmp == 0)
          { ((r) = (r)->hl._left = (root) );
            root = t;
            break;
          }
          else
          { ((l) = (l)->right = (t) );
            ((r) = (r)->hl._left = (root) );
            if(!(root = t->right) )
              break;
          }
        }
        else
        { ((r) = (r)->hl._left = (root) );
          root = ((Dtlink_t*)0);
          break;
        }
      }
      else
      { if((t = root->right) )
        { k = (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
          if((cmp = (cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) )) > 0)
          { ((root)->right = (t)->hl._left, (t)->hl._left = (root));
            ((l) = (l)->right = (t) );
            if(!(root = t->right) )
              break;
          }
          else if(cmp == 0)
          { ((l) = (l)->right = (root) );
            root = t;
            break;
          }
          else
          { ((r) = (r)->hl._left = (t) );
            ((l) = (l)->right = (root) );
            if(!(root = t->hl._left) )
              break;
          }
        }
        else
        { ((l) = (l)->right = (root) );
          root = ((Dtlink_t*)0);
          break;
        }
      }
    }
  }
  if(root)
  {
    dt->type |= 0100000;
    l->right = root->hl._left;
    r->hl._left = root->right;
    if(type&(0000004|0001000))
    { has_root:
      root->hl._left = link.right;
      root->right = link.hl._left;
      if((dt->meth->type&0000010) && (type&(0000004|0001000)) )
      { key = (lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) ); key = (void*)(sz < 0 ? *((char**)((char*)(key)+ky)) : ((char*)(key)+ky));
        while((t = root->hl._left) )
        {
          while((r = t->right) )
            (((t)->right = (r)->hl._left, (r)->hl._left = (t)), (t) = (r));
          root->hl._left = t;
          k = (lk < 0 ? ((Dthold_t*)(t))->obj : (void*)((char*)(t) - lk) ); k = (void*)(sz < 0 ? *((char**)((char*)(k)+ky)) : ((char*)(k)+ky));
          if((cmpf ? (*cmpf)(dt,key,k,disc) : (sz <= 0 ? strcmp(key,k) : memcmp(key,k,sz)) ) != 0)
            break;
          (((root)->hl._left = (t)->right, (t)->right = (root)), (root) = (t));
        }
      }
      dt->data->here = root;
      return (lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) );
    }
    else if(type&0000010)
    { root->hl._left = link.right;
      root->right = ((Dtlink_t*)0);
      link.right = root;
    dt_next:
      if((root = link.hl._left) )
      { while((t = root->hl._left) )
          (((root)->hl._left = (t)->right, (t)->right = (root)), (root) = (t));
        link.hl._left = root->right;
        goto has_root;
      }
      else goto no_root;
    }
    else if(type&0000020)
    { root->right = link.hl._left;
      root->hl._left = ((Dtlink_t*)0);
      link.hl._left = root;
    dt_prev:
      if((root = link.right) )
      { while((t = root->right) )
          (((root)->right = (t)->hl._left, (t)->hl._left = (root)), (root) = (t));
        link.right = root->hl._left;
        goto has_root;
      }
      else goto no_root;
    }
    else if(type&(0000002|0010000))
    {
    dt_delete:
      obj = (lk < 0 ? ((Dthold_t*)(root))->obj : (void*)((char*)(root) - lk) );
      if(disc->freef && (type&0000002))
        (*disc->freef)(dt,obj,disc);
      if(disc->link < 0)
        (*dt->memoryf)(dt,(void*)root,0,disc);
      if((dt->data->size -= 1) < 0)
        dt->data->size = -1;
      goto no_root;
    }
    else if(type&(0000001|0004000))
    { if(dt->meth->type&0000004)
        goto has_root;
      else
      { root->hl._left = ((Dtlink_t*)0);
        root->right = link.hl._left;
        link.hl._left = root;
        goto dt_insert;
      }
    }
    else if(type&0000040)
    { if(dt->meth->type&0000004)
      { if(disc->freef)
          (*disc->freef)(dt,obj,disc);
        if(disc->link < 0)
          (*dt->memoryf)(dt,(void*)me,0,disc);
      }
      else
      { me->hl._left = ((Dtlink_t*)0);
        me->right = link.hl._left;
        link.hl._left = me;
        dt->data->size += 1;
      }
      goto has_root;
    }
  }
  else
  {
    r->hl._left = ((Dtlink_t*)0);
    l->right = ((Dtlink_t*)0);
    if(type&0000010)
      goto dt_next;
    else if(type&0000020)
      goto dt_prev;
    else if(type&(0000004|0001000))
    { no_root:
      while((t = r->hl._left) )
        r = t;
      r->hl._left = link.right;
      dt->data->here = link.hl._left;
      return (type&0000002) ? obj : ((void*)0);
    }
    else if(type&(0000001|0004000))
    { dt_insert:
      if(disc->makef && (type&0000001))
        obj = (*disc->makef)(dt,obj,disc);
      if(obj)
      { if(lk >= 0)
          root = ((Dtlink_t*)((char*)(obj) + lk) );
        else
        { root = (Dtlink_t*)(*dt->memoryf)
            (dt,((void*)0),sizeof(Dthold_t),disc);
          if(root)
            ((Dthold_t*)root)->obj = obj;
          else if(disc->makef && disc->freef &&
            (type&0000001))
            (*disc->freef)(dt,obj,disc);
        }
      }
      if(root)
      { if(dt->data->size >= 0)
          dt->data->size += 1;
        goto has_root;
      }
      else goto no_root;
    }
    else if(type&0000040)
    { root = me;
      dt->data->size += 1;
      goto has_root;
    }
    else
    { obj = ((void*)0);
      goto no_root;
    }
  }
  return ((void*)0);
}
 Dtmethod_t _Dtoset = { dttree, 0000004 };
 Dtmethod_t _Dtobag = { dttree, 0000010 };
Dtmethod_t* Dtoset = &_Dtoset;
Dtmethod_t* Dtobag = &_Dtobag;
Dtmethod_t _Dttree = { dttree, 0000004 };
Dtmethod_t* Dtorder = &_Dttree;
Dtmethod_t* Dttree = &_Dttree;
 Dtlink_t* treebalance(Dtlink_t* list, int size)
{
  int n;
  Dtlink_t *l, *mid;
  if(size <= 2)
    return list;
  for(l = list, n = size/2 - 1; n > 0; n -= 1)
    l = l->right;
  mid = l->right; l->right = ((Dtlink_t*)0);
  mid->hl._left = treebalance(list, (n = size/2) );
  mid->right = treebalance(mid->right, size - (n + 1));
  return mid;
}
int dttreeset(Dt_t* dt, int minp, int balance)
{
  int size;
  if(dt->meth->type != 0000004)
    return -1;
  size = dtsize(dt);
  if(minp < 0)
  { for(minp = 0; minp < (sizeof(size_t)*8 - 2); ++minp)
      if((1 << minp) >= size)
        break;
    if(minp <= (sizeof(size_t)*8 - 2)-4)
      minp += 4;
  }
  if((dt->data->minp = minp + (minp%2)) > (sizeof(size_t)*8 - 2))
    dt->data->minp = (sizeof(size_t)*8 - 2);
  if(balance)
    dt->data->here = treebalance(dtflatten(dt), size);
  return 0;
}
 void* dtvsearch(Dt_t* dt, register void* obj, register int type)
{
  Dt_t *d, *p;
  void *o, *n, *ok, *nk;
  int cmp, lk, sz, ky;
  Dtcompar_f cmpf;
  if(type&(0000001|0000002|0000100|0000040))
    return (*(dt->meth->searchf))(dt,obj,type);
  if((type&(0001000|0000004)) ||
     ((type&(0000200|0000400)) && !(dt->meth->type&(0000010|0000004)) ) )
  { for(d = dt; d; d = d->view)
      if((o = (*(d->meth->searchf))(d,obj,type)) )
        break;
    dt->walk = d;
    return o;
  }
  if(dt->meth->type & (0000010|0000004) )
  { if(!(type & (0000200|0000400|0000010|0000020)) )
      return ((void*)0);
    n = nk = ((void*)0); p = ((Dt_t*)0);
    for(d = dt; d; d = d->view)
    { if(!(o = (*d->meth->searchf)(d, obj, type)) )
        continue;
      (ky = d->disc->key, sz = d->disc->size, lk = d->disc->link, cmpf = d->disc->comparf);
      ok = (void*)(sz < 0 ? *((char**)((char*)(o)+ky)) : ((char*)(o)+ky));
      if(n)
      { cmp = (cmpf ? (*cmpf)(d,ok,nk,d->disc) : (sz <= 0 ? strcmp(ok,nk) : memcmp(ok,nk,sz)) );
        if(((type & (0000010|0000200)) && cmp < 0) ||
           ((type & (0000020|0000400)) && cmp > 0) )
          goto a_dj;
      }
      else
      { a_dj: p = d;
        n = o;
        nk = ok;
      }
    }
    dt->walk = p;
    return n;
  }
  if(!(type & (0000010|0000020)) )
    return ((void*)0);
  if(!dt->walk || obj != (dt->walk->disc->link < 0 ? ((Dthold_t*)(dt->walk->data->here))->obj : (void*)((char*)(dt->walk->data->here) - dt->walk->disc->link) ) )
  { for(d = dt; d; d = d->view)
      if((o = (*(d->meth->searchf))(d, obj, 0000004)) )
        break;
    dt->walk = d;
    if(!(obj = o) )
      return ((void*)0);
  }
  for(d = dt->walk, obj = (*d->meth->searchf)(d, obj, type);; )
  { while(obj)
    { for(p = dt; ; p = p->view)
      { if(p == d)
          return obj;
        if((*(p->meth->searchf))(p, obj, 0000004) )
          break;
      }
      obj = (*d->meth->searchf)(d, obj, type);
    }
    if(!(d = dt->walk = d->view) )
      return ((void*)0);
    else if(type&0000010)
      obj = (*(d->meth->searchf))(d,((void*)0),0000200);
    else obj = (*(d->meth->searchf))(d,((void*)0),0000400);
  }
}
Dt_t* dtview(register Dt_t* dt, register Dt_t* view)
{
  register Dt_t* d;
  ((dt->data->type&010000) ? dtrestore(dt,((Dtlink_t*)0)) : 0);
  if(view)
  { ((view->data->type&010000) ? dtrestore(view,((Dtlink_t*)0)) : 0);
    if(view->meth != dt->meth)
      return ((Dt_t*)0);
  }
  for(d = view; d; d = d->view)
    if(d == dt)
      return ((Dt_t*)0);
  if((d = dt->view) )
    d->nview -= 1;
  dt->view = dt->walk = ((Dt_t*)0);
  if(!view)
  { dt->searchf = dt->meth->searchf;
    return d;
  }
  dt->view = view;
  dt->searchf = dtvsearch;
  view->nview += 1;
  return view;
}
int dtwalk(register Dt_t* dt, int (*userf)(Dt_t*, void*, void*), void* data)
{
  register void *obj, *next;
  register Dt_t* walk;
  register int rv;
  for(obj = (*(((Dt_t*)(dt))->searchf))((dt),(void*)(0),0000200); obj; )
  { if(!(walk = dt->walk) )
      walk = dt;
    next = (*(((Dt_t*)(dt))->searchf))((dt),(void*)(obj),0000010);
    if((rv = (*userf)(walk, obj, data )) < 0)
      return rv;
    obj = next;
  }
  return 0;
}
Dtdisc_t Disc = { 0, sizeof(long), -1, newint, ((Dtfree_f)0), compare, hashint, ((Dtmemory_f)0), ((Dtevent_f)0) };
typedef Dt_t* multiset;
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first != b->first) return(a->first < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
pair ranges[200000];
int numCases, m, n, s, e;
int main(){
  scanf("%d", &numCases);
  while(numCases-- > 0){
    scanf("%d %d", &m, &n);
    int cnt = 0;
    for(int i=0; i<n; i++){
      scanf("%d %d", &s, &e);
      if(s <= e){
        ranges[cnt++] = newpair(s,e);
        ranges[cnt++] = newpair(s+m,e+m);
      }
      else
        ranges[cnt++] = newpair(s,e+m);
    }
    if(n > m){
      puts("NO");
      continue;
    }
    qsort(ranges, cnt, sizeof(pair), cmpP);
    int c = 0, curC = 0;
    multiset active = dtopen(&Disc, Dtobag);
    bool success = true;
    while(c < 2*m){
      if(dtsize(active)==0){
        if(curC < cnt)
          c = ranges[curC].first;
        else
          break;
      }
      while(curC < cnt && c == ranges[curC].first){
        (*(((Dt_t*)(active))->searchf))((active),(void*)(ranges[curC].second),0000001);
        curC++;
      }
      int latest = (*(((Dt_t*)(active))->searchf))((active),(void*)(0),0000200);
      (*(((Dt_t*)(active))->searchf))((active),(void*)(latest),0000002);
      if(!(c <= latest)){
        success = false;
        break;
      }
      c++;
    }
    puts(success ? "YES" : "NO");
  }
  return 0;
}