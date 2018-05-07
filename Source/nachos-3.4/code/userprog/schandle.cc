#include "schandle.h"

int strlen(char * buff)
{
	if (buff == NULL) {return 0;}
	int i = 0;
	for (i = 0; buff[i] != NULL; i++) 
		;
	return i;	
}

int strToInt(char * buff, int len)
{
	/*if (buff == NULL || len < 1)
	{
		de hdh tu bao loi, vi can thiep se khong biet
		tra ve gia tri nao cho phu hop
		neu can thi xu ly bang try catch de bat exception
		
		Mac khac cung khong can kiem tra buoc nay vi kiem tra hop le
		trong ham testBuff truoc khi goi ham nay
	} */
		
	int res = 0;
	int sign = (buff[0] == '-') * (-1) + ('0' <= buff[0] && buff[0] <= '9'); // am: -1, duong: 1
	
	int firstDigit = (int) sign == -1; // index of first digital
	int scale = 1;
	int i = 0;
	
	for (i = len - 1; i >= firstDigit; i--)
	{
		res += (buff[i] - '0') * scale;
		scale *= 10;
	}
	return res * sign;
}

bool testBuffReadInt(char * buff, int len)
{
	if (buff == NULL || len < 1)	{ return false; }
	int sign = 0;
	if (buff[0] == '-') {sign = 1;}
	int i = 0;	
	for (i = sign; i < len; i++)
	{
		if (buff[i] < '0' || buff[i] > '9') {return false;}
	}
	return true;	
}

char * IntToStr(int a)
{
	char * buff = new char[MAX_LEN_INT];
	if (buff == NULL) // thieu bo nho
	{
		return NULL;
	}
	
	if (a == 0)
	{
		buff[0] = '0';
		buff[1] = NULL;
		return buff;
	}
	
	bool sign = a < 0;
	if (sign) { a = -a; buff[0] = '-';}
	int i = (int) sign;
	
	while (a > 0)
	{
		char digit = (char) (a % 10) + '0';
		buff[i++] = digit;
		a /= 10;
	}
	
	int l = (int) sign, r = i - 1;
	while (l < r)
	{
		char tmp = buff[l];
		buff[l] = buff[r];
		buff[r] = tmp;
		
		l++; r--;
	}
	buff[i]	 = NULL;
	return buff;
}

int System2User(int virtAddr,int len,char* buffer)
{
	if (len < 0) return -1;
	if (len == 0)return len;
	int i = 0;
	int oneChar = 0 ;
	do{
		oneChar= (int) buffer[i];
		machine->WriteMem(virtAddr+i,1,oneChar);
		i ++;
	}while(i < len && oneChar != 0);
	return i;
}

