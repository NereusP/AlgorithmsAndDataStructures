#include <stdio.h>
#include <utility>

void cocktailsort(int a[],unsigned int len);
void printf_array(int aa[],unsigned int len);

int main(void)
{
	int aa[]={6,9,7,5,3,3,6,1};
	printf("Before sort:\n");
	printf_array(aa,sizeof(aa)/sizeof(int));
	cocktailsort(aa,sizeof(aa)/sizeof(int));
	printf("After sort:\n");
	printf_array(aa,sizeof(aa)/sizeof(int));
	return 0;
}

void cocktailsort(int a[],unsigned int len)
{
	unsigned int left=0,right=len-1;
	while(left<right)
	{
		for(unsigned int i=left;i<right;i++)
		{
			if(a[i]>a[i+1])
			{
				int tmp=std::move(a[i+1]);
				a[i+1]=std::move(a[i]);
				a[i]=std::move(tmp);
			}
		}
		printf_array(a,len);
		right--;
		for(unsigned int i=right;i>left;i--)
		{
			if(a[i-1]>a[i])
			{
				int tmp=std::move(a[i-1]);
				a[i-1]=std::move(a[i]);
				a[i]=std::move(tmp);
			}
		}
		left++;
		printf_array(a,len);
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

