#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include "football.h"

using namespace std;

const int MAX = 501, INF = 1e9 + 1;

int prf[MAX], dp[MAX][MAX], opt[MAX][MAX];

int sum(int l, int r)
{
	return prf[r] - prf[l - 1];
}

bool cmp(const Player *one, const Player *two)
{
	return (*one) <= (*two);
}

int main()
{
	Football f("../data.csv");
	sort(f.players.begin(), f.players.end(), cmp);
	int n = f.players.size();
	for (int i = 1; i <= n; ++i)
		prf[i] = prf[i - 1] + f.players[i - 1]->pop;
	for (int len = 1; len <= n; ++len)
		for (int start = 1; start <= n - len + 1; ++start)
		{
			int end = start + len - 1;
			dp[start][end] = INF;
			for (int mid = start; mid <= end; ++mid)
			{
				int upd = dp[start][mid - 1] + dp[mid + 1][end] + sum(start, mid - 1) + sum(mid + 1, end);
				if (upd < dp[start][end])
				{
					dp[start][end] = min(dp[start][end], upd);
					opt[start][end] = mid;
				}
			}
		}
	cout.precision(4);
	cout.setf(ios::fixed);
	float sum = 0;
	for(auto it: f.players)
		sum += it->pop;

	queue < pair < pair < int, int >, int > > que;
	que.push({{1, n}, 0});
	while (!que.empty())
	{
		int l = que.front().first.first, r = que.front().first.second, h = que.front().second;
		que.pop();
		if (l <= r)
		{
			int now = opt[l][r];
			Player *player = f.players[now-1];
			cout << setw(25) << player->name << setw(7) << player->pop/*/sum*/ << setw(3) << h
			     << setw(7) << player->pop/*/sum*/*h << setw(10) << dp[l][r] << endl;
			que.push({{l, now - 1}, h + 1});
			que.push({{now + 1, r}, h + 1});
		}
	}
	return 0;
}