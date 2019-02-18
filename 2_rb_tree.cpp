#include <iostream>
#include "football.h"
#include "BstRbt.h"

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
	while (true)
	{
		int num;
		cin >> num;
		if(num < 0)
			break;
		Player p("");
		if (rbt.order(num, p))
			cout << p.name << ' ' << p.team->name;
		else
			cout << "Not found";
	}
	return 0;
}