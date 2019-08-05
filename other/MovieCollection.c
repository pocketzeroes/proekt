#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MAXN 100000

struct node {
	struct node *parent, *left, *right;
	int size, depth;
} nodes[MAXN];
void setsize(struct node *node) {
	node->size = 1;
	node->depth = 1;
	if(node->left) {
		node->size += node->left->size;
		node->depth = MAX(node->depth, node->left->depth+1);
	}
	if(node->right) {
		node->size += node->right->size;
		node->depth = MAX(node->depth, node->right->depth+1);
	}
}
struct node *inittree(int from, int to, struct node *parent) {
	if(from > to)
		return NULL;
	int act = (from+to)/2;
	nodes[act].left = inittree(from,act-1,&nodes[act]);
	nodes[act].right = inittree(act+1,to,&nodes[act]);
	nodes[act].parent = parent;
	setsize(&nodes[act]);
	return &nodes[act];
}
void setparent(struct node *node, struct node *new) {
	if(node->parent && node->parent->left == node)
		node->parent->left = new;
	else if(node->parent && node->parent->right == node)
		node->parent->right = new;
}
struct node *balance(struct node *node) {
	int leftd = 0, rightd = 0;
	struct node *a, *b, *c, *A, *B;
	if(node->left) leftd = node->left->depth;
	if(node->right) rightd = node->right->depth;
	if(leftd > rightd + 1) {
		A = node;
		B = A->left;
		a = B->left;
		b = B->right;
		c = A->right;
		B->parent = A->parent;
		setparent(A, B);
		A->left  = b; if(b) b->parent = A;
		A->right = c; if(c) c->parent = A;
		B->left  = a; if(a) a->parent = B;
		B->right = A;       A->parent = B;
		setsize(A); setsize(B);
		node = B;
	}
  else if(leftd + 1 < rightd) {
		A = node;
		B = A->right;
		a = A->left;
		b = B->left;
		c = B->right;
		B->parent = A->parent;
		setparent(A, B);
		A->left  = a; if(a) a->parent = A;
		A->right = b; if(b) b->parent = A;
		B->left  = A;       A->parent = B;
		B->right = c; if(c) c->parent = B;
		setsize(A); setsize(B);
		node = B;
	}
  else {
		setsize(node);
	}
	if(node->parent)
		return balance(node->parent);
	return node;
}

struct node *delete(struct node *node) {
	struct node *ret;
	if(node->left && node->right) {
		struct node *repl = node->left;
		while(repl->right) repl = repl->right;
		ret = delete(repl);
		if(ret == node) ret = repl;
		repl->left = node->left;   if(repl->left)  repl->left->parent = repl;
		repl->right = node->right; if(repl->right) repl->right->parent = repl;
		repl->parent = node->parent;
		setparent(node, repl);
		node->parent = node->left = node->right = NULL;
	}
  else if(node->left) {
		setparent(node, node->left);
		node->left->parent = node->parent;
		ret = node->left;
		node->parent = node->left = NULL;
	}
  else if(node->right) {
		setparent(node, node->right);
		node->right->parent = node->parent;
		ret = node->right;
		node->parent = node->right = NULL;
	}
  else {
		setparent(node, NULL);
		ret = node->parent;
		node->parent = NULL;
	}
	return ret;
}
void testcase() {
	int i, l, n, a, loc;
	struct node *act;
	scanf("%d %d\n", &l, &n);
	inittree(0, l - 1, NULL);
	for(i = 0; i < n; i++) {
		scanf("%d", &a); a--;
		loc = 0;
		for(act = &nodes[a]; act; act = act->parent) {
			if(act->left)
				loc += act->left->size;
			if(act->parent)
				loc += act->parent->left == act ? -act->size : 1;
		}
		if(i) printf(" ");
		printf("%d",loc);
		if(loc > 0) {
			act = delete(&nodes[a]);
			act = balance(act);
			while(act->parent) act = act->parent;
			while(act->left) act = act->left;
			act->left = &nodes[a]; nodes[a].parent = act;
			balance(&nodes[a]);
		}
	}
	printf("\n");
}
int main() {
	int t;
	scanf("%d\n",&t);
	while(t--)
    testcase();
	return 0;
}
