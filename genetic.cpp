#include <genetic.h>
#include <iostream>
#include <time.h> 
#include <iomanip>

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
		calcTime = 100;
	}
	calcTime = inputCalcTime;
}

void genetic::evolution()
{
	time_t timeStart = clock();
	time_t timeNow, timeLast;

	int maxIncome = 0;
	timeLast = clock();

	for (int i = 0; i < calcTime; i++)
	{

		p->evolution(maxIncome); 
		if (maxIncome < p->maxWoodIncome)
		{
			maxIncome = p->maxWoodIncome;
			for (int j = 0; j < PartnerNum + 2; j++)
				bestAllot[j] = p->king[j];
		}

		timeNow = clock();
		if (i == calcTime - 1)
		{
			time_t timeEnd = clock();
			std::cout << " ¼ÆËãÍê³É£¡  ºÄÊ± =" << (timeEnd - timeStart)/1000.0 << " s. " << std::endl;
			std::cout << std::endl << " ---------------------" << std::endl << std::endl;
		}
		else if (timeNow - timeLast > 5000)
		{
			double timeRest = 1.0*(timeNow - timeStart)*(calcTime - i) / (1000 * i);
			std::cout << " " << i << " calculations completed , current progress : " << std::fixed << std::setprecision(3) << 100.0*i / calcTime << " % , ";
			std::cout << "time remaining estimated : " << (int)timeRest << " s" << std::endl;
			timeLast = timeNow;
		}
	}
}

void genetic::output()
{
	std::cout << "  »ï°éÐòºÅ  ";
	for (int i = 0; i < PartnerNum; i++)
	{
		std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl << "  ·ÖÅä¹Ø¿¨  ";
	for (int i = 0; i < PartnerNum; i++)
	{
		std::cout << std::setw(4) << this->bestAllot[i] + 1;
	}
	std::cout << std::endl << std::endl;

	std::cout << " ¹Ø¿¨ ·ÖÅä»ï°é" << std::endl;
	for (int j = 0; j < StageNum; j++) {
		std::cout << std::setw(5) << j + 1;
		for (int i = 0; i < PartnerNum; i++)
		{
			if (bestAllot[i] == j) {
				std::cout << std::setw(4) << i + 1;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Ìú¿ó = " << bestAllot[PartnerNum] / 5 << std::endl;
	std::cout << "Ä¾Í· = " << bestAllot[PartnerNum] << std::endl;
	std::cout << "½ð±Ò = " << bestAllot[PartnerNum + 1] << std::endl << std::endl;

}