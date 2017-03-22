#define PRIME 5393
struct HashMap{
	long int dis;
	int number;
	struct HashMap *link;
}DistanceMap[PRIME];
long distance(int *a,int *b)
{
	return (int)pow(a[0]-b[0],2)+(int)pow(a[1]-b[1],2);
}
int numberOfBoomerangs(int** points, int pointsRowSize, int pointsColSize) {
    int i,j,k,count=0;
    for(i=0;i<pointsRowSize;i++)
    {
    	for(k=0;k<PRIME;k++)  
    	{
    		DistanceMap[k].dis = 0;
    		DistanceMap[k].number = 0;
    		DistanceMap[k].link = NULL;
        }
        for(j=0;j<pointsRowSize;j++)
        {
                if(j==i)
                    continue;
            add_to_map(distance(points[i],points[j]),DistanceMap);
        }
        for(k=0;k<PRIME;k++)
        {
            if(DistanceMap[k].number>=2)
                count+=DistanceMap[k].number*(DistanceMap[k].number-1);
            struct HashMap *ptr = &DistanceMap[k];
            while(ptr->link!=NULL)
            {
                ptr = ptr->link;
                if(ptr->number>=2)
                {
                    count+=ptr->number*(ptr->number-1);
                }
            }
        }
	}
	return count;
}
int hash(int val)
{
	return abs(val%PRIME);
}
void add_to_map(long dis,struct HashMap* DistanceMap)
{
	int hashValue = hash(dis);
	if(DistanceMap[hashValue].dis==0) 
	{
		DistanceMap[hashValue].dis = dis;
		DistanceMap[hashValue].number = 1;
	}
	else   
	{
		if(DistanceMap[hashValue].dis == dis)    
			DistanceMap[hashValue].number++;
		else  
		{
			struct HashMap *prev = &DistanceMap[hashValue],*current = prev->link;
			while(1)
			{
				if(current == NULL)
				{
					struct HashMap *ptr = (struct HashMap*)malloc(sizeof(struct HashMap));
					ptr->dis = dis;
					ptr->number = 1;
					ptr->link = NULL; 
					prev->link = ptr;
					break;
				}
				else if(current != NULL && current->dis == dis)
				{
					current->number++;
					break;
				}
				else
				{
					current = current->link;
					prev = prev->link;
				}
			}
		}
	}
}


















































