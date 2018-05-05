#include <stdio.h>
#include <utility>

void insertsort(int aa[],unsigned int len);
void printf_array(int aa[],unsigned int len);

int main(void)
{
	int aa[]={47,32,65,37,94,65,83,48,56,83,48,65,46,54,86};
	printf("before sort:\n");
	printf_array(aa,sizeof(aa)/sizeof(int));
	insertsort(aa,sizeof(aa)/sizeof(int));
	printf("after sort:\n");
	printf_array(aa,sizeof(aa)/sizeof(int));
	return 0;
}

void insertsort(int aa[],unsigned int len)
{
	for(unsigned int i=1;i<len;i++)
	{
		//Ordered array length gradually increases from 1
		int temp=std::move(aa[i]);//The last number of an ordered array
		unsigned int j=i;
		for(;j>0&&temp<aa[j-1];j--)
		{
			aa[j]=std::move(aa[j-1]);//Move the element in an inappropriate position backward
		}
		aa[j]=std::move(temp);//Insert into this position
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


