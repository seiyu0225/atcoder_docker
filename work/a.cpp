#include <algorithm>
#include <iomanip>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <numeric>
#include <vector>
#include <climits>
using namespace std;
#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif
#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define _rep(i, n) _rep2(i, 0, n)
#define _rep2(i, a, b) for(int i = (int)(a); i < (int)(b); i++)
#define rep(...) GET_MACRO(__VA_ARGS__, _rep2, _rep)(__VA_ARGS__)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using i64 = long long;
template<class T, class U>
bool chmin(T& a, const U& b) { return (b < a) ? (a = b, true) : false; }
template<class T, class U>
bool chmax(T& a, const U& b) { return (b > a) ? (a = b, true) : false; }

template<typename T>istream& operator>>(istream&i,vector<T>&v){rep(j,v.size())i>>v[j];return i;}
template<typename T>string join(vector<T>&v){stringstream s;rep(i,v.size())s<<' '<<v[i];return s.str().substr(1);}
template<typename T>ostream& operator<<(ostream&o,vector<T>&v){if(v.size())o<<join(v);return o;}
template<typename T>string join(vector<vector<T>>&vv){string s="\n";rep(i,vv.size())s+=join(vv[i])+"\n";return s;}
template<typename T>ostream& operator<<(ostream&o,vector<vector<T>>&vv){if(vv.size())o<<join(vv);return o;}
template<class T> using pq = priority_queue<T, vector<T>, greater<T>>;


int main() {
    int n, m, e;
    cin >> n >> m >> e;

    vector<int> ul(e);
    vector<int> vl(e);

    rep(i, e) {
        cin >> ul[i] >> vl[i];
        ul[i]--;
        vl[i]--;
    }

    int q;
    cin >> q;
    vector<int> x(q);
    set<int> out;
    cin >> x;
    for(auto & i : x) i--;
    for(auto & i : x) out.insert(i);
    reverse(all(x));

    vector<int> ok(n + m, 0);
    rep(i, n, n + m) ok[i] = 1;
    vector<vector<int>> child(n + m);
    dsu d(n + m);
    rep(i, n + m) child[i].push_back(i);
    int ans = 0;
    rep(i, e) {
        // cout << "i : " << i << endl;
        if(out.count(i)) continue;
        int u = ul[i];
        int v = vl[i];
        // cout << "u : " << u << endl;
        // cout << "v : " << v << endl;
        if(ok[d.leader(u)] == 1 and ok[d.leader(v)] == 0) swap(u, v);
        if(ok[d.leader(u)] == 0 and ok[d.leader(v)] == 1) {
            for(auto j : child[d.leader(u)]) {
                ok[j] = 1;
                if(j < n) ans++;
            }
            vector<int> & vu = child[d.leader(u)];
            vector<int> & vv = child[d.leader(v)];
            if(vu.size() < vv.size()) swap(vu, vv);
            for(auto& j : vv) {
                vu.push_back(j);
            }
            d.merge(u, v);
            vv.clear();
            child[d.leader(u)] = vu;
        }else{
            if(d.leader(u) == d.leader(v)) continue;
            vector<int> & vu = child[d.leader(u)];
            vector<int> & vv = child[d.leader(v)];
            if(vu.size() < vv.size()) swap(vu, vv);
            for(auto& j : vv) {
                vu.push_back(j);
            }
            d.merge(u, v);
            vv.clear();
            child[d.leader(u)] = vu;
        }
    }
    vector<int> output;
    rep(qi, q) {
        // cout << "qi : " << qi << endl;
        output.push_back(ans);
        int i = x[qi];
        int u = ul[i];
        int v = vl[i];
        if(ok[d.leader(u)] == 1 and ok[d.leader(v)] == 0) swap(u, v);
        if(ok[d.leader(u)] == 0 and ok[d.leader(v)] == 1) {
            for(auto j : child[d.leader(u)]) {
                ok[j] = 1;
                if(j < n) ans++;
            }
            vector<int> & vu = child[d.leader(u)];
            vector<int> & vv = child[d.leader(v)];
            if(vu.size() < vv.size()) {
                swap(vu, vv);
            }
            for(auto& j : vv) {
                vu.push_back(j);
            }
            d.merge(u, v);
            vv.clear();
            child[d.leader(u)] = vu;
        }else{
            if(d.leader(u) == d.leader(v)) continue;
            vector<int> & vu = child[d.leader(u)];
            vector<int> & vv = child[d.leader(v)];
            if(vu.size() < vv.size()) swap(vu, vv);
            for(auto& j : vv) {
                vu.push_back(j);
            }
            d.merge(u, v);
            vv.clear();
            child[d.leader(u)] = vu;
        }
    }
    reverse(all(output));
    for(auto i : output) cout << i << endl;

    return 0;
}