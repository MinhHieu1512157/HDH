#include "syscall.h"
#include "copyright.h"

void memset(char* str,int k,int n);
void del1stChar(char* str);
int strcat(char* str1,char* str2);
void resetVariables(); // reset value of variables

void memset(char* str,int k,int n)
{
	//if ((int)str == 0 || n < 1) { return;}
	
	int i = 0;
	for(i = 0; i < n ; i++)
		str[i] = (char)k;
}

void del1stChar(char* str)
{
	//if ((int)str == 0) {return;}
	
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = str[i+1];
		i++;
	}
}

int strcat(char* str1,char* str2)
{
	//if ((int)str1 == 0 || (int)str2 == 0) {return;}
	
	int len1 = 0;
	int len2 = 0;
	
	while(str1[len1] != '\0')
		++len1;
	while(str2[len2] != '\0')
		++len2;

	//kiem tra xau 1 con du cho chua xau2 ko
	
	//copy chuoi 2 vao chuoi 1
	len2 = 0;
	while(str2[len2] != '\0')
		str1[len1++] = str2[len2++];
	str1[len1] = '\0';
}

void resetVariables(char * buffer, char * link)
{
	//if ((int)buffer == 0 || (int)link == 0) {return;}
	
	memset(buffer, 0, 60);
	memset(link, 0, 60);
	
	link[0] = '.';
	link[1] = '/';
	link[2] = 't';
	link[3] = 'e';
	link[4] = 's';
	link[5] = 't';
	link[6] = '/';
}

int main()
{
    SpaceId newProc;
    char ch[2], buffer[60];
    char * prompt = "[--]#";
    char link[60];
    int i;       

    resetVariables(buffer, link);
    do //while(1)
    {
	Write("\n", 1, ConsoleOutput);
	Write(prompt, 10, ConsoleOutput);

	Read(buffer, 59, ConsoleInput);
	if(buffer[0] == '0')
		break;
		
	if(buffer[0] == '&')
	{
		del1stChar(buffer);
		strcat(link, buffer);
		
		//Write(link, 60, ConsoleOutput);
		//Write("\n", 1, ConsoleOutput);
		
		newProc = Exec(link);
		if(newProc < 0)
		{
			Write("\nCan't not exec ", 50, ConsoleOutput);
			resetVariables(buffer, link);
			
			continue;
		}
	}
	else
	{
		strcat(link,buffer);
		
		//Write(link, 60, ConsoleOutput);
		//Write("\n", 1, ConsoleOutput);
		
		newProc = Exec(link);
		if(newProc < 0)
		{
			Write("\nCan't not exec ", 50, ConsoleOutput);
			resetVariables(buffer, link);

			continue;
		}	
		Join(newProc);
	}
	resetVariables(buffer, link);

  } while(1);
}
