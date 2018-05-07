#ifndef PTABLE_H
#define PTABLE_H

#include "bitmap.h"
#include "pcb.h"
#include "synch.h"

#define MAX_PROCESS 10

class PTable
{
	private:
		BitMap *bm;
		PCB* pcb[MAX_PROCESS];
		int psize;
		Semaphore* bmsem;//dung de ngan chan truong hop nap 2 tien trinh cung luc
		
	public:
		PTable(int size);
		//khoi tao size doi tuong pcb de luu size process. Gán giá tri ban dau là null.
		//nho khoi tao bm va bmsem de su dung
		~PTable();//huy cac doi tuong da tao
		
		int ExecUpdate(char* name); //return PID
		int ExitUpdate(int ec);

		int JoinUpdate(int id);
		//tim free slot de luu thong tin cho tien trinh moi
		int GetFreeSlot();

		//kiem tra ton tai processID nay hay ko?
		bool IsExist(int pid);

		//khi tien trinh ket thuc , xoa 1 processID ra khoi mang quan ly no
		void Remove(int pid);
		char* GetFileName(int id);		
};
#endif 
