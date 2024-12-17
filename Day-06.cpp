//
// Created by Prakul Agrawal on 12/17/24.
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
    pii start;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] != '.' && v[i][j] != '#') {
                start = {i, j};
                break;
            }
        }
    }
    vvi grid(n, vi(m, 0));
    int x = start.ff, y = start.ss;
    map<char, int> mp = {{'^', 1}, {'v', 3}, {'<', 0}, {'>', 2}};
    map<int, pii> dir = {{1, {-1, 0}}, {3, {1, 0}},
                          {0, {0, -1}}, {2, {0, 1}}};
    int curr = mp[v[x][y]];
    while(true) {
        grid[x][y] = 1;
        int tempX = x + dir[curr].ff, tempY = y + dir[curr].ss;
        if (tempX < 0 || tempX >= n || tempY < 0 || tempY >= m) {
            break;
        }
        if (v[tempX][tempY] == '#'){
            curr = (curr + 1) % 4;
        }
        else{
            x = tempX;
            y = tempY;
        }
    }
    ll ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == 1) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}

// inefficient solution
void solve2() {
    string s = readFile("input.txt");
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    pii start;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] != '.' && v[i][j] != '#') {
                start = {i, j};
                break;
            }
        }
    }
    vvi grid(n, vi(m, 0));
    int x = start.ff, y = start.ss;
    map<char, int> mp = {{'^', 1}, {'v', 3}, {'<', 0}, {'>', 2}};
    map<int, pii> dir = {{1, {-1, 0}}, {3, {1, 0}},
                         {0, {0, -1}}, {2, {0, 1}}};
    int curr = mp[v[x][y]];
    while(true) {
        grid[x][y] = 1;
        int tempX = x + dir[curr].ff, tempY = y + dir[curr].ss;
        if (tempX < 0 || tempX >= n || tempY < 0 || tempY >= m) {
            break;
        }
        if (v[tempX][tempY] == '#'){
            curr = (curr + 1) % 4;
        }
        else{
            x = tempX;
            y = tempY;
        }
    }
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == 1 && v[i][j] == '.') {
                v[i][j] = '#';
                x = start.ff, y = start.ss;
                curr = mp[v[x][y]];
                set<pair<int, pii>> vis;
                int flag = 0;
                while(true) {
                    if (vis.find({curr, {x, y}}) != vis.end()) {
                        flag = 1;
                        break;
                    }
                    vis.insert({curr, {x, y}});
                    int tempX = x + dir[curr].ff, tempY = y + dir[curr].ss;
                    if (tempX < 0 || tempX >= n || tempY < 0 || tempY >= m) {
                        break;
                    }
                    if (v[tempX][tempY] == '#'){
                        curr = (curr + 1) % 4;
                    }
                    else{
                        x = tempX;
                        y = tempY;
                    }
                }
                ans += flag;
                v[i][j] = '.';
            }
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