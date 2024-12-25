//https://codeforces.com/problemset/problem/1592/C
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

void solve(){
    int n, k;
    i64 val = 0;
    cin >> n >> k; 
    vector<i64> a(n);
    vector<i64> f(n);
    for (int i = 0; i < n; i++){
        cin >> a[i]; 
        f[i] = a[i];
        val ^= a[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++){
        int p, q;
        cin >> p >> q;
        p--; q--;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    
    vector<bool> visit(n, false);
    int cnt = 0;

    auto dfs = [&](auto self, int u) -> i64{
        if (visit[u] == true) return 0;
        visit[u] = true;
        for (auto v : adj[u]){
            f[u] ^= self(self, v);
        }
        if (f[u] == val){
            cnt++;
            f[u] = 0;
        }
        return f[u];
    };

    dfs(dfs, 0);
    if (val == 0) cnt++;

    if (cnt >= 2 && (k > 2 || val == 0)) cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}

