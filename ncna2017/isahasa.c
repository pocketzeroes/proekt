#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#ifdef _MSC_VER
  #define strdup _strdup
#endif

enum { MAXV = 1000 };
enum { ISA = 0 };
enum { HASA = 1 };

typedef struct edge {
	int dest;
	int type;
	struct edge*next;
}edge;
edge*newEdge(int id, int it, edge*nxt) {
	edge*rez = malloc(sizeof(edge));
	rez->dest = id;
	rez->type = it;
	rez->next = nxt;
	return rez;
}

typedef struct {
	char*name;
	bool visited,
		hasvisited;
	edge*list;
}vertex;
vertex vertices[MAXV];
int  nvert;
bool firsthasa;


void resetVisited() {
	for (int i = 0; i<nvert; i++)
		vertices[i].visited = vertices[i].hasvisited = false;
}
int getVertex(char* s) {
	for (int i = 0; i<nvert; i++)
		if (strcmp(s, vertices[i].name) == 0)
			return i;
	vertices[nvert].name = strdup(s);
	vertices[nvert].list = 0;
	return nvert++;
}
void addEdge(char* src, char* dest, char* type) {
	int is = getVertex(src);
	int id = getVertex(dest);
	int it = ISA;
	if (strcmp(type, "has-a") == 0)
		it = HASA;
	vertices[is].list = newEdge(id, it, vertices[is].list);
}
bool checkIsa(edge *ed, int dest) {
	if (ed->type != ISA)
		return false;
	int d = ed->dest;
	if (vertices[d].visited)
		return false;
	else if (d == dest)
		return true;
	vertices[d].visited = true;
	for (edge* e = vertices[d].list; e != 0; e = e->next) {
		if (checkIsa(e, dest))
			return true;
	}
	return false;
}
bool checkIsaStr(char* src, char* dest) {
	if (strcmp(src, dest) == 0)
		return true;
	int is = getVertex(src);
	int id = getVertex(dest);
	resetVisited();
	vertices[is].visited = true;
	for (edge* e = vertices[is].list; e != 0; e = e->next) {
		if (checkIsa(e, id))
			return true;
	}
	return false;
}
bool checkHasa(edge *ed, int dest, bool hasaFlag) {
	if (ed->type == HASA)
		hasaFlag = true;
	int d = ed->dest;
	if (d == dest && hasaFlag)
		return true;
	else if (vertices[d].visited && ed->type == ISA)
		return false;
	else if (vertices[d].hasvisited && ed->type == HASA)
		return false;
	if (ed->type == ISA)
		vertices[d].visited = true;
	else {
		if (firsthasa) {
			for (int i = 0; i<nvert; i++)
				vertices[i].visited = false;
			firsthasa = false;
		}
		vertices[d].hasvisited = true;
	}
	for (edge* e = vertices[d].list; e != 0; e = e->next) {
		if (checkHasa(e, dest, hasaFlag))
			return true;
	}
	return false;
}
bool checkHasaStr(char* src, char* dest) {
	int is = getVertex(src);
	int id = getVertex(dest);
	resetVisited();
	for (edge* e = vertices[is].list; e != 0; e = e->next) {
		if (checkHasa(e, id, false))
			return true;
	}
	return false;
}
char buff[100000];
int main() {
	int n, m;
	char*s1 = NULL;
	char*s2 = NULL;
	char*s3 = NULL;
	scanf("%d %d", &n, &m);
	nvert = 0;
	for (int i = 0; i<n; i++) {
		scanf("%s", &buff); s1 = strdup(buff);
		scanf("%s", &buff); s2 = strdup(buff);
		scanf("%s", &buff); s3 = strdup(buff);
		addEdge(s1, s3, s2);
	}
	int count = 0;
	for (int i = 1; i <= m; i++){
		if (s1) { free(s1); s1 = NULL; }
		if (s2) { free(s2); s2 = NULL; }
		if (s3) { free(s3); s3 = NULL; }
		scanf("%s", &buff); s1 = strdup(buff);
		scanf("%s", &buff); s2 = strdup(buff);
		scanf("%s", &buff); s3 = strdup(buff);
		printf("Query %d: ", i);
		if (strcmp(s2, "is-a") == 0) {
			if (checkIsaStr(s1, s3))
				puts("true");
			else
				puts("false");
		}
		else {
			firsthasa = true;
			if (checkHasaStr(s1, s3))
				puts("true");
			else
				puts("false");
		}
	}
}
