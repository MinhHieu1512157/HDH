#include "syscall.h"
#include "copyright.h"

int main(void)
{
	int ch = 0;
	for (ch = 0; ch < 256; ch++)
	{
		PrintInt(ch);
		PrintString("\t");
		PrintChar(ch);
		PrintString("\n");	
	}
	Halt();
	return 0;
}
