#include "syscall.h"
#include "copyright.h"

#define maxlen 32

int main(void)
{
	char filename[maxlen + 1];
	int test = -1;
	PrintString("Input file name to create:\n");
	ReadString(filename, maxlen);
	if (test = CreateFile(filename) == -1)
		PrintString("\nCreate failed...");
	else if (test == 0)
		PrintString("\nCreate succeeded...");
	Halt();
	return 4;
}
