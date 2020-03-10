#include <population.h>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <time.h> 
#include <iostream>

bool sortFun(int arr1[PartnerNum+2], int arr2[PartnerNum + 2])
{
	if (arr1[PartnerNum] > arr2[PartnerNum])
		return true;
	else if (arr1[PartnerNum] = arr2[PartnerNum] && arr1[PartnerNum + 1] > arr2[PartnerNum + 1])
		return true;
	else
		return false;
}

int population::calcIncome(int partnerAllot[PartnerNum + 2])
{
	int woodIncome = 0;
	int coinIncome = 0;

	// 计算各关现有攻防和
	int GFHnow[StageNum] = { 0 };
	for (int i = 0; i < PartnerNum; i++)
	{
		int thisStage = partnerAllot[i];
		GFHnow[thisStage] += partGFH[i];
	}

	// 计算收益
	for (int i = 0; i < StageNum; i++)
	{
		if (GFHnow[i] > stageGFH[i])
		{
			woodIncome += stageIncomeWood[i];
			coinIncome += stageIncomeCoin[i];
		}
		else
		{
			woodIncome += int(1.0 * GFHnow[i] / stageGFH[i] * stageIncomeWood[i]);
			coinIncome += int(1.0 * GFHnow[i] / stageGFH[i] * stageIncomeCoin[i]);
		}
	}
	
	// pol[i][12~13] 填充
	partnerAllot[PartnerNum] = woodIncome;
	partnerAllot[PartnerNum+1] = coinIncome;
	return woodIncome;
}

population::population(int GFH[PartnerNum])
{
	srand((unsigned)time(NULL));
	setPartnerGHF(GFH);
	for (int i = 0; i < PopulationNum; i++)
	{
		pop[i] = new int[PartnerNum+2];
		for (int j = 0; j < PartnerNum; j++)
		{
			pop[i][j] = rand() % StageNum;
		}

	}

}

void population::setPartnerGHF(int GFH[PartnerNum])
{
	for (int i = 0; i < PartnerNum; i++)
	{
		partGFH[i] = GFH[i];
	}
}

void population::init(void)
{
	for (int i = 0; i < PopulationNum; i++)
	{
		for (int j = 0; j < PartnerNum; j++)
		{
			pop[i][j] = rand() % StageNum;
		}
	}
}

void population::eval(void)
{
	for (int i = 0; i < PopulationNum; i++)
	{
		calcIncome(pop[i]);
	}
	std::sort(pop, pop+PopulationNum, sortFun);
	maxWoodIncome = pop[0][12];
	for (int i = 0; i < PartnerNum; i++)
		king[i] = pop[0][i];
}

void population::select(void)
{
	// 复制数据
	int tempPop[PopulationNum][PartnerNum];
	for (int i = 0; i < PopulationNum; i++)
	{
		for (int j = 0; j < PartnerNum; j++)
		{
			tempPop[i][j] = pop[i][j];
		}
	}
	
	//赌轮盘
	double wheel[PopulationNum];
	for (int i = 0; i < PopulationNum; i++)
	{
		if (i == 0)
			wheel[i] = pop[0][12];
		else
		{
			wheel[i] = wheel[i - 1] + pop[i][12];
		}
	}
	double maxScale = wheel[PopulationNum - 1]; // 轮盘的最大刻度

	// king
	for (int i = 0; i < KingNum; i++)
	{
		for (int j = 0; j < PartnerNum; j++)
		{
			pop[i][j] = tempPop[0][j];
		}	
	}
	//其它，赌轮盘
	for (int i = KingNum; i < PopulationNum; i++)
	{
		double pointer = rand()*1.0 / UINT_MAX * maxScale;
		int k = 0;
		while (pointer > wheel[k])
		{
			k++;
		}
		for (int j = 0; j < PartnerNum; j++)
		{
			pop[i][j] = tempPop[k][j];
		}
	}
}

void population::crossOver(int m, int n)
{
	int breakpoint = rand() % PartnerNum;
	for (int j = breakpoint; j < PartnerNum; j++)
	{
		int temp = pop[m][j];
		pop[m][j] = pop[n][j];
		pop[n][j] = temp;
	}
}

void population::cross()
{
	for (int i = KingNum / 2; i < PopulationNum / 2; i++)
	{
		if (rand() / double(RAND_MAX) < crossRatio)
		{
			crossOver(2 * i, 2 * i + 1);
		}
	}
}

void population::variance()
{
	for (int i = 0; i < PopulationNum; i++)
	{
		if (rand() / double(RAND_MAX) < varianceRatio)
		{
			int locus = rand() % PartnerNum;
			int aimValue = rand() % StageNum;
			pop[i][locus] = aimValue;
		}
	}
}

void population::evolution(int incomeThreshold)
{
	int time = 0;
	int sameTime = 0; 
	int maxSameTime = 100;
	int maxIncomeLast = 0;

	init();
	eval();
	for (int i = 0; i < 3000 && sameTime < maxSameTime; i++)
	{
		if (i == 1000 && maxWoodIncome < incomeThreshold)
			break;
		maxIncomeLast = maxWoodIncome;

		select();
		cross();
		variance();
		eval();

		if (maxIncomeLast == maxWoodIncome) 
		{
			sameTime++;
		}
		else
		{
			sameTime = 0;
		}
		time++;
	}
	//std::cout << " Max wood income = " << maxWoodIncome << "   Calc time:" << time << std::endl;
}
