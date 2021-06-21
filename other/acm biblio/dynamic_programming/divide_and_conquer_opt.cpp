#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll n, k, x[1005], w[1005], dp[1005][1005], cost[1005][1005];

void solve(int lo, int hi, int optL, int optR, int k)
{
	if (lo > hi)
		return;

	int m = (lo + hi) / 2, opt;
	for (int i = optL; i <= min(optR, m); ++i)
		if (dp[k - 1][i] + cost[i + 1][m] < dp[k][m])
		{
			dp[k][m] = dp[k - 1][i] + cost[i + 1][m];
			opt = i;
		}

	solve(lo, m - 1, optL, opt, k);
	solve(m + 1, hi, opt, optR, k);
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	while (cin >> n >> k)
	{
		for (int i = 1; i <= n; ++i)
			cin >> x[i] >> w[i];

		memset(cost, 0, sizeof cost);
		memset(dp, 63, sizeof dp);

		for (int i = 1; i <= n; ++i)
		{
			for (int j = i - 1; j; --j)
				cost[j][i] = cost[j + 1][i] + (x[i] - x[j]) * w[j];
			dp[1][i] = cost[1][i];
		}

		for (int i = 2; i <= k; ++i)
			solve(1, n, 1, n, i);

		cout << dp[k][n] << "\n";
	}

	return 0;
}
