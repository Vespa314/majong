#pragma once
#include "Majong_Card.h"
#include "PaiMian.h"
#define CARD_USED 1
#define CARD_UNUSED 0

class CMajong_Analyse
{
public:
	CMajong_Card pool[13];
	CMajong_Card result[13];
	CMajong_Analyse(void);
	~CMajong_Analyse(void);

	void NewSort();
	void Analyse();

	void Zuhe(int Card_Used[],CPaiMian paimian,int num1,int num2,int num3,int mianzi_type);
	int FindCard(CMajong_Card _dst_card,int Card_Used[],int mask1,int mask2);
	int FindDudiao(int Card_Used[]);

	static unsigned long int TingPaiResult;
};