char* User2System(int virtAddr,int limit)
{
	int i;// index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit +1];//need for terminal string
	if (kernelBuf == NULL)
	return kernelBuf;
	memset(kernelBuf,0,limit+1);
	//printf("\n Filename u2s:");
	for (i = 0 ; i < limit ;i++)
	{
		machine->ReadMem(virtAddr+i,1,&oneChar);
		kernelBuf[i] = (char)oneChar;
		//printf("%c",kernelBuf[i]);
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

void increaseProgramCounter()
{
	// tang thanh ghi chi lenh PC: prev = current, current = next, next += 4
	machine->registers[PrevPCReg] = machine->registers[PCReg];
	machine->registers[PCReg] = machine->registers[NextPCReg];
	machine->registers[NextPCReg] += 4;
}

void SystemCall(int type) {
	switch (type) {
		case SC_Halt :
			Halt_SystemCall();
			break;			
		case SC_Exit :
			Exit_SystemCall();
			break;
		case SC_Create :
			Create_SystemCall();
			break;
		case SC_Open :
			Open_SystemCall();
			break;
		case SC_Read :
			Read_SystemCall();
			break;
		case SC_Write : 
			Write_SystemCall();
			break;
		case SC_Close :
			Close_SystemCall();
			break;
		case SC_Exec :
			Exec_SystemCall();
			break;
		case SC_Join :
			Join_SystemCall();
			break;
		case SC_ReadInt:
			ReadInt_SystemCall();
			break;
		case SC_PrintInt:
			PrintInt_SystemCall();
			break;
		case SC_ReadChar:
			ReadChar_SystemCall();
			break;
		case SC_PrintChar:
			PrintChar_SystemCall();
			break;
		case SC_ReadString:
			ReadString_SystemCall();
			break;
		case SC_PrintString:
			PrintString_SystemCall();
			break;	
		case SC_Seek:
			Seek_SystemCall();
			break;
		case SC_CreateSemaphore:
			CreateSemaphore_SystemCall();
			break;
		case SC_Signal:
			Signal_SystemCall();
			break;
		case SC_Wait:
			Wait_SystemCall();
			break;
		case SC_SetMsg:
			SetMsg_SystemCall();
			break;
		case SC_GetMsg:
			GetMsg_SystemCall();
			break;
		case SC_IsEmptyMsg:
			IsEmptyMsg_SystemCall();
			break;
		default:
			break;			
	}
}

void Halt_SystemCall()
{
	DEBUG('a', "\n Shutdown, initiated by user program.");
	printf ("\n\nShutdown, initiated by user program.\n");
	interrupt->Halt();	// halt lai he thong tra quyen cho hdh
}

void Exit_SystemCall()
{
	int exitStatus = 0;
    exitStatus = machine->ReadRegister(4);

    // Check if process exited with error, print error
	if (exitStatus != 0){
        printf("\nExit:: Process %s exited with error level %d.\n",currentThread->getName(),exitStatus);
    }

    int res = pTab->ExitUpdate(exitStatus);
	currentThread->FreeSpace();
	currentThread->Finish();
	machine->WriteRegister(2,res);
}

void Create_SystemCall()
{
	int virtAddr;
	char* filename = NULL;
	
	// Lấy tham số tên tập tin từ thanh ghi r4
	virtAddr = machine->ReadRegister(4);
	
	// MaxFileLength là = 32
	filename = User2System(virtAddr, MAX_FILE_LENGTH + 1);
	if (filename == NULL)
	{
		DEBUG('a', "\n Not enough memory in system");
		// trả về lỗi cho chương trình người dùng
		machine->WriteRegister(2,-1); 
				return;
	}
	
	// tao file bi loi
	if (!fileSystem->Create(filename, 0))
	{
		DEBUG('a', "\n Error create file '%s'",filename);
		// trả về lỗi cho chương trình người dùng
		machine->WriteRegister(2,-1);
				delete filename;
		return;
	}
	
	// trả về cho chương trình người dùng thành công
	machine->WriteRegister(2,0); 
		delete filename;
}

void Open_SystemCall()
{
	int virtAddr = 0; // dia chi ten file trong user space
	int type = 0; // kieu mo file: 0 = doc-ghi, 1 = chi doc
	int openFileID = -1;
	char * filename = NULL;
	OpenFile* of = NULL;
	
	virtAddr = machine->ReadRegister(4); // doc dia chi ten file thanh thanh ghi R4
	type = machine->ReadRegister(5); // doc kieu mo file tu thanh ghi R5
	if (type != 0 && type != 1 || fileSystem->numFile > FileSystem::MAX_NUM_FILE) // sai kieu mo hoac bang da day
	{
		DEBUG('a', "\nType Error.\n");
		// ham bao loi tra ve -1
		machine->WriteRegister(2, -1); 
				return;
	}
	
	filename = User2System(virtAddr, MAX_FILE_LENGTH + 1); // MAX_FILE_LEGTH = 32
	if (filename == NULL)
	{
		DEBUG('a', "\nNot enough memory in system.");
		machine->WriteRegister(2,-1); 
				return;
	}
	
	if (strcmp(filename, "stdin") == 0) // open stdin
	{
		machine->WriteRegister(2, 0);
				return;
	}
	
	if (strcmp(filename, "stdout") == 0) // open stdout
	{
		if (type == 0)
		{	machine->WriteRegister(2, 1);
						return;
		}
		else
		{
			DEBUG('a', "\nType Error.\n");
			// ham bao loi tra ve -1
			machine->WriteRegister(2, -1); 
						return;
		}
	}
	
	// mo file
	of = fileSystem->Open(filename, type);
	if (of == NULL)
	{
		DEBUG('a', "\nCan't open file.");
		// ham bao loi tra ve -1
		machine->WriteRegister(2, -1); 
				return;
	}
	
	// chen file mo duoc vao bang mo ta file
	for (int i = 2; i < FileSystem::MAX_NUM_FILE; i++)
	{
		if (fileSystem->fileTable[i] == NULL)
		{	
			fileSystem->fileTable[i] = of;
			openFileID = i;
			break;
		}	
	}
	fileSystem->numFile++;

	// thanh cong, tra ve OpenFileID
	machine->WriteRegister(2, openFileID); 
		delete filename;
}

void Read_SystemCall()
{
	int virtAddr = 0; // dia chi buff trong user space
	int charCount = 0; // so byte can doc
	int openFileID = -1;
	
	virtAddr = machine->ReadRegister(4);
	charCount = machine->ReadRegister(5);
	openFileID = machine->ReadRegister(6);

	// invalid value of parameters
	if (virtAddr == 0 || charCount < 1
		|| openFileID < 0 || openFileID > 9
		|| (fileSystem->fileTable[openFileID] == NULL && openFileID != ConsoleInput)// inexist file in fileTable
		|| openFileID == ConsoleOutput) // openFileID = 1: non-permitted to read from stdout
	{
		DEBUG('a', "\nInvalid value of parameters.");
				machine->WriteRegister(2, -1);
		return;
	}

	char * buff = new char[charCount];
	if (buff == NULL)
	{
		DEBUG('a', "\nNot enough memory.");
				machine->WriteRegister(2, -1);
		return;
	}

	int numBytes = 0;
	int curPos = 0;
	if (openFileID == 0) // stdin
	{
		numBytes = gSynchConsole->Read(buff, charCount);
	}	
	else
	{
		curPos = fileSystem->fileTable[openFileID]->GetCurrentPos();
		numBytes = fileSystem->fileTable[openFileID]->ReadAt(buff, charCount, curPos);
	}
	System2User(virtAddr, numBytes, buff);
	machine->WriteRegister(2, numBytes);
		delete[] buff;
}

void Write_SystemCall()
{
	int virtAddr = 0;
	int charCount = 0;
	int openFileID = -1;
	int numBytes = 0;
	
	virtAddr = machine->ReadRegister(4);
	charCount = machine->ReadRegister(5);
	openFileID = machine->ReadRegister(6);

	// loi gia tri cua tham so
	if (virtAddr == 0 || charCount < 1 || openFileID < 0 
		|| openFileID >= FileSystem::MAX_NUM_FILE
		|| openFileID == ConsoleInput )
	{
		DEBUG('a', "\nInvalide value of parameters.");
		increaseProgramCounter();		
		machine->WriteRegister(2, -1);
		return;
	}

	char * buff = User2System(virtAddr, charCount);
	if (buff == NULL)
	{
		DEBUG('a', "\nNot enough memory.");
		increaseProgramCounter();		
		machine->WriteRegister(2, -1);
		return;
	}

	if (openFileID == ConsoleOutput) // write on console
	{
		numBytes = gSynchConsole->Write(buff, charCount);
				machine->WriteRegister(2, numBytes);
		return;
	}

	if (fileSystem->fileTable[openFileID] == NULL)
	{
		DEBUG('a', "\nInexist file.");
		increaseProgramCounter();		
		machine->WriteRegister(2, -1);
		return;
	}

	if (fileSystem->fileTable[openFileID]->type != 0) // 0: write and read
	{
		DEBUG('a', "\nFile is not in writing mode.");
		increaseProgramCounter();		
		machine->WriteRegister(2, -1);
		return;
	}

	int curPos = fileSystem->fileTable[openFileID]->GetCurrentPos();
	numBytes = fileSystem->fileTable[openFileID]->WriteAt(buff, charCount, curPos);

	machine->WriteRegister(2, numBytes);
		delete[] buff;
}

void Close_SystemCall()
{
	int openFileID = -1;
	openFileID = machine->ReadRegister(4); // doc ID cua file can dong tu thanh ghi
	if (openFileID == ConsoleInput || openFileID == ConsoleOutput)
	{
		machine->WriteRegister(2, 0);
				return;
	}

	if (openFileID < 2 || openFileID > 9) 
	{
		machine->WriteRegister(2, -1);
				return;
	}
	
	if (fileSystem->fileTable[openFileID] != NULL)
	{
		delete fileSystem->fileTable[openFileID];
		fileSystem->numFile--;
		fileSystem->fileTable[openFileID] = NULL;
		machine->WriteRegister(2, 0);
				return;
	}
	else
	{
		machine->WriteRegister(2, -1);
			}
}

void Exec_SystemCall()
{
	// Get address of the file name
    int buffAddr = 0;
    buffAddr = machine->ReadRegister(4);

    char* name = User2System(buffAddr,MAX_FILE_LENGTH+1);

	OpenFile *oFile = fileSystem->Open(name);
   	if (oFile == NULL)
    {
		printf("\nExec:: Can't open this file.");
		machine->WriteRegister(2,-1);
		return;
    }

    delete oFile;

	// Return child process id
	int id = pTab->ExecUpdate(name); 
	machine->WriteRegister(2,id);
    return;
}

void Join_SystemCall()
{
	int id = machine->ReadRegister(4);
	int res = pTab->JoinUpdate(id);
	machine->WriteRegister(2,res);
}


int ReadInt_SystemCall()
{
	char * buff = NULL;
	int len = 0;
	int res = 0;
	
	buff = new char[MAX_LEN_INT]; // vung dem cho day ky tu so
	if (buff == NULL) // thieu bo nho
	{
		DEBUG('a', "\nNot enough memory.");
		machine->WriteRegister(2, -1); // tra ve loi trong thanh ghi $v0 ($2)
				return 0;
	}
	
	len = gSynchConsole->Read(buff, MAX_LEN_INT); // doc day ky tu so tu man hinh
	if (len < 1) // khong doc duoc ky tu nao
	{
		machine->WriteRegister(2, 0); // tra ve loi trong thanh ghi $v0 ($2)
				return 0;
	}
		
	// doc duoc day ky tu so
	// kiem tra day ky tu hop le
	if (! testBuffReadInt(buff, len))
	{
		machine->WriteRegister(2, 0); // chuoi ky so doc vao khong hop le, tra ve 0 trong $v0 ($2)
				return 0;
	}
	
	// chuoi hop len doi chuoi thanh so Int	
	res = strToInt(buff, len); // doi chuoi ky so doc vao thanh so nguyen
	machine->WriteRegister(2,res); // tra so nguyen ket qua ve thanh ghi $v0 ($0)
	delete buff;
		return res;
}

void PrintInt_SystemCall()
{
	int a = machine->ReadRegister(4); // lay tham so duy nhat (so nguyen) tu $a0 ($4)
	char * buff = IntToStr(a); // doi thanh chuoi ky so
	gSynchConsole->Write(buff, strlen(buff)); // ghi ra man hinh console
		delete buff;
}

char ReadChar_SystemCall()
{
	char ch = '\0';
	gSynchConsole->Read(&ch, 1); // doc 1 ky tu tu console
	machine->WriteRegister(2, ch); // ghi ky tu doc duoc vao thanh ghi $v0 ($2)
		return ch;
}

void PrintChar_SystemCall()
{
	char ch = (char) machine->ReadRegister(4); // doc tham so duy nhat (ky tu) tu thanh ghi $a0 ($4)
	gSynchConsole->Write(&ch, 1); // ghi ky tu ra console
	}

void ReadString_SystemCall()
{
	// doc cac tham so trong cac thanh ghi $a0($4), $a1($5)
	int virtAddr = machine->ReadRegister(4); // dia chi chuoi
	int len = machine->ReadRegister(5); // chieu dai chuoi
	char * buff = new char[len + 1]; // them 1 cho null
	if (buff == NULL)
	{
		// not enough memory
		machine->WriteRegister(2, -1); // tra ve so byte doc duoc
				return;
	}
	
	int numBytes = gSynchConsole->Read(buff, len); // doc chuoi ky tu tu console, tra ve so byte doc duoc
	buff[numBytes] = NULL; // gan ky tu ket thuc chuoi cho chuoi vua doc
	System2User(virtAddr, numBytes + 1, buff); // sao chep chuoi doc duoc tu vung nho he thong ra vung nho nguoi dung (system space --> user space)
	machine->WriteRegister(2, numBytes); // tra ve so byte doc duoc
		delete buff;
}

void PrintString_SystemCall()
{
	// doc tham so duy nhat tu thanh ghi $a0 ($4)
	int virtAddr = machine->ReadRegister(4); // dia chi chuoi truyen vao
	char ch;
	// lap: doc tung ky tu va in ra console cho den khi gap ky tu ket thuc
	do {
		char * buff = User2System(virtAddr, 1); // chuyen 1 byte (1 ky tu) trong chuoi dau vao 
		//(chuoi nay dang nam trong user space vao system space)
		if (buff == NULL)
		{
			// not enough memory
						return;
		}
		
		ch = *buff;
		gSynchConsole->Write(buff, 1); // in ky tu vua doc ra console
		delete buff;
		
		virtAddr += 1; // tang dia chi chuoi vao len 1 byte == tro den ky tu tiep theo
	} while (ch != '\0'); // dung khi gap ky tu null ket thuc chuoi
	}

void Seek_SystemCall()
{
	int pos = 0;
	OpenFileID openFileID = -1;
	
	pos = machine->ReadRegister(4);
	openFileID = machine->ReadRegister(5);

	// khong duoc seek tren console
	if (pos < -1 || openFileID == 0 || openFileID == 1
		|| fileSystem->fileTable[openFileID] == NULL) // inexist file
	{
		DEBUG('a', "\nInvalid value of parameters.");
		machine->WriteRegister(2, -1);
				return;
	}

	if (pos == -1 || pos >= fileSystem->fileTable[openFileID]->Length()) // seek den cuoi file
	{
		// Length = n: file co kich thuoc n byte tu 0 --> n - 1, n - 1 la ky ket thuc file (EOF)
		pos = fileSystem->fileTable[openFileID]->Length() - 1;		
	}

	int curPos = 0;
	fileSystem->fileTable[openFileID]->Seek(pos);
	curPos = fileSystem->fileTable[openFileID]->GetCurrentPos();
	
	machine->WriteRegister(2, curPos);
	}

void CreateSemaphore_SystemCall()
{
	int addrName = machine->ReadRegister(4);
	int semval = machine->ReadRegister(5);

	char *name = User2System(addrName,MAX_FILE_LENGTH + 1);

    if(name == NULL)
	{
		printf("\nCreateSemaphore:: Something went wrong.\n");
		machine->WriteRegister(2,-1);
		return;
	}

	int res = semTab->Create(name,semval);

	if(res < 0)
	{
		printf("\nnCreateSemaphore:: Can't create semaphore : %s \n",name);
		machine->WriteRegister(2,-1);
		return;
	}
    // Successfully
	machine->WriteRegister(2,res);
}

void Signal_SystemCall()
{
	int addrName = machine->ReadRegister(4);
	char *name = User2System(addrName,MAX_FILE_LENGTH + 1);

	if(name == NULL)
	{
        printf("\nUp:: Something went wrong.\n");
		machine->WriteRegister(2,-1);
		return;
	}

	int res = semTab->Signal(name);
	if(res < 0)
	{
		printf("\nUp:: Can't Up semaphore : %s.\n",name);
		machine->WriteRegister(2,-1);
		return;
	}
	machine->WriteRegister(2,res);
}

void Wait_SystemCall()
{
	int addr = machine->ReadRegister(4);
	char *name = User2System(addr,32);

	if(name == NULL)
	{
		printf("\nSomething went wrong. Try again?\n");
		machine->WriteRegister(2,-1);
		return;
	}

	int res = semTab->Wait(name);

	if(res < 0)
	{
		printf("\nCan't Down semaphore : %s",name);
		machine->WriteRegister(2,-1);
		return;
	}
	machine->WriteRegister(2,0);
}

void SetMsg_SystemCall()
{
	int id = machine->ReadRegister(4);
	int value = machine->ReadRegister(5);
	//char *num = IntToStr(id);
	semTabMail[id]->P();
	while(mailbox[id] != -1); //dang co thu
	mailbox[id] = value;
	semTabMail[id]->V();
}

void GetMsg_SystemCall()
{
	int id = currentThread->processID;
	//char *num = IntToStr(id);
	semTabMail[id]->P();
	int val = mailbox[id];
	mailbox[id] = -1;
	machine->WriteRegister(2, val);
	semTabMail[id]->V();
}

void IsEmptyMsg_SystemCall()
{
	int id = currentThread->processID;
	//char *num = IntToStr(id);
	semTabMail[id]->P();
	//printf("%d\n", mailbox[id]);
	if (mailbox[id] == -1) machine->WriteRegister(2, 1);
	else machine->WriteRegister(2, 0);
	semTabMail[id]->V();
}
