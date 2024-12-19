// https://codeforces.com/contest/1873/problem/H
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
    int n, a, b;
    cin >> n >> a >> b;
    vector<vector<int>> adj (n + 1);
    for (int i = 0; i < n; i++){
        int p, q;
        cin >> p >> q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }

    vector<int> disA(n + 1, -1); 
    vector<int> disB(n + 1, -1); 

    // Find the closest point k from b to the circle. 
    int k = -1;
    vector<bool> visit (n + 1, false); 
    auto dfs = [&](auto self, int u, int p) -> void {
        if (k != -1) return; 
        if (visit[u]){
            k = u;
            return;
        }
        visit[u] = true;
        for (auto v : adj[u]) 
            if (v != p) self(self, v, u);
    };

    dfs(dfs, b, -1);

    auto bfs = [&](int s){
        vector<int> dis(n + 1, -1);
        queue<int> q; 
        q.push(s);
        dis[s] = 0;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (auto v : adj[u]){
                if (dis[v] != -1) continue;
                dis[v] = dis[u] + 1; 
                q.push(v);
            }
        }
        return dis;
    };

    disA = bfs(a);
    disB = bfs(b);

    // dbg(disA);
    // dbg(disB);
    // std::cout << k;
    std::cout << (disB[k] < disA[k] ? "YES\n" : "NO\n");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin >> T;
    while (T--){
        solve();
    }
}
