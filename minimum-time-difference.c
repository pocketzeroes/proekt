
int diff(int a, int b)
{
	int c = abs(a - b);
	if (c > 720)
	{
		c = 1440 - c;
	}
	return c;
}

void sort(int *nums, int size)
{
	int temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (nums[i] > nums[j])
			{
				temp = nums[i];
				nums[i] = nums[j];
				nums[j] = temp;
			}
		}
	}
}


int findMinDifference(char** timePoints, int timePointsSize)
{
	int *timeArray = malloc(sizeof(int)*timePointsSize);
	int time;
	int hour;
	int min;
	for (int i = 0; i < timePointsSize; i++)
	{
		hour = 10 * (timePoints[i][0] - '0') + (timePoints[i][1] - '0');
		min = 10 * (timePoints[i][3] - '0') + (timePoints[i][4] - '0');
		time = hour * 60 + min;
		timeArray[i] = time;
	}
	sort(timeArray, timePointsSize);
	int minDiff = diff(timeArray[0], timeArray[timePointsSize - 1]);
	int tempDiff;
	for (int i = 1; i < timePointsSize; i++)
	{
		tempDiff = diff(timeArray[i], timeArray[i - 1]);
		minDiff  = (minDiff<tempDiff)?minDiff:tempDiff;
	}
	return minDiff;
}





