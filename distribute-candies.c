#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
int min(int a,int b){return a<b?a:b;}

typedef struct iovecS {
	int key;
	int value;
}iovec;
iovec*newIOvec(int k, int v) {
	iovec*rez = malloc(sizeof(iovec));
	rez->key   = k;
	rez->value = v;
	return rez;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef __RB_TREE_H__
#define __RB_TREE_H__ 1
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#ifndef RB_ITER_MAX_HEIGHT
#define RB_ITER_MAX_HEIGHT 64
#endif
struct rb_node;
struct rb_tree;
typedef int(*rb_tree_node_cmp_f) (struct rb_tree *self, struct rb_node *a, struct rb_node *b);
typedef void(*rb_tree_node_f)     (struct rb_tree *self, struct rb_node *node);
struct rb_node {
	int             red;
	struct rb_node *link[2];
	void           *value;
};
struct rb_tree {
	struct rb_node    *root;
	rb_tree_node_cmp_f cmp;
	size_t             size;
	void              *info;
};
struct rb_iter {
	struct rb_tree *tree;
	struct rb_node *node;
	struct rb_node *path[RB_ITER_MAX_HEIGHT];
	size_t          top;
	void           *info;
};
int             rb_tree_node_cmp_ptr_cb(struct rb_tree *self, struct rb_node *a, struct rb_node *b);
void            rb_tree_node_dealloc_cb(struct rb_tree *self, struct rb_node *node);
struct rb_node *rb_node_alloc();
struct rb_node *rb_node_create(void *value);
struct rb_node *rb_node_init(struct rb_node *self, void *value);
void            rb_node_dealloc(struct rb_node *self);
struct rb_tree *rb_tree_alloc();
struct rb_tree *rb_tree_create(rb_tree_node_cmp_f cmp);
struct rb_tree *rb_tree_init(struct rb_tree *self, rb_tree_node_cmp_f cmp);
void            rb_tree_dealloc(struct rb_tree *self, rb_tree_node_f node_cb);
void           *rb_tree_find(struct rb_tree *self, void *value);
int             rb_tree_insert(struct rb_tree *self, void *value);
int             rb_tree_remove(struct rb_tree *self, void *value);
size_t          rb_tree_size(struct rb_tree *self);
int             rb_tree_insert_node(struct rb_tree *self, struct rb_node *node);
int             rb_tree_remove_with_cb(struct rb_tree *self, void *value, rb_tree_node_f node_cb);
int             rb_tree_test(struct rb_tree *self, struct rb_node *root);
struct rb_iter *rb_iter_alloc();
struct rb_iter *rb_iter_init(struct rb_iter *s);
struct rb_iter *rb_iter_create();
void            rb_iter_dealloc(struct rb_iter *self);
void           *rb_iter_first(struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_last(struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_next(struct rb_iter *self);
void           *rb_iter_prev(struct rb_iter *self);
#endif
struct rb_node *rb_node_alloc() {
	return malloc(sizeof(struct rb_node));
}
struct rb_node *rb_node_init(struct rb_node *self, void *value) {
	if (self) {
		self->red = 1;
		self->link[0] = self->link[1] = NULL;
		self->value = value;
	}
	return self;
}
struct rb_node *rb_node_create(void *value) {
	return rb_node_init(rb_node_alloc(), value);
}
void rb_node_dealloc(struct rb_node *self) {
	if (self) {
		free(self);
	}
}
static int rb_node_is_red(const struct rb_node *self) {
	return self ? self->red : 0;
}
static struct rb_node *rb_node_rotate(struct rb_node *self, int dir) {
	struct rb_node *result = NULL;
	if (self) {
		result = self->link[!dir];
		self->link[!dir] = result->link[dir];
		result->link[dir] = self;
		self->red = 1;
		result->red = 0;
	}
	return result;
}
static struct rb_node *rb_node_rotate2(struct rb_node *self, int dir) {
	struct rb_node *result = NULL;
	if (self) {
		self->link[!dir] = rb_node_rotate(self->link[!dir], !dir);
		result = rb_node_rotate(self, dir);
	}
	return result;
}
int rb_tree_node_cmp_ptr_cb(struct rb_tree *self, struct rb_node *a, struct rb_node *b) {
	return (a->value > b->value) - (a->value < b->value);
}
void rb_tree_node_dealloc_cb(struct rb_tree *self, struct rb_node *node) {
	if (self) {
		if (node) {
			rb_node_dealloc(node);
		}
	}
}
struct rb_tree *rb_tree_alloc() {
	return malloc(sizeof(struct rb_tree));
}
struct rb_tree *rb_tree_init(struct rb_tree *self, rb_tree_node_cmp_f node_cmp_cb) {
	if (self) {
		self->root = NULL;
		self->size = 0;
		self->cmp = node_cmp_cb ? node_cmp_cb : rb_tree_node_cmp_ptr_cb;
	}
	return self;
}
struct rb_tree *rb_tree_create(rb_tree_node_cmp_f node_cb) {
	return rb_tree_init(rb_tree_alloc(), node_cb);
}
void rb_tree_dealloc(struct rb_tree *self, rb_tree_node_f node_cb) {
	if (self) {
		if (node_cb) {
			struct rb_node *node = self->root;
			struct rb_node *save = NULL;
			while (node) {
				if (node->link[0] == NULL) {
					save = node->link[1];
					node_cb(self, node);
					node = NULL;
				}
				else {
					save = node->link[0];
					node->link[0] = save->link[1];
					save->link[1] = node;
				}
				node = save;
			}
		}
		free(self);
	}
}
int rb_tree_test(struct rb_tree *self, struct rb_node *root) {
	int lh, rh;
	if (root == NULL)
		return 1;
	else {
		struct rb_node *ln = root->link[0];
		struct rb_node *rn = root->link[1];
		if (rb_node_is_red(root)) {
			if (rb_node_is_red(ln) || rb_node_is_red(rn)) {
				assert(!"Red violation");
				return 0;
			}
		}
		lh = rb_tree_test(self, ln);
		rh = rb_tree_test(self, rn);
		if ((ln != NULL && self->cmp(self, ln, root) >= 0) || (rn != NULL && self->cmp(self, rn, root) <= 0))
		{
			assert(!"Binary tree violation");
			return 0;
		}
		if (lh != 0 && rh != 0 && lh != rh) {
			assert(!"Black violation");
			return 0;
		}
		if (lh != 0 && rh != 0)
			return rb_node_is_red(root) ? lh : lh + 1;
		else
			return 0;
	}
}
void *rb_tree_find(struct rb_tree *self, void *value) {
	void *result = NULL;
	if (self) {
		struct rb_node node = { .value = value };
		struct rb_node *it = self->root;
		int cmp = 0;
		while (it) {
			if ((cmp = self->cmp(self, it, &node))) {
				it = it->link[cmp < 0];
			}
			else {
				break;
			}
		}
		result = it ? it->value : NULL;
	}
	return result;
}
int rb_tree_insert(struct rb_tree *self, void *value) {
	return rb_tree_insert_node(self, rb_node_create(value));
}
int rb_tree_insert_node(struct rb_tree *self, struct rb_node *node) {
	int result = 0;
	if (self && node) {
		if (self->root == NULL) {
			self->root = node;
			result = 1;
		}
		else {
			struct rb_node head = { 0 };
			struct rb_node *g, *t;
			struct rb_node *p, *q;
			int dir = 0, last = 0;
			t = &head;
			g = p = NULL;
			q = t->link[1] = self->root;
			while (1) {
				if (q == NULL) {
					p->link[dir] = q = node;
				}
				else if (rb_node_is_red(q->link[0]) && rb_node_is_red(q->link[1])) {
					q->red = 1;
					q->link[0]->red = 0;
					q->link[1]->red = 0;
				}
				if (rb_node_is_red(q) && rb_node_is_red(p)) {
					int dir2 = t->link[1] == g;
					if (q == p->link[last]) {
						t->link[dir2] = rb_node_rotate(g, !last);
					}
					else {
						t->link[dir2] = rb_node_rotate2(g, !last);
					}
				}
				if (self->cmp(self, q, node) == 0) {
					break;
				}
				last = dir;
				dir = self->cmp(self, q, node) < 0;
				if (g != NULL) {
					t = g;
				}
				g = p, p = q;
				q = q->link[dir];
			}
			self->root = head.link[1];
		}
		self->root->red = 0;
		++self->size;
	}
	return 1;
}
int rb_tree_remove_with_cb(struct rb_tree *self, void *value, rb_tree_node_f node_cb) {
	if (self->root != NULL) {
		struct rb_node head = { 0 };
		struct rb_node node = { .value = value };
		struct rb_node *q, *p, *g;
		struct rb_node *f = NULL;
		int dir = 1;
		q = &head;
		g = p = NULL;
		q->link[1] = self->root;
		while (q->link[dir] != NULL) {
			int last = dir;
			g = p, p = q;
			q = q->link[dir];
			dir = self->cmp(self, q, &node) < 0;
			if (self->cmp(self, q, &node) == 0) {
				f = q;
			}
			if (!rb_node_is_red(q) && !rb_node_is_red(q->link[dir])) {
				if (rb_node_is_red(q->link[!dir])) {
					p = p->link[last] = rb_node_rotate(q, dir);
				}
				else if (!rb_node_is_red(q->link[!dir])) {
					struct rb_node *s = p->link[!last];
					if (s) {
						if (!rb_node_is_red(s->link[!last]) && !rb_node_is_red(s->link[last])) {
							p->red = 0;
							s->red = 1;
							q->red = 1;
						}
						else {
							int dir2 = g->link[1] == p;
							if (rb_node_is_red(s->link[last])) {
								g->link[dir2] = rb_node_rotate2(p, last);
							}
							else if (rb_node_is_red(s->link[!last])) {
								g->link[dir2] = rb_node_rotate(p, last);
							}
							q->red = g->link[dir2]->red = 1;
							g->link[dir2]->link[0]->red = 0;
							g->link[dir2]->link[1]->red = 0;
						}
					}
				}
			}
		}
		if (f) {
			void *tmp = f->value;
			f->value = q->value;
			q->value = tmp;
			p->link[p->link[1] == q] = q->link[q->link[0] == NULL];
			if (node_cb) {
				node_cb(self, q);
			}
			q = NULL;
		}
		self->root = head.link[1];
		if (self->root != NULL) {
			self->root->red = 0;
		}
		--self->size;
	}
	return 1;
}
int rb_tree_remove(struct rb_tree *self, void *value) {
	int result = 0;
	if (self) {
		result = rb_tree_remove_with_cb(self, value, rb_tree_node_dealloc_cb);
	}
	return result;
}
size_t rb_tree_size(struct rb_tree *self) {
	size_t result = 0;
	if (self) {
		result = self->size;
	}
	return result;
}
struct rb_iter *rb_iter_alloc() {
	return malloc(sizeof(struct rb_iter));
}
struct rb_iter *rb_iter_init(struct rb_iter *self) {
	if (self) {
		self->tree = NULL;
		self->node = NULL;
		self->top = 0;
	}
	return self;
}
struct rb_iter *rb_iter_create() {
	return rb_iter_init(rb_iter_alloc());
}
void rb_iter_dealloc(struct rb_iter *self) {
	if (self) {
		free(self);
	}
}
static void * rb_iter_start(struct rb_iter *self, struct rb_tree *tree, int dir) {
	void *result = NULL;
	if (self) {
		self->tree = tree;
		self->node = tree->root;
		self->top = 0;
		if (self->node != NULL) {
			while (self->node->link[dir] != NULL) {
				self->path[self->top++] = self->node;
				self->node = self->node->link[dir];
			}
		}
		result = self->node == NULL ? NULL : self->node->value;
	}
	return result;
}
static void * rb_iter_move(struct rb_iter *self, int dir) {
	if (self->node->link[dir] != NULL) {
		self->path[self->top++] = self->node;
		self->node = self->node->link[dir];
		while (self->node->link[!dir] != NULL) {
			self->path[self->top++] = self->node;
			self->node = self->node->link[!dir];
		}
	}
	else {
		struct rb_node *last = NULL;
		do {
			if (self->top == 0) {
				self->node = NULL;
				break;
			}
			last = self->node;
			self->node = self->path[--self->top];
		} while (last == self->node->link[dir]);
	}
	return self->node == NULL ? NULL : self->node->value;
}
void *rb_iter_first(struct rb_iter *self, struct rb_tree *tree) {
	return rb_iter_start(self, tree, 0);
}
void *rb_iter_last(struct rb_iter *self, struct rb_tree *tree) {
	return rb_iter_start(self, tree, 1);
}
void *rb_iter_next(struct rb_iter *self) {
	return rb_iter_move(self, 1);
}
void *rb_iter_prev(struct rb_iter *self) {
	return rb_iter_move(self, 0);
}
int my_cmp_cb(struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
	iovec *a = (iovec *)node_a->value;
	iovec *b = (iovec *)node_b->value;
	return a->key - b->key;
}
bool rb_tree_is_in(struct rb_tree *t, void *v) {
	iovec*f = rb_tree_find(t, v);
	return f != NULL;
}
typedef struct rb_tree rbTree;

int distributeCandies(int*candies, int candiesSz){
    rbTree*s=rb_tree_create(my_cmp_cb);
    for(int i=0;i<candiesSz;i++){int c = candies[i];
        iovec*iv=newIOvec(c,0);
        if(!rb_tree_is_in (s,iv))
            rb_tree_insert(s,iv);
    }
    return min(rb_tree_size(s), candiesSz / 2);
}





























