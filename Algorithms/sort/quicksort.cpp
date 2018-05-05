#include <stdio.h>
#include <utility>

void quicksort(int aa[],int left,int right);
void printf_array(int aa[],unsigned int len);

int main(void)
{
	int AA[]={9,8,1,6,3,0,5,4,1,3,2,11,4,12,5};
	printf("Before sort:\n");
	printf_array(AA,sizeof(AA)/sizeof(int));
	quicksort(AA,0,sizeof(AA)/sizeof(int)-1);
	printf("After sort:\n");
	printf_array(AA,sizeof(AA)/sizeof(int));
	return 0;
}

void quicksort(int aa[],int left,int right)
{
	int i=left,j=right;
	int pivot=aa[left];//For convenience, use the first number as a reference
	if(i>=j)
	{
		//If i=j, there is only one number in the sequence and no longer needs to be sorted
		return;
	}
	while(i<j)
	{
		while((j>i)&&(aa[j]>=pivot))
		{
			j--;//Find a number less than the reference from the rightmost
		}
		while((i<j)&&(aa[i]<=pivot))
		{
			i++;//Find a number greater than the base from the leftmost
		}
		if(i!=j)
		{
			//If i!=j, then swap
			int tmp=std::move(aa[i]);
			aa[i]=std::move(aa[j]);
			aa[j]=std::move(tmp);
		}
		else
		{
			//Otherwise, exchange the number of positions i with the reference
			int tmp=std::move(aa[i]);
			aa[i]=std::move(aa[left]);
			aa[left]=std::move(tmp);
		}
		/*
		Continually swapping the number greater than the base on the right with the number less than the base on the left
		*/
	}
	//At the end of the loop, there must be i=j
	//recursive
	quicksort(aa,left,i-1);//Do the same thing with a subsequence that is less than the datum
	quicksort(aa,i+1,right);//Do the same thing with a subsequence that is greater than the datum
}

void printf_array(int aa[],unsigned int len)
{
	for(unsigned int i=0;i<len;i++)
	{
		printf("%d ",aa[i]);
	}
	printf("\n");
}

