#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>

using namespace std;

int main()
{
	freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
    string s;
    cin >> s;
	int n, m, k;
	cin >> n >> m >> k;
	set<int> terminals;
	for (int i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		terminals.insert(x - 1);
	}
	vector< vector<int> > go(n, vector<int>(26, -1));
	for (int i = 0; i < m; i++)
	{
		int a, b;
		char c;
		cin >> a >> b >> c;
		go[a - 1][c - 'a'] = b - 1;
	}
	int cur = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (go[cur][s[i] - 'a'] == -1)
		{
			cout << "Rejects\n";
			return 0;
		}
		cur = go[cur][s[i] - 'a'];
	}
	if (terminals.count(cur) == 1)
		cout << "Accepts\n";
	else
		cout << "Rejects\n";
}