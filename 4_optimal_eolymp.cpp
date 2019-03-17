#include <iostream>

using namespace std;

const int MAX = 251, INF = 1e9 + 1;

int in[MAX], prf[MAX], dp[MAX][MAX];

int sum(int l, int r)
{
	return prf[r] - prf[l - 1];
}

int main()
{
	int n;
	while (cin >> n)
	{
		for (int i = 1; i <= n; ++i)
		{
			cin >> in[i];
			prf[i] = prf[i - 1] + in[i];
		}
		for (int len = 1; len <= n; ++len)
			for (int start = 1; start <= n - len + 1; ++start)
			{
				int end = start + len - 1;
				dp[start][end] = INF;
				for (int mid = start; mid <= end; ++mid)
					dp[start][end] = min(dp[start][end], dp[start][mid - 1] + dp[mid + 1][end] + sum(start, mid - 1) + sum(mid + 1, end));
			}
		cout << dp[1][n] << endl;
	}
	return 0;
}