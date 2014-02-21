#include "StdAfx.h"
#include "PaiMian.h"

CPaiMian::CPaiMian(void)
{
	Cur_Idx = 0;
	Total_num = 0;
}

CPaiMian::~CPaiMian(void)
{
}

unsigned long int CPaiMian::Analyse()
{
	unsigned long int result = 0;
	//�����������12�������ܳ�������ʽ
	if(Total_num < 12)
		return 0;

	
	int quezhang_num = GetTypeNum(QUEZHANG);
	//����1��û��ɵ�˳�ӣ�����������
	if(quezhang_num > 1)
		return 0;

	int quetou_num = GetTypeNum(QUETOU);
	//3,4,5�����ӣ�����������
	if(quetou_num >=3 && quetou_num < 6)
		return 0;

	//������ͬʱ��������˫�����߶��ӣ�Ƕ�£�ƫ�������
	if((2 == quetou_num)+(6 == quetou_num)+(0 == quetou_num)+(1 == quezhang_num)>1)
		return 0;

	if(2 == quetou_num)//�Զ���
		result =  duipeng();
	else if(6 == quetou_num)//�߶���
		result =  qiduizi();
	else if(0 == quetou_num)//����
		result =  dudiao();
	else if(1 == quezhang_num)//˳�Ӳ�����
		result =  changgui();
	

// 	CString str = "";
// 	for(int i = 0;i < Cur_Idx;i++)
// 	{
// 		if(mianzi[i].type == SHUNZI)
// 			str.Format("%s˳��:",str);
// 		else if(mianzi[i].type == KEZI)
// 			str.Format("%s����:",str);
// 		else if(mianzi[i].type == QUETOU)
// 			str.Format("%s����:",str);
// 		else if(mianzi[i].type == QUEZHANG)
// 			str.Format("%sȱ��:",str);
// 		else if(mianzi[i].type == DUDIAO)
// 			str.Format("%s����:",str);
// 		else
// 			str.Format("%sδ֪:",str);
// 		for(int j = 0;j < 3;j++)
// 		{
// 			if(mianzi[i].Card[j].Type != TYPE_UNKNOWN)
// 			{
// 				if(mianzi[i].Card[j].Type == WAN)
// 					str.Format("%s %dW",str,mianzi[i].Card[j].Num);
// 				else if(mianzi[i].Card[j].Type == TIAO)
// 				{
// 					str.Format("%s %dS",str,mianzi[i].Card[j].Num);
// 
// 				}else if(mianzi[i].Card[j].Type == BING)
// 					str.Format("%s %dP",str,mianzi[i].Card[j].Num);
// 				else
// 					str.Format("%s %d",str,mianzi[i].Card[j].Type-DONG);
// 			}
// 		}
// 		str.Format("%s\n",str);
// 	}
// 	
// 	str.Format("%s����:\n\n",str);
// 	for(int i = 0;i < 34;i++)
// 	{
// 		if(result & 0x01<<i)
// 		{
// 			if(i<9)
// 				str.Format("%s %dW",str,i+1);
// 			else if(i<18)
// 			{
// 				str.Format("%s %dS",str,i+1-9);
// 			}else if(i<27)
// 				str.Format("%s %dP",str,i+1-18);
// 			else
// 				str.Format("%s %d",str,i+1-27);
// 		}
// 	}
// 		AfxMessageBox(str);

	return result;
}



int CPaiMian::GetTypeNum( int MianziType )
{
	int counter = 0;
	for(int i = 0;i < Cur_Idx;i++)
	{
		if(mianzi[i].type == MianziType)
		{
			counter++;
		}
	}
	return counter;
}

unsigned long int CPaiMian::duipeng()
{
	unsigned long int result = 0x00;
	for(int i = 0;i < Cur_Idx;i++)
	{
		if(mianzi[i].type == QUETOU)
			result |= mianzi[i].Card[0].GetIdx();
	}
	return result;
}

unsigned long int CPaiMian::qiduizi()
{
	unsigned long int result = 0x00;
	for(int i = 0;i < Cur_Idx;i++)
	{
		if(mianzi[i].type == DUDIAO)
			result |= mianzi[i].Card[0].GetIdx();
	}
	return result;
}

unsigned long int CPaiMian::dudiao()
{
	unsigned long int result = 0x00;
	for(int i = 0;i < Cur_Idx;i++)
	{
		if(mianzi[i].type == DUDIAO)
			result |= mianzi[i].Card[0].GetIdx();
	}
	return result;
}

//˳��ȱһ��
unsigned long int CPaiMian::changgui()
{
	unsigned long int result = 0x00;
	for(int i = 0;i < Cur_Idx;i++)
	{
		if(mianzi[i].type == QUEZHANG)
		{
			if (2 == mianzi[i].Card[1].Num-mianzi[i].Card[0].Num)
			{
				result |= CMajong_Card(mianzi[i].Card[0].Num+1,mianzi[i].Card[0].Type).GetIdx();
				return result;
			}
			else if(1 == mianzi[i].Card[0].Num)
			{
				result |= CMajong_Card(3,mianzi[i].Card[0].Type).GetIdx();
				return result;
			}
			else if(8 == mianzi[i].Card[0].Num)
			{
				result |= CMajong_Card(7,mianzi[i].Card[0].Type).GetIdx();
				return result;
			}
			else
			{
				result |= CMajong_Card(mianzi[i].Card[0].Num-1,mianzi[i].Card[0].Type).GetIdx();
				result |= CMajong_Card(mianzi[i].Card[1].Num+1,mianzi[i].Card[0].Type).GetIdx();
				return result;
			}

		}
	}
	return result;
}
