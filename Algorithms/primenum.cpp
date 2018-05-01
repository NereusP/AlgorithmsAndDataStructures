#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

void shellsort(int a[],unsigned int len);
unsigned int primenum(int prm[],unsigned int n);//产生素数(质数)

int main(void)
{
	int aa[]={32,64,36,53,47,65,83,96,586,4,39,3,7,0,4,3,9,7,6,3,1,0,6,13,8,60,6,18};
	shellsort(aa,sizeof(aa)/sizeof(int));
	for(unsigned int i=0;i<sizeof(aa)/sizeof(int);i++)
	{
		std::cout<<aa[i]<<" ";
	}
	std::cout<<std::endl;
	std::cout<<"Prime number:\n";
	primenum(20);
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

unsigned int primenum(int prm[],unsigned int n)
{
	for(unsigned int i=0;i<n;i++)
	{
		prm[i]=(3*i+1+sin(i*M_PI/2)*sin(i*M_PI/2));
	}
}

