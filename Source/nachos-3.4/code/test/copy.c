#include "syscall.h"
#include "copyright.h"

#define MAX_LEN_STR 255
#define MAX_SIZE_BUFF 256

int main(void)
{
	char sFileName[MAX_LEN_STR + 1];
	char dFileName[MAX_LEN_STR + 1];
	char buff[MAX_SIZE_BUFF];
	OpenFileID sFileID = -1;
	OpenFileID dFileID = -1;
	int numBytes = 0;
	
	PrintString("Copy file from source file to dest file.\n");
	PrintString("- Input source file name:\n");
	ReadString(sFileName, MAX_LEN_STR);
	PrintString("- Input dest file name:\n");	
	ReadString(dFileName, MAX_LEN_STR);

	sFileID = Open(sFileName, 1);
	dFileID = Open(dFileName, 0);	

	if (sFileID < 0) { Halt(); return;}
	if (dFileID < 0)
	{
		CreateFile(dFileName);
		dFileID = Open(dFileName, 0);
		if (dFileID < 0) { Halt(); return;}
	}
	
	while (numBytes = Read(buff, MAX_SIZE_BUFF, sFileID))
	{
		Write(buff, numBytes, dFileID);
	}
	Close(sFileID);
	Close(dFileID);

	Halt();	
	return 0;
}
