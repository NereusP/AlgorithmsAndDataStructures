#include <iostream>

void bubblesort(int a[],unsigned int len);

int main(void)
{
	int AA[]={2,3,4,5,2,7,5,8,4,8,45,92,89,2,9};
	for(unsigned int i=0;i<sizeof(AA)/sizeof(int);i++)
	{
		std::cout<<AA[i]<<" ";
	}
	std::cout<<"\n";
	bubblesort(AA,sizeof(AA)/sizeof(int));
	for(unsigned int i=0;i<sizeof(AA)/sizeof(int);i++)
	{
		std::cout<<AA[i]<<" ";
	}
	std::cout<<"\n";
	return 0;
}

void bubblesort(int a[],unsigned int len)
{
	for(unsigned int i=0;i<len-1;i++)
	{
		for(unsigned int j=0;j<len-1-i;j++)
		{
			if(a[j+1]<a[j])
			{
				int temp=std::move(a[j+1]);
				a[j+1]=std::move(a[j]);
				a[j]=std::move(temp);
			}
		}
	}
}

