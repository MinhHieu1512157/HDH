#ifndef PCB_H
#define PCB_H

#include "thread.h"
#include "synch.h"

class PCB
{
	private:
		Semaphore* joinsem; //semaphore cho qua trinh join
		Semaphore* exitsem; //semaphore cho qua trinh exit
		Semaphore* multex; // semaphore cho truy xuat doc quyen
		int exitcode;
		int numwait;//so tien trinh da join

		char FileName[32]; //ten cua chuong trinh duoc exec	

		Thread* thread;
		int pid;
		
	public:
		int parentID;//ID cua tien trinh cha
		PCB();
		PCB(int id);//contructor
		~PCB();//deconstructor
		
		// nap chuong trinh co ten luu trong bien filename và  processID la pid 
		int Exec(char *filename,int pid);
		int GetID();
		int GetNumWait(); 

		void JoinWait(); //1.tien trinh cha doi tien trinh con ket thuc
		void ExitWait(); //4.la tien trinh con ket thuc

		void JoinRelease(); //2.bao cho tien trinh cha thuc thi tiep
		void ExitRelease(); //3.cho phep tien trinh con ket thuc

		void IncNumWait(); 
		void DecNumWait(); 

		void SetExitCode(int ec);
		int  GetExitCode();

		void SetFileName(char* fn);
		char* GetFileName();		
};
#endif
