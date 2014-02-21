#include "StdAfx.h"
#include "Majong_Card.h"

CMajong_Card::CMajong_Card(void)
{
	Type = TYPE_UNKNOWN;
}


CMajong_Card::~CMajong_Card(void)
{
}

unsigned long int CMajong_Card::GetIdx()
{
	if (WAN == Type)
	{
		return 0x01<<(Num-1);
	}
	else if(TIAO == Type)
	{
		return 0x01<<(Num-1+9);
	}
	else if(BING == Type)
	{
		return 0x01<<(Num-1+18);
	}
	else
	{
		return 0x01<<(Type-DONG+27);
	}

	return 0;
		
}
