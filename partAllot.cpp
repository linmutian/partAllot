#include <genetic.h>
#include <iostream>
#include <windows.h>

using namespace std;

void printInfo();

int main()
{
	SetConsoleTitle(L"小伙伴去哪儿 控制台版 Ver C1.03 by 林木甜");
	printInfo();
	
	bool notValid = false;
	int GFH[PartnerNum] = { 0 };
	int calcTime;

	// 输入攻防和
	do
	{
		//notValid = false;
		cout << endl << " 请依次输入小伙伴的攻防和,以空格/英文逗号隔开：" << endl << " ";
		for (int i = 0; i < PartnerNum; i++)
		{
			cin >> GFH[i]; cin.ignore(1, ', ');
			if (cin.fail())
			{
				cout << " 无效字符！程序将会退出！" << endl;
				system("pause");
				return 0;
			}
			if (GFH[i] <= 0)
				notValid = true;
		}
		if (notValid)
		{
			cout << " 请确保所有输入数据大于0并重新输入！" << endl << endl;
		}
	} while (notValid);
	cout << endl << " ---------------------" << endl << endl;

	// 输入计算次数
	cout << " （计算次数越多，越容易得到最优解，也越耗时，建议次数为400~1500次）" << endl;
	cout << " 请输入计算次数：";
	cin >> calcTime;
	if (cin.fail())
	{
		cout << " 无效字符！程序将会退出！" << endl;
		system("pause");
		return 0;
	}

	else if (calcTime < 100) {
		cout << endl << " ---------------------" << endl << endl;
		cout << " 次数过少，自动修正至100次，请耐心等待！（每10秒将更新进度）" << endl << endl;
	}
	else {
		cout << endl << " ---------------------" << endl << endl;
		cout << " 输入成功，请耐心等待！（每5秒将更新进度）" << endl << endl;
	}

	genetic g(calcTime);
	g.setGFH(GFH);
	g.evolution();
	g.output();
	system("pause");
	return 0;
}

void printInfo()
{
	cout << endl;
	cout << " ┌────────────────────────────────────────────────────────────────────────┐" << endl;
	cout << " │    本工具为召唤与合成的探索分配而写，目的是获得最大的铁矿/木头收益。   │ " << endl;
	cout << " │    采用算法为遗传算法，不能保证一定为最优解，如程序存在问题，可往taptap│ " << endl;
	cout << " │ 论坛或i/t群向我反馈。                                                  │ " << endl;
	cout << " │    原则上控制台版不再有后续的功能性更新（如果bug会继续修），qt版功能会 │ " << endl;
	cout << " │ 逐步增加。                         —— 林木甜  updated on 2020.3.11   │ " << endl;
	cout << " └────────────────────────────────────────────────────────────────────────┘ " << endl;
}