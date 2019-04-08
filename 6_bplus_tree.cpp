#include <iostream>
#include "football.h"
#include "BstBPlus.h"

using namespace BST;
using namespace std;

#include <algorithm>
#include <random>
#include <string>

int main()
{
	Football f("../data.csv");
	BPlus < Player, 3 > tree;
	for (int i = 0; i < f.players.size(); ++i)
		tree.insert(*f.players[i]);
	tree.print();
	while (true)
	{
		string name;
		getline(cin, name);
		if (name.empty())
			break;
		Player query(name);
		Player result("");
		if (tree.find(query, result))
			cout << result.name << ' ' << result.team->name;
		else
			cout << "Not found";
	}
	return 0;
}