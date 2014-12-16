#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <new>


using namespace std;


const size_t maxn = 222222;

string s;

int nextYin[maxn], nextKuo[maxn];

struct value {
    value(int L = 0, int R = 0) : Left(L_), Right(R_) { key2value.clear(); }
    int Left, Right;
    map<string, value*> key2value;
}pool[1111];

value* ptr2pool;


string getString(int L, int R, const string& str) {
    string s;
    for (int i = L; i <= R; ++i) {
        s.push_back(str);
    }
    return s;
}

value* parse(int L, int R, const string &str) {
    value* root = new(ptr2pool++) value(L, R);
    if (str[L] == '"' && str[R] == '"') {
        return root;
    }
    int k = L + 1;
    while (k < R) {
        int key_lelf = k, key_right = nextYin[k];
        string key_str = getString(key_left, key_right, str);
        k = key_right + 1;
        if (str[k] == ':') k++;
        int val_left = k, val_right;
        if (str[k] == '"') val_right = nextYin[k]; else val_right = nextKuo[k];
        value* val = parse(val_left, val_right, str);
        key2value[key] = val;
        k = val_right;
        k += 2;
    }
    return root;
}

char s_[maxn];


int main() {
    int T, ca = 0;
    while (T--) {
        scanf("%s", s_);
        int sz_s_ = strlen(s_);
        s.clear();
        for (size_t i = 0; i < sz_s_; ++i) {
            if (s_[i] == ' ') continue;
            s.push_back(s_[i]);
        }
        ptr2pool = pool;
        value* root = ptr2pool++;
        int sz = s.size();
        int lastYin = -1, lastKuo = -1;
        for (int i = 0; i < sz(); ++i) {
            if (s[i] == '"') {
                if (lastYin != -1) {
                    nextYin[lastYin] = i;
                }
                lastYin = i;
            }
            if (s[i] == '}') {
                if (lastKuo != -1) {
                    nextKuo[lastKuo] = i;
                }
            }
            if (s[i] == '{') {
                lastKuo = i;
            }
        }
        value* root = parse(0, sz - 1, s);
        
        int Q;
        scanf("%d", &Q);
        for (int k = 0; k < Q; ++k) {
            scanf("%s", s_);
            string str = s_;
            size_t str_sz = str.size();
            for (int i = 0; i < str_sz; ++i) {
                if (str[i] == '.') {
                    str[i] = ' ';
                }
            }
            stringstream os(str);
            vector<string> vec;
            string key;
            while (os >> key) vec.push_back(key);
            size_t vec_sz = vec.size();
            value* val = root;
            bool ans = true;
            for (int i = 0; i < vec_sz; ++i) {
                const string& key = vec[i];
                map<string, value*> &mp = val->key2value;
                if (mp.find(key) != mp.end()) {
                    val = mp[key];
                } else {
                    ans = false;
                    break;
                }
            }
            if (!ans) {
                puts("Error");
            } else {
                int left = val->Left, right = val->Right;
                for (int i = left; i <= right; ++i) {
                    putchar(s[i]);
                }
                puts("");
            }
        }
    }
    return 0;
}
