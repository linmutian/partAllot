#pragma once

const int StageNum = 18; // 关卡数
const int PartnerNum = 12;  // 小伙伴数量
const int PopulationNum = 300; // 种群数量
const int KingNum = 4; //必须是偶数！！
const double varianceRatio = 0.05; // 变异率
const double crossRatio = 0.8; // 交叉率

class population
{
public:
	population(int[PartnerNum]);

	void init();
	void eval();
	void select();
	void crossOver(int, int);
	void cross();
	void variance();
	void evolution(int incomeThreshold =1000);

	int calcIncome(int partnerAllot[PartnerNum + 2]);
	void setPartnerGHF(int [PartnerNum]);
	int maxWoodIncome;
	int king[PartnerNum];

private:
	/*
	pol 即种群 ，个体pol[i]的编码为:
	pol[i][0~11]为分配关卡;
	pol[i][12]为对应总木头收益;
	pol[i][13]为对应总金币收益.
	*/
	int **pop = new int*[PopulationNum];
	int partGFH[PartnerNum]; // 伙伴的攻防和

	int stageGFH[StageNum]= // 关卡所需攻防和
	{ 350,900,1200,2200,2800,4000,4800,8000,9000,10000,11000,20000,22000,23000,25000,35000,51000,54000 };
	int stageIncomeWood[StageNum] = // 关卡木头收益
	{ 300,600,900,1200,1500,1800,2100,2400,2700,3000,3300,3600,3900,4200,4500,4800,5100,5400 };
	int stageIncomeCoin[StageNum] = // 关卡金币收益
	{ 289716,442332,464316,508548,552780,575028,619260,663492,
		773940,884652,995112,1106076,1217304,1328532,1439760,1550988,1662216,1773444 };
};