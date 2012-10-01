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

#define si_b 128

using namespace std;

const long long MOD = 1e9 + 7;


struct state
{
	bitset<si_b> mask;
	state() {};
	state(int a) {mask.set(a);};
	//state(bitset<128> a): mask(a) {};
	bool operator<(const state & b) const
	{
		return (this->mask.to_string() < b.mask.to_string());
	}
};


int main()
{
	freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);
	int n, m, k, len;
	cin >> n >> m >> k >> len;
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

	map<state, int> new_nodes;
	new_nodes[state(0)] = 0;
	queue<state> q;
	q.push(state(0));
	vector<int> in, out;
	set<int> new_terminals;
	int new_size = 1;
	if (terminals.count(0) == 1) new_terminals.insert(0);

	while (!q.empty())
	{
		state cur_state = q.front(); q.pop();
		for (int c = 0; c < 26; c++)
		{
			state new_state;
			bool is_terminal = false;
			for (int i = 0; i < n; i++)
			{
				if (!cur_state.mask[i]) continue;
				for (int j = 0; j < go[i][c].size(); j++)
				{
					int t = go[i][c][j];
					new_state.mask[t] = true;
					is_terminal |= terminals.count(t); 
				}
			}
			if (new_nodes.count(new_state) == 0)
			{
				if (is_terminal) new_terminals.insert(new_size);
				new_nodes[new_state] = new_size++;
				q.push(new_state);	
			}
			in.push_back(new_nodes[cur_state]);
			out.push_back(new_nodes[new_state]);
		}
	}

	n = new_size;
	if (n > 100) return 666;
	m = in.size();
	terminals = new_terminals;

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
	cout << ans[0] << endl;
}