#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <iterator>
#include <bitset>
#include <queue>
#include <map>

using namespace std;

const long long MOD = 1e9 + 7;

enum color { WHITE, GREY, BLACK };

vector< vector<int> > go, rev;
set<int> terminals;

vector<color> colors;
vector<long long> ans;
bool ans_inf = false;

void init(int v)
{
	colors[v] = WHITE;
	for (int i = 0; i < rev[v].size(); i++)
	{
		int u = rev[v][i];
		if (colors[u] == BLACK) init(u);
	}
}

int calc(int v)
{
	switch (colors[v])
	{
	case BLACK:
		{
			return ans[v];
			break;
		}
	case GREY:
		{
			ans_inf = true;
			return 0;
			break;
		}
	default:
		break;
	}
	colors[v] = GREY;
	ans[v] = terminals.count(v);
	for (int c = 0; c < 26; c++) 
		ans[v] += calc(go[v][c]);
	while (ans[v] >= MOD) ans[v] -= MOD;
	colors[v] = BLACK;
	return ans[v];
}

int main()
{
	freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		terminals.insert(x - 1);
	}
	go = vector< vector<int> >(n + 1, vector<int>(26, n));
	rev.resize(n);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		char c;
		cin >> a >> b >> c;
		go[a - 1][c - 'a'] = b - 1;
		rev[b - 1].push_back(a - 1);
	}

	colors.assign(n  + 1, BLACK);
	ans.assign(n + 1, 0);
	for (int i = 0; i < n; i++)
		if (terminals.count(i)) init(i);

	long long answer = calc(0);
	cout << (ans_inf ? -1 : answer) << endl; 
}