#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>


using namespace std;

map<char, int> char2int;
map<int, char> int2char;

vector<int> getNext(const vector<int> &vec, int pos) {
	vector<int> v;
	v = vec;
	set<int> pre;
	for (int i = 0; i < pos; ++i) {
		if (pre.find(vec[i]) != pre.end()) {
			return vector<int> ();
		}
		pre.insert(vec[i]);
	}
	int sz = v.size();
	for (int num = vec[pos] + 1; num < 16; ++num) {
		if (pre.find(num) == pre.end()) {
			set<int> s = pre;
			s.insert(num);
			v[pos] = num;
			for (int i = pos + 1; i < sz; ++i) {
				for (int val = 0; val < 16; ++val) {
					if (s.find(val) == s.end()) {
						v[i] = val;
						s.insert(val);
						break;
					}
				}
			}
			return v;
		}
	}
	return vector<int>();

}





int main() {
	for (int i = 0; i < 10; ++i) {
		char2int[i + '0'] = i;
		int2char[i] = i + '0';
	}
	for (int i = 10; i < 16; ++i) {
		char2int[i - 10 + 'A'] = i;
		int2char[i] = i - 10 + 'A';
	}


	freopen("in.txt", "r", stdin);



	string s;
	while (cin >> s) {
		vector<int> vec;
		for (int i = 0; i < s.size(); ++i) {
			vec.push_back(char2int[s[i]]);
		}


			int sz = vec.size();
			int ansed = 0;
			vector<int> v;
			for (int pos = sz - 1; pos >= 0; --pos) {
				v = getNext(vec, pos);
				if (v.size() > 0) {
					ansed = 1;
					break;
				}
			}
			if (!ansed) {
				vector<int> vec0;
				vec0.push_back(0);
				for (int i = 0; i < sz; ++i) {
					vec0.push_back(vec[i]);
				}
				v = getNext(vec0, 0);
				ansed = 1;
			}
			string str;
			for (int i = 0; i < v.size(); ++i) {
				str.push_back(int2char[v[i]]);
			}
			cout << str << endl;
	}
	return 0;
}
