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
int main() {
    i64 n, k;
    cin >> n >> k;
    vector<int> a(n);
    if(k * 2 > n) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> used(n, 0);
    vector<int> ans(n, -1);
    rep(i, n) {
        if(i + k < n) {
            ans[i] = i + k;
            used[i + k] = 1;
        }else break;
    }
    int j = 0;
    // cout << "ans : " << ans << endl;
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1)
            continue;
        while(j < n and (used[j] == 1 or abs(j - i) < k)) j++;
        if (j >= n) {
            // cout << "j : " << j << " break!!!" <<  endl;
            break;
        }
        // cout << "i : " << i << endl;
        // cout << "j : " << j  <<  endl;
        ans[i] = j;
        used[j] = 1;
        // cout << "ans : " << ans << endl;
    }
    for(auto & i : ans)
        i++;
    cout << ans << endl;
    return 0;
}