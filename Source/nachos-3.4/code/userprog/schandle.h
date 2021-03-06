#ifndef SCHANDLE_H
#define SCHANDLE_H

#include "copyright.h"
#include "system.h"
#include "syscall.h"

int System2User(int virtAddr,int len,char* buffer); // sao chep vung nho tu he thong (system space) ra vung nguoi dung (user space)
char* User2System(int virtAddr,int limit); // sao chep vung nho tu nguoi dung (user space) vo vung nho he thong (system space)

void increaseProgramCounter(); // tang thanh ghi chi lenh PC tro den lenh tiep theo
void SystemCall(int type); // xu ly cac type trong SyscallException

// ham xu ly tung syscall cu the trong SyscallException
void Halt_SystemCall();
void Exit_SystemCall();
void Create_SystemCall();
void Open_SystemCall();
void Read_SystemCall();
void Write_SystemCall();
void Close_SystemCall();
void Exec_SystemCall();
void Join_SystemCall();

int ReadInt_SystemCall();
void PrintInt_SystemCall();
char ReadChar_SystemCall();
void PrintChar_SystemCall();
void ReadString_SystemCall();
void PrintString_SystemCall();
void Seek_SystemCall();
void CreateSemaphore_SystemCall();
void Signal_SystemCall();
void Wait_SystemCall();

void SetMsg_SystemCall();
void GetMsg_SystemCall();
void IsEmptyMsg_SystemCall();

#define MAX_LEN_INT 10 // so ky so toi da cho mot so nguyen           //
#define MAX_FILE_LENGTH 32 // chieu dai toi da ten tap tin            //  

/************************* support func *******************************/
bool testBuffReadInt(char * buff, int len); // kiem tra chuoi ky so doc vao la hop le
int strToInt(char * buff, int len); // chuyen chuoi ky so thanh so nguyen
char * IntToStr(int a); // chuoi so nguyen thanh chuoi ky so
int strlen(char * buff); // tinh do dai mot chuoi ky tu

#endif
