#include "syscall.h"
#include "copyright.h"

#define MAX_LEN_STR 255

int main(void)
{
	char sFileName[MAX_LEN_STR + 1];
	char dFileName[MAX_LEN_STR + 1];
	OpenFileID sFileID = -1;
	OpenFileID dFileID = -1;
	int numBytes = 0;
	int back = 0;
	int curPos = -1;
	char ch;
	
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
		if (CreateFile(dFileName) < 0) {Halt(); return;}
		dFileID = Open(dFileName, 0);
		if (dFileID < 0) { Halt(); return;}
	}
	
	// dich toi cuoi file
	curPos = Seek(-1, sFileID);
	// lui lai bo qua ky tu ket file
	curPos -= 1;
	do
	{
		curPos = Seek(curPos, sFileID);
		Read(&ch, 1, sFileID);
		Write(&ch, 1, dFileID);
		curPos--;
		
	} while (curPos >= 0);
	Close(sFileID);
	Close(dFileID);	

	Halt();	
	return 0;
}
