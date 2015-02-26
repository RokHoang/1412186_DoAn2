#include	<stdio.h>
#include	<stdlib.h>
#include	<conio.h>
#include	"1412186_DoAn2.h"
int main()
{
	int		stt,ketqua;
	int		ask=10;
	do
	{
		system("cls");
		printf("********** DO AN 2 - 1412186 **********\n");
		printf("**1. Tinh so Fibonaci			     **\n");
		printf("**2. Tinh toan so lon			     **\n");
		printf("***************************************\n\n");
		printf("Hay chon chuong trinh ban muon su dung: (1,2)\n");
		scanf("%i",&stt);
		fflush(stdin);
		switch(stt)
		{
			case 1: calFib();		break;
			case 2: calBigNum();	break;
		}
		printf("\n\n---------------------------------------\n\n");
		fflush(stdin);
		do
		{
		printf("Ban co muon tiep tuc su dung chuong trinh khong ? (y/n) \n");
		ask=getch();
		}	while ((ask!=89) && (ask!=121) && (ask!=78) && (ask!=110));
	}	while ((ask==89) || (ask==121));
	return 0;
}
