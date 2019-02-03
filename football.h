#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Player;

struct Team
{
	string name;
	vector < Player * > players;
	Team(string n) : name(n) {}
};

struct Player
{
	string name;
	Team *team;
	Player(string n, Team *t) : name(n), team(t) {}
	bool operator==(const Player &p) const
	{
		return name == p.name;
	}
};

struct Football
{
	vector < Team * > teams;
	vector < Player * > players;
	Football()
	{
		ifstream data("../data.csv");
		string line, prv;
		Team *cur;
		while (getline(data, line, '\n'))
		{
			stringstream line_stream(line);
			string name, club;
			getline(line_stream, name, ',');
			getline(line_stream, club, ',');
			if (prv.length())
			{
				if (club != prv)
				{
					if (prv != "club")
						teams.push_back(cur);
					cur = new Team(club);
				}
				Player *player = new Player(name, cur);
				cur->players.push_back(player);
				players.push_back(player);
			}
			prv = club;
		}
		teams.push_back(cur);
	}
};

typedef long long ll;

namespace std
{
template <>
struct hash < Player * >
{
	static const size_t p = 2147483647; // 8th Mersenne prime
	ll m, a, b;
	hash < Player * >(int m, int a = 1, int b = 0) : m(m), a(a), b(b) {}
	size_t operator()(const Player *player) const
	{
		return size_t(((a*hash < string >()(player->name) + b)%p)%m);
	}
};
}
