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

const i64 INF = 1e18;
i64 op(i64 a, i64 b) {
    return max(a, b);
}

i64 e() {
    return -INF;
}

int main() {
    int n, c;
    cin >> n >> c;
    vector<pair<i64, i64>> xv;
    rep(i, n) {
        i64 x, v;
        cin >> x >> v;
        xv.emplace_back(x, v);
    }
    vector<pair<i64, i64>> xv_rev = xv;
    reverse(all(xv_rev));
    for(auto & p : xv_rev) p.first = c - p.first;

    i64 ans = 0;

    vector<i64> val_sum(n), val_sum_rev(n);
    i64 sum = 0;
    for(int i = 0; i < n; i++) {
        sum += xv[i].second;
        val_sum[i] = sum - xv[i].first;
        chmax(ans, val_sum[i]);
    }

    sum = 0;
    for(int i = n - 1; i >= 0; i--) {
        sum += xv[i].second;
        val_sum_rev[i] = sum - xv[i].first;
        chmax(ans, val_sum_rev[i]);
    }

    segtree<i64, op, e> seg(val_sum_rev);
    rep(i, n) {
        seg.set(n - i - 1, 0);
        i64 now_ans = val_sum[i] - xv[i].first;
        now_ans += seg.all_prod();
        chmax(ans, now_ans);
    }

    segtree<i64, op, e> seg_rev(val_sum);
    rep(i, n) {
        seg_rev.set(n - i - 1, 0);
        i64 now_ans = val_sum_rev[i] - xv_rev[i].first;
        now_ans += seg_rev.all_prod();
        chmax(ans, now_ans);
    }

    cout << ans << endl;

    return 0;
}