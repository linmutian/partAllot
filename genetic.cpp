#include <genetic.h>
#include <iostream>
#include <time.h> 

genetic::genetic(int initCalcTime)
{
	int testGFH[12] = { 17214,16056,18554,17518,10566,10218,9678,9624,9232,7056,6806,6730 };
	p = new population(testGFH);
	setCalcTime(initCalcTime);
}

void genetic::setGFH(int inputGFH[PartnerNum])
{
	p->setPartnerGHF(inputGFH);
}

void genetic::setCalcTime(int inputCalcTime)
{
	if (inputCalcTime < 100)
	{
		std::cout << " 输入次数过少，将调整为100" << std::endl;
		calcTime = 100;
	}
	calcTime = inputCalcTime;
}

void genetic::evolution()
{
	time_t tStart = clock();
	int maxIncome = 0;

	for (int i = 0; i < calcTime; i++)
	{
		p->evolution(maxIncome); 
		if (maxIncome < p->maxWoodIncome)
		{
			maxIncome = p->maxWoodIncome;
			for (int j = 0; j < PartnerNum + 2; j++)
				bestAllot[j] = p->king[j];
		}
	}
	time_t tEnd = clock();

	std::cout << "maxIncome = " << maxIncome << std::endl;
	std::cout << "  allot：";
	for (int i = 0; i < PartnerNum; i++)
	{
		std::cout << bestAllot[i] << "  ";
	}
	std::cout << std::endl;
	std::cout << " 耗时 = " << tEnd - tStart << " ms. " << std::endl;

}