#include "syscall.h"
#include "copyright.h"

#define MAX_LEN_STR 255

int main(void)
{
	char str[MAX_LEN_STR + 1];
	OpenFileID openFileID = -1;
	int numBytes = 0;
	do
	{
		PrintString("\nType your sentence on screen or press enter to exit:\n");
		openFileID = Open("stdin", 1); // mo console de doc va ghi
		numBytes = Read(str, MAX_LEN_STR, openFileID);
		Close(openFileID);
		openFileID = Open("stdout", 0);
		Write(str, numBytes, openFileID);
		Close(openFileID);
	} while (numBytes > 0);
	Halt();	
	return 0;
}
