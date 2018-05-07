#include "syscall.h"
#include "copyright.h"

int main(void)
{
	int i = 0, j = 0;
	int n = 0;
	int a[100];
	
	n = ReadInt();
	if (n < 1 || n > 100) // sai kich thuoc
	{
		return 1;
	}
	
	// nhap
	for (i = 0; i < n; i++) {a[i] = ReadInt();}

	for (i = 0; i < n; i++)	
	{
		PrintInt(a[i]);
		PrintString(" ");
	}
	PrintString("\n");
	
	//bubble sort	
	for (i = 0; i < n; i++)
	{
		for (j = n - 1; j > i; j--)
		{
			if (a[j] < a[j - 1])
			{
				int tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
			}
		}
	}
	
	// xuat mang
	for (i = 0; i < n; i++)	
	{
		PrintInt(a[i]);
		PrintString(" ");
	}
	
	Halt();
	return 0;
}
