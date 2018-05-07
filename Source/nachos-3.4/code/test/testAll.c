#include "syscall.h"
#include "copyright.h"

#define maxlen 32

int strlen(char * str);
int strlen(char * str)
{
	int i;
	if ((int)str == 0)
		return 0;
	i = 0; 
	while (str[i] != '\0')
		i++;
	return i;
}

void PrintRes(int res);
void PrintRes(int res)
{
	PrintInt(res);
	PrintChar('\n');
}

int main()
{
	int choose = 0;	
	int len, a;
	char ch;
	char filename[maxlen +1];
	char str[256];
	OpenFileId openFileID = -2;
	int type = 3;
	int numBytes = 0;
	int res = -7;
	int pos = -2;
	
	loop_all:
	PrintString("\n---------------------\n0.File mangement\n1.ReadInt\n2.ReadChar\n3.ReadString\n4.Multiprog\n");
	choose = ReadInt();
	switch(choose) {
		case 0:	
			loop_file_mng:
			PrintString("\n---------------------\n0.CreateFile\n1.OpenFile\n2.CloseFile\n3.ReadFile\n4.WriteFile\n5.Seek\n");
			choose = ReadInt();
			switch(choose)
			{
				case 0:
					ReadString(filename, maxlen);
					res = CreateFile(filename);
					PrintRes(res);
					break;
				case 1:
					ReadString(str, 255);
					type = ReadInt();
					openFileID = Open(str, type);
					PrintRes(openFileID);
					break;
				case 2:
					openFileID = ReadInt();
					res = Close(openFileID);
					PrintRes(res);
					break;
				case 3:
					openFileID = ReadInt();
					numBytes = Read((char*)str, 255, openFileID);
					PrintInt(numBytes);
					PrintChar('\n');
					str[numBytes] = '\0';
					PrintString(str);
					break;
				case 4:
					openFileID = ReadInt();
					ReadString(str, 256);
					len = strlen(str);
					numBytes = Write(str, len, openFileID);				
					PrintInt(numBytes);
					PrintChar('\n');					
					break;
				case 5:
					openFileID = ReadInt();
					pos = ReadInt();
					res = Seek(pos, openFileID);
					PrintRes(res);					
					break;
				case -1:
					goto loop_all;
				default:
					goto loop_file_mng;
					break;
			}
			goto loop_file_mng;
			break;
		case 1:	
			a = ReadInt();
			PrintInt(a);
			break;
		case 2:
			ch = ReadChar();
			PrintChar(ch);
			break;
		case 3:			
			ReadString(str, 255);
			PrintString(str);
			break;
		case 4:
			Exec("./test/multiprog1");
			break;
		case -1:
			PrintString("Finish program.");
			Halt();
			return 0;
		default:
			break;
	}
	goto loop_all;
}
