#include "syscall.h"
#include "copyright.h"

int main(void)
{
	// xuat thong tin nhom
	PrintString("\tTHONG TIN NHOM\n");
	PrintString("STT   MSSV       Ho ten\t\t  Lop\n");
	PrintString("1   1512479  Nguyen Duy Tam   CNTN2015\n");
	PrintString("2   1512157  Cao Nguyen Minh Hieu   CNTN2015\n");
	PrintString("----------------------------------------\n");
	PrintString("\tMO TA CHUONG TRINH\n");
	PrintString("STT Ten \t\t\tMo ta\n");
	PrintString("1   ascii In ra ban mang ascii\n");
	PrintString("2   sort  Nhap vao n so nguyen (n <= 100)\n");
	PrintString("          Sap xep mang bang bubble sort\n");
	PrintString("----------------------------------------\n");		
	Halt();
	return 0;
}
