#include <iostream>

void insertsort(int aa[],unsigned int len);

int main(void)
{
	int aa[]={47,32,65,37,94,65,83,48,56,83,48,65,46,54,86};
	std::cout<<"before sort:\n";
	for(unsigned int i=0;i<sizeof(aa)/sizeof(int);i++)
	{
		std::cout<<aa[i]<<" ";
	}
	insertsort(aa,sizeof(aa)/sizeof(int));
	std::cout<<"\nafter sort:\n";
	for(unsigned int i=0;i<sizeof(aa)/sizeof(int);i++)
	{
		std::cout<<aa[i]<<" ";
	}
	std::cout<<"\n";
	return 0;
}

void insertsort(int aa[],unsigned int len)
{
	for(unsigned int i=1;i<len;i++)
	{
		int temp=std::move(aa[i]);
		unsigned int j=i;
		for(;j>0&&temp<aa[j-1];j--)
		{
			aa[j]=std::move(aa[j-1]);
		}
		aa[j]=std::move(temp);
	}
}

