#include <iostream>
#include <random>
#include <set>
#include <ctime>
#include <algorithm>
#include "football.h"

using namespace std;

template < class T >
class PerfectHash
{
private:
	hash < T > first_hasher;
	vector < hash < T > > second_hashers;
	vector < vector < size_t > > hashes;
public:
	PerfectHash(vector < T > init, unsigned int m) : first_hasher(hash < T >(m))
	{
		vector < vector < T > > buckets(m);
		for (T el: init)
			buckets[first_hasher(el)].push_back(el);
		default_random_engine generator(time(0));
		size_t counter = 1, failed_attempts = 0;
		for (int i = 0; i < m; ++i)
		{
			uniform_int_distribution < int > distribution(0, first_hasher.p - 1);
			vector < T > bucket = buckets[i];
			unsigned mj = bucket.size()*bucket.size();
			hashes.push_back(vector < size_t >(mj));
			while(true)
			{
				fill(hashes[i].begin(), hashes[i].end(), 0);
				int a = distribution(generator), b = distribution(generator);
				hash < T > second_hasher(mj, a, b);
				size_t temporal_counter = counter;
				bool flag = true;
				for (T el: bucket)
				{
					size_t temporal_hash = second_hasher(el);
					if (hashes[i][temporal_hash])
						flag = false;
					hashes[i][temporal_hash] = temporal_counter++;
				}
				if(flag)
				{
					second_hashers.push_back(second_hasher);
					counter = temporal_counter;
					break;
				}
				else
					++failed_attempts;
			}
		}
		cout << "Failed attempts: " << failed_attempts << endl;
	}
	size_t operator()(const T obj) const
	{
		size_t first_hash = first_hasher(obj);
		size_t second_hash = second_hashers[first_hash](obj);
		return hashes[first_hash][second_hash] - 1;
	}
};

int main()
{
	Football f;
	cout << "Players: " << f.players.size() << endl;
	PerfectHash < Player * > ph(f.players, 10);
	vector <size_t> phs;
	for (Player *player: f.players)
	{
		cout << "Name: " << player->name << ", hash: " << ph(player) << endl;
		phs.push_back(ph(player));
	}
	sort(phs.begin(), phs.end());
	cout << "All hashes: " << endl;
	for(auto it: phs)
		cout << it << ' ';
	return 0;
}