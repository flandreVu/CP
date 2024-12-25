//https://codeforces.com/contest/2041/problem/D
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int INF = 1e9;
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

// DOWN, UP, LEFT, RIGHT
int cx[] = {-1, 1, 0, 0};
int cy[] = {0, 0, -1, 1};

class Node {
    // dir: lastest direction, cnt: number of dir 
    public:
        int x, y, dis = 0, cnt = 0, dir = -1;
        Node(int x, int y, int dis, int cnt, int dir) : x(x), y(y), dis(dis), cnt(cnt), dir(dir){};
        bool operator>(const Node& _) const{
            if(this->dis != _.dis) return this->dis > _.dis;
            else return this->cnt > _.cnt;
        }
};


void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    int sx, sy, tx, ty; 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 'S'){
                sx = i;
                sy = j;
            } else if (a[i][j] == 'T'){
                tx = i;
                ty = j;
            }
        }

    priority_queue<Node, vector<Node>, greater<>> q; 
    q.emplace(sx, sy, 0, 0, -1);
    vector<vector<vector<int>>> d(n + 1, vector<vector<int>>(m + 1, vector<int>(4, -1))); 

    while (!q.empty()){
        auto [x, y, dis, cnt, dir] = q.top();
        q.pop();
        if (dir != -1 && d[x][y][dir] != -1) continue;
        if (dir != -1) d[x][y][dir] = dis;
        for (int i = 0; i < 4; i++){
            int nx = x + cx[i];
            int ny = y + cy[i];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m || a[nx][ny] == '#') continue;
            if (i == dir){
                if (cnt == 3) q.emplace(nx, ny, dis + 3, 2, i); 
                else q.emplace(nx, ny, dis + 1, cnt + 1, i);
            } else q.emplace(nx, ny, dis + 1, 1, i); 
        }
    }

    int ans = INF;
    for (auto i : d[tx][ty]) if (i != -1) ans = min(ans, i);
    std::cout << (ans == INF ? -1 : ans);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
