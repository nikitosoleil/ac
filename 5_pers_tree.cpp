#include <iostream>
#include "football.h"
#include "BstRbtPers.h"

using namespace BST;
using namespace std;

#include <algorithm>
#include <random>

int main()
{
	Football f("../data.csv");
	RBT < Player > rbt;
	for (Player *p: f.players)
		rbt.insert(*p);
	for (int i = 0; i < f.players.size(); ++i)
		cout << rbt.size(i) << ' ';
	cout << endl;

	while (true)
	{
		int num;
		cin >> num;
		if (num < 0)
			break;
		rbt.print(num);
	}

	return 0;
}