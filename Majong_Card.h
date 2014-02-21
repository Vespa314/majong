#pragma once

#define TYPE_UNKNOWN -1

#define WAN 1
#define TIAO 2
#define BING 3

#define DONG 4
#define NAN 5
#define XI 6
#define BEI 7
#define ZHONG 8
#define FA 9
#define BAI 10
class CMajong_Card
{
public:
	CMajong_Card(int num,int type):Num(num),Type(type){};
	CMajong_Card(void);
	~CMajong_Card(void);

	CMajong_Card & operator=(const CMajong_Card &t1){
		Num = t1.Num;
		Type = t1.Type;
		return *this;
	}

	unsigned long int GetIdx();
	int Num;
	int Type;
};
