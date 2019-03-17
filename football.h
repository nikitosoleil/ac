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
	int pop;
	Player(string n, Team *t = NULL, int p = 0) : name(n), team(t), pop(p) {}
	bool operator<(const Player &p) const
	{
		for (int i=0; i<min(name.length(), p.name.length()); ++i)
			if(name[i] != p.name[i])
				return name[i] < p.name[i];
		return name.length() < p.name.length();
	}
	bool operator<=(const Player &p) const
	{
		for (int i = 0; i < min(name.length(), p.name.length()); ++i)
			if (name[i] != p.name[i])
				return name[i] < p.name[i];
		return name.length() <= p.name.length();
	}
	bool operator>(const Player &p) const
	{
		for (int i = 0; i < min(name.length(), p.name.length()); ++i)
			if (name[i] != p.name[i])
				return name[i] > p.name[i];
		return name.length() > p.name.length();
	}
	bool operator==(const Player &p) const
	{
		return name.compare(p.name) == 0;
	}
};

struct Football
{
	vector < Team * > teams;
	vector < Player * > players;
	Football(string path)
	{
		ifstream data(path);
		string line, prv;
		Team *cur;
		while (getline(data, line, '\n'))
		{
			stringstream line_stream(line);
			string name, club, pop;
			getline(line_stream, name, ',');
			getline(line_stream, club, ',');
			for(int i=0; i<5; ++i) // age, position, cat, market_value, page_views
				getline(line_stream, pop, ',');
			if (prv.length())
			{
				if (club != prv)
				{
					if (prv != "club")
						teams.push_back(cur);
					cur = new Team(club);
				}
				Player *player = new Player(name, cur, stoi(pop));
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
