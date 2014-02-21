#include "StdAfx.h"
#include "MianZi.h"

CMianZi::CMianZi(void)
{
	for(int i = 0;i < 3;i++)
	{
		Card[i].Type = TYPE_UNKNOWN;
	}
}


CMianZi::~CMianZi(void)
{
}
