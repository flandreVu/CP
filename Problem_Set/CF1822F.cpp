//https://codeforces.com/contest/1822/problem/F
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
    int n, k, c;
    cin >> n >> k >> c;
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++){
        int p, q;
        cin >> p >> q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    
    auto bfs = [&](int s){
        vector<int> dis (n + 1, -1 ); 
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        int x = s;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (auto v : adj[u]) 
                if (dis[v] == -1){
                    q.push(v);
                    dis[v] = dis[u] + 1;
                    x = v;
                }
        }
        return make_tuple(dis, x);
    };

    // disR: distance to other nodes from root. 
    auto [disR, A] = bfs(1);
    auto [disA, B] = bfs(A); 
    auto disB = get<0>(bfs(B));

    // dbg(disR); 
    // dbg(disA);
    // dbg(disB);
    i64 ans = 1LL * disR[A] * k;
    for (int i = 1; i <= n; i++){
        i64 temp = 1LL * max(disA[i],disB[i]) * k - 1LL * disR[i] * c;
        ans = max(ans, temp);
    }
    std::cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
