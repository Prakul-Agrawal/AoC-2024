//
// Created by Prakul Agrawal on 12/18/24.
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

void solve1() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    vvi grid(n, vi(m, 0));
    map<char, vpii> mp;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] != '.'){
                mp[v[i][j]].pb({i, j});
            }
        }
    }
    for(auto key : mp) {
        vpii val = key.ss;
        int len = sz(val);
        rep(i, 0, len) {
            rep(j, i+1, len) {
                pii p1 = val[i], p2 = val[j];
                int xDiff = p2.ff - p1.ff;
                int yDiff = p2.ss - p1.ss;
                pii a = {p1.ff - xDiff, p1.ss - yDiff};
                pii b = {p2.ff + xDiff, p2.ss + yDiff};
                if (a.ff >= 0 && a.ff < n && a.ss >= 0 && a.ss < m)
                    grid[a.ff][a.ss] = 1;
                if (b.ff >= 0 && b.ff < n && b.ss >= 0 && b.ss < m)
                    grid[b.ff][b.ss] = 1;
            }
        }
    }
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            ans += grid[i][j];
        }
    }
    cout << ans << endl;
}

void solve2() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    vvi grid(n, vi(m, 0));
    map<char, vpii> mp;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] != '.'){
                mp[v[i][j]].pb({i, j});
            }
        }
    }
    for(auto item : mp) {
        vpii val = item.ss;
        int len = sz(val);
        rep(i, 0, len) {
            rep(j, i+1, len) {
                pii p1 = val[i], p2 = val[j];
                int xDiff = p2.ff - p1.ff;
                int yDiff = p2.ss - p1.ss;
                while (true){
                    pii a = {p1.ff - xDiff, p1.ss - yDiff};
                    if (a.ff < 0 || a.ff >= n || a.ss < 0 || a.ss >= m)
                        break;
                    grid[a.ff][a.ss] = 1;
                    p1 = a;
                }
                while (true){
                    pii b = {p2.ff + xDiff, p2.ss + yDiff};
                    if (b.ff < 0 || b.ff >= n || b.ss < 0 || b.ss >= m)
                        break;
                    grid[b.ff][b.ss] = 1;
                    p2 = b;
                }
            }
        }
    }
    for(auto item : mp){
        if (sz(item.ss) > 1)
            for(auto [x,y] : item.ss){
                grid[x][y] = 1;
            }
    }
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            ans += grid[i][j];
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0); // To increase input-output speed
    cin.tie(0);
    solve1();
    solve2();
}