#include <stdio.h>
#include <utility>

void binary_insertsort(int aa[],unsigned int len);
void printf_array(int aa[],unsigned int len);

int main(void)
{
	int AA[]={6,9,8,63,56,7,12,4,0,9};
	printf("Before sort:\n");
	printf_array(AA,sizeof(AA)/sizeof(int));
	binary_insertsort(AA,sizeof(AA)/sizeof(int));
	printf("After sort:\n");
	printf_array(AA,sizeof(AA)/sizeof(int));
	return 0;
}

void binary_insertsort(int aa[],unsigned int len)
{
	int low=0,high=0,mid=0;
	for(unsigned int i=1;i<len;i++)
	{
		low=0;
		high=i-1;
		int tmp=std::move(aa[i]);
		while(low<=high)
		{
			mid=(low+high)>>1;
			if(tmp<aa[mid])
			{
				high=mid-1;
			}
			else
			{
				low=mid+1;
			}
		}
		for(int j=i;j>low;j--)
		{
			aa[j]=std::move(aa[j-1]);
		}
		aa[low]=std::move(tmp);
		printf("turn %d:\n",i);
		printf_array(aa,len);
	}
}

void printf_array(int aa[],unsigned int len)
{
	for(unsigned int i=0;i<len;i++)
	{
		printf("%d ",aa[i]);
	}
	printf("\n");
}

