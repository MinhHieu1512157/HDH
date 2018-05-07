#include "syscall.h"
#include "copyright.h"

#define MAX_LEN_STR 255
#define MAX_SIZE_BUFF 256

int main(void)
{
	char filename[MAX_LEN_STR + 1];
	char buff[MAX_SIZE_BUFF];
	OpenFileID openFileID = -1;
	OpenFileID consoleOutputID = -1;
	int numBytes = 0;
	
	PrintString("Input file name to read:\n");
	ReadString(filename, MAX_LEN_STR);
	openFileID = Open(filename, 1);
	consoleOutputID = Open("stdout", 0);
	if (openFileID < 0 || consoleOutputID < 0)
	{
		Halt();
		return;
	}
	
	while (numBytes = Read(buff, MAX_SIZE_BUFF, openFileID))
	{
		Write(buff, numBytes, consoleOutputID);
	}
	Close(openFileID);
	Close(consoleOutputID);		

	Halt();	
	return 0;
}
