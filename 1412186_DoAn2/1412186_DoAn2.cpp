#include	<stdio.h>
#include	<string.h>
#include	"1412186_DoAn2.h"
void	input1(bigNum *a,bigNum *b,char *toantu)
{
	char x[10000];
	char *vitri;
	printf("Hay nhap phep tinh cua ban: (cach nhau 1 khoang trang) \n");
	gets(x);
	vitri=strtok(x," ");
	
	if (*vitri=='-')	//so hang 1
	{	
		(*a).dau=-1;
		vitri++;
	}
	else
		(*a).dau=1;
	strcpy((*a).digit,vitri);
	
	vitri=strtok(NULL," ");//toan tu
	*toantu=*vitri;

	vitri=strtok(NULL," ");//sohang2
	if (*vitri=='-')
	{	
		(*b).dau=-1;
		vitri++;
	}
	else
		(*b).dau=1;
	strcpy((*b).digit,vitri);
}
void	input2(long *n)
{
	printf("Hay nhap vi tri so Fibonaci: ");
	scanf("%ld",&*n);
}
void	add0(bigNum *a,bigNum *b)
{
	char tam[10000];
	while (strlen((*a).digit)<strlen((*b).digit))
	{
		strcpy(tam,(*a).digit);
		strcpy((*a).digit+1,tam);
		(*a).digit[0]='0';
	}
	while (strlen((*b).digit)<strlen((*a).digit))
	{
		strcpy(tam,(*b).digit);
		strcpy((*b).digit+1,tam);
		(*b).digit[0]='0';
	}
}
int		cmpBigNum(bigNum a,bigNum b)
{
	long i;
	add0(&a,&b);
	for (i=0;i<=(strlen(a.digit));i++)
	{	
		if (a.digit[i]>b.digit[i])
			return 1;
		if (a.digit[i]<b.digit[i])
			return -1;
	}
	return 0;
}
bigNum	addBigNum(bigNum a,bigNum b)
{
	int x,y;
	long i;
	int memory=0;
	int sum;
	char tam[10000];
	bigNum c={1,0};//gan ki tu ket thuc cho c//c.digit[strlen(a.digit)]=0;
	add0(&a,&b);

	for (i=strlen(a.digit)-1;i>=0;i--)
	{
		x=a.digit[i]-'0';
		y=b.digit[i]-'0';
		sum=memory+x+y;
		memory=sum/10;
		sum=sum%10;
		c.digit[i]=sum+'0';
	}
	if (memory==1)
	{
		strcpy(tam,c.digit);
		strcpy(c.digit+1,tam);
		c.digit[0]='1';
	}
	return c;
}
bigNum	subBigNum(bigNum a,bigNum b)
{
	int x,y;
	long i;
	int memory=0;
	int sub;
	bigNum c,tam;
	if (cmpBigNum(a,b)==(-1))
	{
		tam=a;a=b;b=tam;
		c.dau=-1;			//dau cua ket qua
	}
	add0(&a,&b);
	c.digit[strlen(a.digit)]=0;
	for (i=strlen(a.digit)-1;i>=0;i--)
	{
		x=a.digit[i]-'0'; 
		y=b.digit[i]-'0';
		if ((x-memory)<y)
		{	
			x+=10;
			memory=1;
		}
		else 
		{	
			x=x-memory;
			memory=0;
		}
		sub=x-y;
		c.digit[i]=sub+'0';
	}
	return c;
}
bigNum	mutil(bigNum a,int x)
{
	long i;
	int memory=0;
	int k;
	bigNum c;
	c.digit[strlen(a.digit)]=0;
	for (i=strlen(a.digit)-1;i>=0;i--)
	{
		k=(a.digit[i]-'0')*x+memory;
		memory=k/10;
		c.digit[i]=k%10+'0';
	}
	if (memory>0)
	{
		strcpy(c.digit+1,c.digit);
		c.digit[0]=memory+'0';
	}
	return c;
}
bigNum	mutilBigNum(bigNum a,bigNum b)
{
	bigNum c,thuaso;
	int x;
	long i,j;
	strcpy(c.digit,"0");
	for (i=strlen(b.digit)-1;i>=0;i--)
	{
		x=b.digit[i]-'0';
		thuaso=mutil(a,x);
		for (j=strlen(b.digit)-1-i;j!=0;j--)//nhan voi 10 mu x
			strcat(thuaso.digit,"0");
		c=addBigNum(thuaso,c);
	}
	return c;
}
bigNum	divBigNum(bigNum a,bigNum b)
{
	bigNum c;
	bigNum one;
	strcpy(one.digit,"1");
	strcpy(c.digit,"0");
	if (cmpBigNum(a,b)==-1)
	{	
		strcpy(c.digit,"0");
		c.digit[1]=0;
		return c;
	}
	do
	{
		a=subBigNum(a,b);
		c=addBigNum(c,one);
	}	while (cmpBigNum(a,b)!=(-1));
	return c;
}
bigNum	fibBigNum(long n)
{
	bigNum fib;
	bigNum fib1,fib2;
	long i;
	strcpy(fib1.digit,"1");
	strcpy(fib2.digit,"0");
	for(i=1;i<=n;i++)
	{
		fib=addBigNum(fib1,fib2);
		fib1=fib2;
		fib2=fib;
	}
	return fib;
}
bigNum	control(bigNum a,bigNum b,char toantu)
{
	bigNum c;
	switch(toantu)
	{
	case '*':	
		c=mutilBigNum(a,b);
		if(a.dau==b.dau) 
			c.dau=1;
		else
			c.dau=-1;
		break;
	case '/':
		c=divBigNum(a,b);
		if(a.dau==b.dau)
			c.dau=1;
		else
			c.dau=-1;
		break;
	case '+':
		if (a.dau==b.dau) 
		{	
			c=addBigNum(a,b);
			c.dau=a.dau;
		}
		else
		{	
			if (a.dau==1)
				c=subBigNum(a,b);
			else
				c=subBigNum(b,a);
		}
		break;
	case '-':
		if (a.dau==b.dau) 
		{	
			c=subBigNum(a,b);
			c.dau*=a.dau;
		}
		else//
		{	
			if (a.dau==1)
				c=addBigNum(a,b);
			else
			{
				c=addBigNum(b,a);
				c.dau=-1;
			}
		}
		break;
	}
	return c;
}
void	calBigNum()
{
	bigNum a;
	bigNum b;
	bigNum c;
	bigNum zero;
	strcpy(zero.digit,"0");
	char toantu;
	input1(&a,&b,&toantu);
	c=control(a,b,toantu);
	if (cmpBigNum(c,zero)==0)
		printf("=0");
	else 
	{	
		if (c.dau==(-1))
			printf("=-%s",c.digit);
		else
			printf("=%s",c.digit);
	}
}
void	calFib()
{
	long n;
	input2(&n);
	printf("So fibonaci thu %ld la %s",n,fibBigNum(n).digit);
}