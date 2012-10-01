#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

const long long MOD = 1e9 + 7; 

int main()
{
	freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);
	
	int n, m, k, len;
	cin >> n >> m >> k >> len;
	
	set<int> terminals;
	for (int i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		terminals.insert(x - 1);
	}
	
	vector<int> in(m), out(m);
	for (int i = 0; i < m; i++)
	{
		char c;
		cin >> in[i] >> out[i]>> c;
		in[i]--, out[i]--;
	}
	
	vector<long long> ans(n);
	for (int i = 0; i < n; i++)
		ans[i] = terminals.count(i);

	for (int i = 0; i < len; i++)
	{
		vector<long long> cur(n) ;
		for (int j = 0; j < m; j++)
		{
			cur[in[j]] += ans[out[j]];
			cur[in[j]] %= MOD;
		}
		ans = cur;
	}
	/*long long answer = 0;
	for (int i = 0; i < n; i++)
		answer += ans[i] * terminals.count(i);*/
	cout << ans[0] << endl;
}