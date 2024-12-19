#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
// const int INF = 2e5 + 10;
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
        int n, t;
        cin >> n >> t;
        vector<vector<pair<int, int>>>adj (n + 1);
        for (int i = 1; i <= t; i++){
            int m;
            cin >> m; 
            for (int j = 1; j <= m; j++){
                int p, q;
                cin >> p >> q;
                adj[p].emplace_back(q ,i);
                adj[q].emplace_back(p, i);
            }
        }

        int k; 
        cin >> k;
        vector<vector<int>> a(t + 1);
        for (int i = 1; i <= k; i++){
            int val;
            cin >> val;
            a[val].push_back(i);
        }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q; 
    q.emplace(0, 1);
    vector<int> dis(n + 1, -1);
        
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (dis[u] != -1) continue;
        dis[u] = d;
        for (auto [v, t] : adj[u]){
            auto it = upper_bound(a[t].begin(), a[t].end(), dis[u]);
            if (it != a[t].end()) q.emplace(*it, v);
        }
    }
    // dbg(dis);
    std::cout << dis[n];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
