#include <stdio.h>
#include <utility>

void shellsort(int a[],unsigned int len);
void printf_array(int aa[],unsigned int len);

int main(void)
{
	int aa[]={32,64,36,53,47,65,83,96,586,4,39,3,7,0,4,3,9,7,6,3,1,0,6,13,8,60,6,18};
	printf("Before sort:\n");
	printf_array(aa,sizeof(aa)/sizeof(int));
	shellsort(aa,sizeof(aa)/sizeof(int));
	printf("After sort:\n");
	printf_array(aa,sizeof(aa)/sizeof(int));
	return 0;
}

void shellsort(int a[],unsigned int len)
{
	for(unsigned int gap=len/2;gap>0;gap=gap/2)
	{
		for(unsigned int i=gap;i<len;i++)
		{
			int tmp=std::move(a[i]);
			unsigned int j=i;
			for(;j>=gap&&tmp<a[j-gap];j-=gap)
			{
				a[j]=std::move(a[j-gap]);
			}
			a[j]=std::move(tmp);
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

