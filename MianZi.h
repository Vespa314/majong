#pragma once

#include "Majong_Card.h"

#define SHUNZI 1
#define KEZI 2
#define QUETOU 3

#define QUEZHANG 4
#define DUDIAO 5
class CMianZi
{
public:
	CMajong_Card Card[3];
	int type;
	CMianZi(void);
	~CMianZi(void);
};
