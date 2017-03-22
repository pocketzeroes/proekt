#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define dummy dp->head


typedef struct node
{
	int data;
	struct node *next;
	struct node *prev;
}node;
typedef struct deque
{
	int count;
	node *head;
}deque;
deque *createDeque(void)
{
	node *sentinel = malloc(sizeof(node));
	deque *dp = malloc(sizeof(deque));
	assert(dp != NULL && sentinel != NULL);
	sentinel -> prev = sentinel;
	sentinel -> next = sentinel;
	dummy = sentinel;
	dp -> count = 0;
	return dp;
}
void destroyDeque(deque *dp)
{
	node *temp, *prev;
	temp = prev = dummy -> next;
	while (temp != dummy)
	{
		temp = temp -> next;
		free(prev);
		prev = temp;
	}
	free(dummy);
	free(dp);
}
int numItems(deque *dp)
{
	assert(dp != NULL);
	return dp->count;
}
bool empty(deque *dp)
{
	assert(dp != NULL);
	return dp->count == 0;
}
void push_front(deque *dp, int x)
{
	assert(dp != NULL);
	dp -> count++;
	node *newNode = malloc(sizeof(node));
	newNode -> data = x;
	newNode -> next = dummy -> next;
	newNode -> prev = dummy;
	dummy -> next -> prev = newNode;
	dummy -> next = newNode;
}
void addLast(deque *dp, int x)
{
	assert(dp != NULL);
	dp -> count++;
	node *newNode = malloc(sizeof(node));
	newNode -> data = x;
	newNode -> prev = dummy -> prev;
	newNode -> next = dummy;
	dummy -> prev -> next = newNode;
	dummy -> prev = newNode;
}
int pop_front(deque *dp)
{
	assert(dp != NULL && dp -> count > 0);
	dp -> count--;
	node *temp = dummy -> next;
	dummy -> next = temp -> next;
	temp -> next -> prev = temp -> prev;
	int x = temp -> data;
	free(temp);
	return x;
}
int pop_back(deque *dp)
{
	assert(dp != NULL && dp -> count > 0);
	dp -> count--;
	node *temp = dummy -> prev;
	dummy -> prev = temp -> prev;
	temp -> prev -> next = temp -> next;
	int x = temp -> data;
	free(temp);
	return x;
}
int removePosition(deque *dp, int position)
{
	assert(dp != NULL);
	dp -> count--;
	int i;
	node *temp = dummy -> next;
	for(i = 0; i < position; i++)
	{
		temp = temp -> next;
	}
	temp -> prev -> next = temp -> next;
	temp -> next -> prev = temp -> prev;
	int x = temp -> data;
	free(temp);
	return x;
}
int front(deque *dp)
{
	assert(dp != NULL && dummy -> next != NULL);
	return dummy->next->data;
}
int back(deque *dp)
{
	assert(dp != NULL && dummy -> prev != NULL);
	return dummy -> prev -> data;
}
int getPosition(deque *dp, int position)
{
	assert(dp != NULL && position <= dp -> count);
	int i;
	node* temp = malloc(sizeof(node));
	temp = dummy -> next;
	for (i = 0; i < position; i++)
	{
		temp = temp -> next;
	}
	return temp -> data;
}
int search(deque *dp, int x)
{
	assert(dp != NULL && dp -> count != 0);
	int i = 0;
	int found = 0;
	int position = 0;
	node *temp = malloc(sizeof(node));
	temp = dummy -> next; 
	for (i = 0; i < dp -> count; i++)
	{
		if(temp -> data == x)
		{
			found = 1;
			printf("found %d!\n", x);
			break;
		}
		else
		{
			temp = temp -> next;
			position++;
		}
	}
	if (found == 1)
		return position;
	else
		return -1;
}
void printDeque(deque *dp)
{
	assert(dp != NULL && dp -> count != 0);
	int i = 0;
	node *temp = malloc(sizeof(node));
	temp = dummy -> next;
	for(i = 0; i < dp -> count; i++)
	{
		printf("\nnode %d: %d\n", i, temp -> data);
		temp = temp -> next;
	}
	printf("\ncount: %d\n", dp -> count);
	return;
}
void moveToFirst(deque *dp, int position)
{
	assert(dp != NULL && dp -> count >= position);
	int i = 0;
	node *temp = malloc(sizeof(node));
	temp = dummy -> next;
	for(i = 0; i < position; i++)
	{
		temp = temp -> next;
	}
	temp -> next -> prev = temp -> prev;
	temp -> prev -> next = temp -> next;
	temp -> next = dummy -> next;
	temp -> prev = dummy;
	dummy -> next -> prev = temp;
	dummy -> next = temp;	
	return;
};
void UpdateData(deque *dp, int position, int data)
{
	assert(dp != NULL);
	assert(dp -> count >= position);
	int i;
	node *temp = malloc(sizeof(node));
	temp = dummy -> next;
	for(i = 0; i < position; i++)
	{
		temp = temp -> next;
	}
	temp -> data = data;
	return;
}
int findMin(deque *dp)
{
	assert(dp != NULL);
	int min, i;
	int position = 0;
	node *temp = malloc(sizeof(node));
	temp = dummy -> next;
	min = temp -> data;
	temp = temp -> next;
	for(i = 1; i < dp -> count; i++)
	{
		if(temp -> data <= min)
		{
			position = i;
			min = temp -> data;
		}
	}
	return position;
}

////////////////


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


char* removeKdigits(char* num, int k){
    deque*dq=createDeque();
    int i = 0, cnt = 0;
    for (; num[i]; i++){
        while (!empty(dq) && num[i] < front(dq) && cnt < k) {
            pop_front(dq);
            cnt++;
        }
        if (cnt == k) break;
        push_front(dq,num[i]);
    }
    while (cnt++ < k && !empty(dq)) pop_front(dq);
    while (!empty(dq) && back(dq) == '0') pop_back(dq);
    while (empty(dq) && num[i] == '0') i++;
    char*ret=malloc(numItems(dq));
    int  retLen=0;
    while (!empty(dq)) {
        ret[retLen++] = back(dq);
        pop_back(dq);
    }
    ret[retLen]='\0';
    char*sub=substr(num, i, strlen(num) - i);
    char*buf;
    asprintf(&buf,"%s%s", ret, sub);
    return strlen(buf)>0 ? buf : "0";
}


















