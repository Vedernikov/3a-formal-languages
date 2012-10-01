#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

int main()
{
	freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);
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
	vector< vector< vector<int> > > go(n, vector< vector<int> >(26, vector<int>()));
	for (int i = 0; i < m; i++)
	{
		int a, b;
		char c;
		cin >> a >> b >> c;
		go[a - 1][c - 'a'].push_back(b - 1);
	}
	set<int> cur;
	cur.insert(0);
	for (int i = 0; i < s.length(); i++)
	{
		char cur_ch = s[i] - 'a';
		set<int> new_cur;
		for (set<int>::iterator it = cur.begin(); it != cur.end(); it++)
			for (int j = 0; j < go[*it][cur_ch].size(); j++)
				new_cur.insert(go[*it][cur_ch][j]);
		cur = new_cur;
	}
	bool ans = false;
	for (int i = 0; i < n; i++)
		if (cur.count(i) == 1 && terminals.count(i) == 1)ans = true;
	
	if (ans)
		cout << "Accepts\n";
	else
		cout << "Rejects\n";
}