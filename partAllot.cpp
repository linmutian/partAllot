#include <genetic.h>
using namespace std;

int main()
{
	genetic g(1000);
	//int GFH[] = { 17214,16056,18554,17518,10566,10218,9678,9624,9232,7056,6806,6730 };
	//g.setGFH(GFH);
	g.evolution();
    return 0;
}