#include "stable.h"

STable::STable()
{
	int i;
	this->bm = new BitMap(MAX_SEMAPHORE);
	for(i = 0; i < MAX_SEMAPHORE ; i++)
		this->lockTab[i] = NULL;

}

STable::~STable()
{
	if(bm != NULL)
		delete this->bm;
	if(lockTab != NULL)
		delete []lockTab;
}

int STable::Create(char* name,int init)
{
	int id = bm->Find();
	if(id < 0)
		return -1;

	lockTab[id] = new Sem(name,init);

	return 0;
}
int STable::Wait(char* name)
{
	for(int i = 0 ; i < MAX_SEMAPHORE ; ++i)
	{
		if(bm->Test(i))
		{
			char* temp = lockTab[i]->GetName();
			if(strcmp(temp,name) == 0)
			{
				lockTab[i]->wait();
				return 0;
			}
		}
	}
	return -1;
}

int STable::Signal(char* name)
{
	for(int i = 0 ; i < MAX_SEMAPHORE ; ++i)
	{
		if(bm->Test(i))
		{
			char* temp = lockTab[i]->GetName();
			if(strcmp(temp,name) == 0)
			{
				lockTab[i]->signal();
				return 0;
			}
		}
	}
	return -1;
}

int STable::FindFreeSlot(int id)
{
	return bm->Find();
}
