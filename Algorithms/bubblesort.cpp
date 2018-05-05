#include <stdio.h>
#include <utility>

void bubblesort(int a[],unsigned int len);
void printf_array(int aa[],unsigned int len);

int main(void)
{
	int AA[]={2,3,4,5,2,7,5,8,4,8,45,92,89,2,9};
	printf("before sort:\n");
	printf_array(AA,sizeof(AA)/sizeof(int));
	bubblesort(AA,sizeof(AA)/sizeof(int));
	printf("after sort:\n");
	printf_array(AA,sizeof(AA)/sizeof(int));
	return 0;
}

void bubblesort(int a[],unsigned int len)
{
	bool bswap=false;
	for(unsigned int i=0;i<len-1;i++)
	{
		bswap=false;
		for(unsigned int j=0;j<len-1-i;j++)
		{
			if(a[j+1]<a[j])
			{
				int temp=std::move(a[j+1]);
				a[j+1]=std::move(a[j]);
				a[j]=std::move(temp);
				bswap=true;
			}
			printf("turn %d-%d:\n",i,j);
			printf_array(a,len);
		}
		if(!bswap)
		{
			//If no exchange occurs in one round, the sorting is completed
			break;
		}
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
