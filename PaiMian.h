#pragma once

#include "MianZi.h"
#include "PaiMian.h"
class CPaiMian
{
public:
	CMianZi mianzi[7];
	int Cur_Idx;
	int Total_num;
	unsigned long int Analyse();

	int GetQuezhang();
	int GetTypeNum(int MianziType);

	unsigned long int duipeng();
	unsigned long int qiduizi();
	unsigned long int dudiao();
	unsigned long int changgui();
	CPaiMian(void);
	~CPaiMian(void);
};


