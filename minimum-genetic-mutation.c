#define DNASize 9
struct Node{
	char string[DNASize];
	struct Node *link;
}*top;

int minMutation(char* start, char* end, char** bank, int bankSize)
{
    int i,j,diff,mutation=0,split=0,total_split=1;    
    initiate_queue();
    add_to_queue(start);
    struct Node *node = top->link;
    while(node!=NULL)
    {
    	for(i=0;i<bankSize;i++)
    	{
    		diff = 0;
    		for(j=0;j<DNASize;j++)
			{
				if(node->string[j] != bank[i][j])
					diff++;
			}
			if(diff==1)
			{
				add_to_queue(bank[i]);
				split++;
				strcpy(bank[i],"QQQQQQQQ");
			}
			else if(diff==0)
				strcpy(bank[i],"QQQQQQQQ");
		}
		node = node->link;
		delete_queue();
		total_split--;
		if(total_split==0)
		{
			mutation++;
			total_split=split;
			split=0;
		}
		if( parse_queue(end)==1) 
			return mutation;
	}
	free(top);
	return -1;
}
void initiate_queue()
{
	top = (struct Node*)malloc(sizeof(struct Node));
	if(top==NULL)
	{
		printf("Out of memory\n");
		return;
	}
	top->link = NULL;
}
void add_to_queue(char * DNA)
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node)),*ptr=top;
	if(node==NULL)
	{
		printf("Out of memory\n");
		return;
	}
	strcpy(node->string,DNA);
	node->link = NULL;
	while(ptr->link!=NULL)
	{
		ptr = ptr->link;
	}
	ptr->link= node;
}
void delete_queue(void)
{
	struct Node *ptr = top->link;
	top->link = ptr->link;
	free(ptr);
}
int parse_queue(char * end)
{
	struct Node *node = top->link;
	while(node!=NULL)
	{
		if(strcmp(end,node->string)==0)   
			return 1;
		node = node->link;
	}
	return 0;
}




































