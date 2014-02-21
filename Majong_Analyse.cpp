#include "StdAfx.h"
#include "Majong_Analyse.h"

unsigned long int CMajong_Analyse::TingPaiResult = 0;

CMajong_Analyse::CMajong_Analyse(void)
{
}

CMajong_Analyse::~CMajong_Analyse(void)
{
}
/*
  平和 | 斷么九 | 一盃口 | 役牌 
  三色同順 | 一氣通貫 | 混全帶么九 | 七對子 | 對對和 | 三暗刻
  三色同刻 | 混老頭 | 小三元 |
  混一色 | 純全帶么九 | 二杯口
  清一色	
  國士無雙 | 四暗刻 | 大三元 | 小四喜 | 大四喜 | 字一色 | 綠一色 | 清老頭 | 九蓮寶燈 |
  形听
*/
void CMajong_Analyse::Analyse()
{
	NewSort();//排序

	//标记已经被用的牌
	int Card_Used[13] = {CARD_UNUSED};
	CPaiMian paimian;
	for(int i = 0;i < 13;i++)
	{
		Card_Used[i] = CARD_UNUSED;
	}

	TingPaiResult = 0;//初始化听牌结果
	Zuhe(Card_Used,paimian,-1,-1,-1,-1);//第一次调用参数全部用-1
}

//按类型排序  W->S->P->F->SY
void CMajong_Analyse::NewSort()
{
	CMajong_Card temp[13];
	int idx = 0;
	for(int c_type = WAN;c_type < BAI;c_type++)
	{
		if(c_type < DONG)
		{
			for(int i = 1;i <= 9;i++)
			{
				for (int k = 0;k <13;k++)
				{
					if(pool[k].Type == c_type && pool[k].Num == i)
					{
						temp[idx++] = pool[k];
					}
				}
			}
		}
		else
		{
			for (int k = 0;k <13;k++)
			{
				if(pool[k].Type == c_type)
				{
					temp[idx++] = pool[k];
				}
			}
		}
	}

	for(int i = 0;i < 13;i++)
	{
		pool[i] = temp[i];
	}
}

//递归组合面子
void CMajong_Analyse::Zuhe(int Card_Used[],CPaiMian paimian,int num1,int num2,int num3,int mianzi_type)
{
	if(num1 >= 0 && num2 >= 0)
	{
		paimian.mianzi[paimian.Cur_Idx].Card[0] = pool[num1];
		Card_Used[num1] = CARD_USED;
		paimian.mianzi[paimian.Cur_Idx].Card[1] = pool[num2];
		Card_Used[num2] = CARD_USED;
		paimian.mianzi[paimian.Cur_Idx].type = mianzi_type;
		if (num3 >= 0)
		{
			paimian.mianzi[paimian.Cur_Idx].Card[2] = pool[num3];
			Card_Used[num3] = CARD_USED;
		}
		paimian.Total_num += 2+(num3>=0);
		paimian.Cur_Idx++;

		int idx_dudiao = -1;
		if(paimian.Total_num == 12)//只剩一张牌
		{
			idx_dudiao = FindDudiao(Card_Used);
			if(idx_dudiao != -1)
			{
				paimian.mianzi[paimian.Cur_Idx].Card[0] = pool[idx_dudiao];
				Card_Used[idx_dudiao] = CARD_USED;
				paimian.mianzi[paimian.Cur_Idx].type = DUDIAO;
				paimian.Cur_Idx++;
				paimian.Total_num++;
			}
		}
		TingPaiResult |= paimian.Analyse();
		if(paimian.Total_num == 13)
		{
			if(idx_dudiao != -1)
				Card_Used[idx_dudiao] = CARD_UNUSED;
			return;
		}
	}

	int Next_Card_id;
	int Next_Next_Card_id;
	for(int i = 0;i < 13;i++)
	{
		if(CARD_UNUSED == Card_Used[i])
		{
			//顺子
			 Next_Card_id = FindCard(CMajong_Card(pool[i].Num+1,pool[i].Type),Card_Used,i,-1);
			 Next_Next_Card_id = FindCard(CMajong_Card(pool[i].Num+2,pool[i].Type),Card_Used,i,Next_Card_id);
			if(Next_Card_id >= 0 && Next_Next_Card_id >= 0)
			{
				Zuhe( Card_Used, paimian, i, Next_Card_id, Next_Next_Card_id, SHUNZI);
				Card_Used[i] = CARD_UNUSED;
				Card_Used[Next_Card_id] = CARD_UNUSED;
				Card_Used[Next_Next_Card_id] = CARD_UNUSED;
			}

			//刻子
			Next_Card_id = FindCard(CMajong_Card(pool[i].Num,pool[i].Type),Card_Used,i,-1);
			Next_Next_Card_id = FindCard(CMajong_Card(pool[i].Num,pool[i].Type),Card_Used,i,Next_Card_id);
			if(Next_Card_id >= 0 && Next_Next_Card_id >= 0)
			{
				Zuhe( Card_Used, paimian, i, Next_Card_id, Next_Next_Card_id, KEZI);
				Card_Used[i] = CARD_UNUSED;
				Card_Used[Next_Card_id] = CARD_UNUSED;
				Card_Used[Next_Next_Card_id] = CARD_UNUSED;
			}

			//雀头
			Next_Card_id = FindCard(CMajong_Card(pool[i].Num,pool[i].Type),Card_Used,i,-1);
			if(Next_Card_id >= 0)
			{
				Zuhe( Card_Used, paimian, i, Next_Card_id, -1, QUETOU);
				Card_Used[i] = CARD_UNUSED;
				Card_Used[Next_Card_id] = CARD_UNUSED;
			}

			//顺子缺一张
			Next_Card_id = FindCard(CMajong_Card(pool[i].Num+1,pool[i].Type),Card_Used,i,-1);
			Next_Next_Card_id = FindCard(CMajong_Card(pool[i].Num+2,pool[i].Type),Card_Used,i,Next_Card_id);
			if(Next_Card_id >= 0 && Next_Next_Card_id < 0)
			{
				Zuhe( Card_Used, paimian, i, Next_Card_id, -1, QUEZHANG);
				Card_Used[i] = CARD_UNUSED;
				Card_Used[Next_Card_id] = CARD_UNUSED;
			}
			else if(Next_Card_id < 0 && Next_Next_Card_id >= 0)
			{
				Zuhe( Card_Used, paimian, i, Next_Next_Card_id, -1, QUEZHANG);
				Card_Used[i] = CARD_UNUSED;
				Card_Used[Next_Next_Card_id] = CARD_UNUSED;
			}
		}
	}
}

//查找指定的CMajong_Card所在的位置
int CMajong_Analyse::FindCard( CMajong_Card dst_card,int Card_Used[],int mask1,int mask2)
{
	int result = -1;
	for(int i = 0;i < 13;i++)
	{
		if(mask1 != i && mask2 != i && Card_Used[i] == CARD_UNUSED && pool[i].Num == dst_card.Num && pool[i].Type == dst_card.Type)
			return i;
	}
	return result;
}

//查找仅剩的一张还没被列入组合的牌
int CMajong_Analyse::FindDudiao( int Card_Used[] )
{
	for(int i = 0;i < 13;i++)
	{
		if(Card_Used[i] == CARD_UNUSED)
		{
			return i;
		}
	}
	return -1;
}


