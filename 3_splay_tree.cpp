#include <iostream>
#include "football.h"
#include "BstSplay.h"

using namespace BST;
using namespace std;

#include <algorithm>
#include <random>
#include <string>

int main()
{
	Football f("../data.csv");
	Splay < Player > tree;
	for (Player *p: f.players)
		tree.insert(*p);
	while (true)
	{
		string name;
		getline(cin, name);
		if(name.empty())
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