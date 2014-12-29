#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

class NewZealand {
public:
	vector<int> Main(const vector<string>&, int, int, const vector<int>&);
private:
	void DP(const vector<string>&);
	vector<int> GetAns(const vector<int>&);
	vector<vector<int> > max_size_;
	int n_, m_;
};

vector<int> NewZealand::Main(const vector<string>& mp,int n, int m, const vector<int>& p) {
	n_ = n;
	m_ = m;
	DP(mp);
	return GetAns(p);
}	

void NewZealand::DP(const vector<string>& mp) {
	int n = n_, m = m_;
	max_size_.assign(n + 3, vector<int>(m + 3, 0));
	for(int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mp[i - 1][j - 1] == '0') continue;
			max_size_[i][j] = min(min(max_size_[i - 1][j],
										max_size_[i][j - 1]),
										max_size_[i - 1][j - 1]) + 1;
		}
	}
}

vector<int> NewZealand::GetAns(const vector<int>& p) {
	int n = n_, m = m_;
	vector<int> sz(min(n, m) + 3, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			sz[max_size_[i][j]]++; 
		}
	}
	for (int i = min(n, m); i >= 0; --i) {
		sz[i] = sz[i + 1] + sz[i];
	}
	vector<int> ans;
	for (int i = 0; i < p.size(); ++i) {
		if (p[i] > min(n, m)) 
			ans.push_back(0);	
		else ans.push_back(sz[p[i]]);
	}
	return ans;
}


int main() {
    freopen("in.txt", "r", stdin);
	int n, m, P;
	string str;
	NewZealand* nz = new NewZealand();
	while (cin >> n >> m >> P) {
		vector<string> vec_str;
		for (int i = 0; i < n; ++i) {
			cin >> str;
			vec_str.push_back(str);
		}
		vector<int> p;
		for (int i = 0; i < P; ++i) {
			int val;
			cin >> val;
			p.push_back(val);
		}
		
		vector<int> ans = nz->Main(vec_str, n, m, p);
		for (int i = 0; i < ans.size(); ++i) {
			printf("%d\n", ans[i]);
		}
	}
}

