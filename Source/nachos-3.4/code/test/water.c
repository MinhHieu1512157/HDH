//#include "syscall.h"
#define READ_ONLY 1
#define READ_WRITE 0

static int times;
static short line;
static short student;

int atoi(char *strNum) {
	short first = 1;
	int ret = 0, i = 0;
	char ch, cSign = ' ';
	while (strNum[i] != '\0') {
		ch = strNum[i++];
		if (ch == '-' || ch == '+') {
			if (first && cSign == ' ') cSign = ch;
			else break;
		} else {
			ret *= 10;
			ret += ch - 48;
		}
		first = 0;
	}
	if (cSign == '-' && ret) ret = -ret;
	return ret;
}

int ReadNum (int fID, char* strNum) {
	short first = 1;
	char buff[2], ch, cSign = ' ';
	int read, ret = 0, k = 0;
	read = Read(buff, 1, fID);
	while (read && (buff[0] == 32 || buff[0] == '\n')) //loai bo khoang trang va dau xuong dong cho toi khi gap ky tu dau tien
		read = Read(buff, 1, fID);
	while(read) {
		ch = buff[0];
		if (ch == 32 || ch == '\n') break; //khoang trang hay '\n'
		if (ch == '-' || ch == '+') {
			if (first && cSign == ' ') cSign = ch;
			else break;
			strNum[k++] = ch;
		} else {
			ret *= 10;
			ret += ch - 48;
			strNum[k++] = ch;
		}
		read = Read(buff, 1, fID);
		first = 0;
	}
	if (cSign == '-' && ret) ret = -ret;
	if (ch == '\n') { ++line; student = 0; };
	strNum[k] = '\0';
	return ret;
}

//Ham doc noi dung file
//0 -> thoi diem
//1 -> sinh vien thu may
//2 -> bao nhieu lit nuoc
void ReadInfo (int fID, int* info, char* strLiter) {
	info[0] = line;
	info[1] = ++student;
	info[2] = ReadNum(fID, strLiter);
}

void main() {
	short faucet[2], idStudent[100]; //0 -> free, 1 -> busy
	char strNum[11];
	int prevLine = 1, fRead, fWrite, i, pid, countStudent, info[3], tmp;
	line = 0; student = 0; countStudent = 0;
	faucet[0] = 0; faucet[1] = 0; //ca 2 voi deu dang ranh
	CreateSemaphore("Student", 2); //semaphore gioi han sinh vien lay nuoc
	CreateFile("./output.txt");
	fRead = Open("./input.txt", READ_ONLY);
	fWrite = Open("./output.txt", READ_WRITE);
	times = ReadNum(fRead, strNum); //so luong thoi diem can xet
	if (times > 0) {
		do {
			while (prevLine == line) { //khoi tao toan bo sinh vien toi lay nuoc trong cung 1 thoi diem
				ReadInfo(fRead, info, strNum);
				pid = Exec("./test/student");
				SetMsg(pid, info[2]); //lit nuoc can lay
				//SetMsg(pid, info[1]); //sinh vien thu may
				//SetMsg(pid, info[0]); //thoi diem thu may
				idStudent[countStudent++] = pid;
			}
			i = 0; prevLine = line;
			while (countStudent > 0) {
				pid = idStudent[i];
				if (!faucet[0]) { //dung voi so 1
					Write("1 ", 2, fWrite);					
					SetMsg(pid, 1);
					faucet[0] = 1;
				} else if (!faucet[1]) { //dung voi so 2
					Write("2 ", 2, fWrite);
					SetMsg(pid, 2);
					faucet[1] = 1;
				}
				else { //khong co voi nao ranh
					PrintString("HERE1\n");
					while (1){
						if (IsEmptyMsg() == 0) { //doi cho toi khi co sinh vien gui bao da lay xong
							faucet[GetMsg()] = 0;
							break;
						}
					}
					PrintString("HERE2\n");
					continue;
				}
				--countStudent; ++i;
			}
			Write("\n", 1, fWrite);
			while (i > 0)
				Join(idStudent[--i]); //doi toan bo tien trinh thoi diem 1 xong moi sang thoi diem 2
		} while (line <= times);
	}
	Close(fRead); Close(fWrite);
}
