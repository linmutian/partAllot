#pragma once

#include <population.h>


class genetic
{
public:
	genetic(int);
	void setGFH(int [PartnerNum]);
	void setCalcTime(int);

	//int getBestReward();
	//int getBestAllot(int);

	void evolution();
	void output();

private:
	int calcTime = 1000;
	int calcTimeMin = 100;
	population *p;

	int bestAllot[PartnerNum + 2];

};