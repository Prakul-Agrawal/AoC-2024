//
// Created by Prakul Agrawal on 12/22/24.
//

#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF 1e18
typedef long long ll;
//#define int long long;
typedef long double ldb;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<pli> vpli;
typedef vector<pil> vpil;
typedef vector<vpii> vvpii;
typedef vector<vpll> vvpll;
typedef vector<vpli> vvpli;
typedef vector<vpil> vvpil;
#define ff first
#define ss second
#define pb push_back
#define endl '\n'
#define all(s) s.begin(), s.end()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define tc int t; cin>>t; while(t--)
#define printcase int t; cin>>t; for(int i=1;i<=t;i++){cout<<"Case #"<<i<<": ";solve();}
#define max_heap(x) priority_queue<x>
#define min_heap(x) priority_queue<x, vector<x>, greater<x>>

string readFile(string filename) {
    ifstream file(filename);
    string s;
    string line;
    while (getline(file, line)) {
        s += line + "\n";
    }
    return s;
}

void updateSet(set<pii> &curr, set<pii> &next, int n, int m, vvi &grid, int val){
    vpii dir = {{1,0},{-1,0},{0,1},{0,-1}};
    for(auto [x,y] : curr){
        for(auto [dx,dy] : dir){
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == val + 1){
                next.insert({nx,ny});
            }
        }
    }
    curr = next;
    next.clear();
}

void solve1(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vvi grid;
    while (getline(iss, line)) {
        vi temp;
        for(auto c : line){
            temp.pb(c - '0');
        }
        grid.pb(temp);
    }
    ll ans = 0;
    int n = sz(grid), m = sz(grid[0]);
    rep(i,0,n){
        rep(j,0,m){
            if (grid[i][j] == 0){
                set<pii> curr = {{i,j}}, next;
                rep(val,0,9){
                    updateSet(curr, next, n, m, grid, val);
                }
                ans += sz(curr);
            }
        }
    }
    cout << ans << endl;
}

void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vvi grid;
    while (getline(iss, line)) {
        vi temp;
        for(auto c : line){
            temp.pb(c - '0');
        }
        grid.pb(temp);
    }
    ll ans = 0;
    int n = sz(grid), m = sz(grid[0]);
    map<int,vpii> mp;
    rep(i,0,n){
        rep(j,0,m){
            mp[grid[i][j]].pb({i,j});
        }
    }
    vvl dp(n, vl(m, 0));
    for(auto [x,y] : mp[9]){
        dp[x][y] = 1;
    }
    for(int i = 8; i >= 0; i--){
        vpii dir = {{1,0},{-1,0},{0,1},{0,-1}};
        for(auto [x,y] : mp[i]){
            for(auto [dx,dy] : dir){
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == i + 1){
                    dp[x][y] += dp[nx][ny];
                }
            }
        }
    }
    for(auto [x,y] : mp[0]){
        ans += dp[x][y];
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename);
    solve2(filename);
}