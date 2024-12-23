//
// Created by Prakul Agrawal on 12/23/24.
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

void solve1(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    vvi vis(n, vi(m, 0));
    ll ans = 0;
    vpii dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (!vis[i][j]){
                char let = v[i][j];
                queue<pii> q;
                q.push({i, j});
                vis[i][j] = 1;
                ll area = 0, peri = 0;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    area++;
                    for (auto [dx, dy] : dir) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                            peri++;
                        } else if (v[nx][ny] != let) {
                            peri++;
                        } else if (!vis[nx][ny]) {
                            vis[nx][ny] = 1;
                            q.push({nx, ny});
                        }
                    }
                }
                ans += area * peri;
            }
        }
    }
    cout << ans << endl;
}

void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    vvi vis(n, vi(m, 0));
    ll ans = 0;
    vpii dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (!vis[i][j]){
                char let = v[i][j];
                queue<pii> q;
                q.push({i, j});
                vis[i][j] = 1;
                map<int, set<int>> rows, cols;
                ll area = 0, sides = 0;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    rows[x].insert(y);
                    cols[y].insert(x);
                    area++;
                    for (auto [dx, dy] : dir) {
                        int nx = x + dx, ny = y + dy;
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                            continue;
                        } else if (v[nx][ny] != let) {
                            continue;
                        } else if (!vis[nx][ny]) {
                            vis[nx][ny] = 1;
                            q.push({nx, ny});
                        }
                    }
                }
                for (auto [x, ys] : rows) {
                    int flagUp = 0, flagDown = 0;
                    int uX = x - 1, dX = x + 1;
                    int prevY = *ys.begin() - 1;
                    for(auto y : ys) {
                        if (prevY != y - 1) {
                            flagUp = 0;
                            flagDown = 0;
                        }
                        if (uX < 0 || v[uX][y] != let) {
                            if (flagUp == 0){
                                sides++;
                                flagUp = 1;
                            }
                        }
                        else {
                            flagUp = 0;
                        }
                        if (dX >= n || v[dX][y] != let) {
                            if (flagDown == 0){
                                sides++;
                                flagDown = 1;
                            }
                        }
                        else {
                            flagDown = 0;
                        }
                        prevY = y;
                    }
                }
                for (auto [y, xs] : cols) {
                    int flagLeft = 0, flagRight = 0;
                    int lY = y - 1, rY = y + 1;
                    int prevX = *xs.begin() - 1;
                    for(auto x : xs) {
                        if (prevX != x - 1) {
                            flagLeft = 0;
                            flagRight = 0;
                        }
                        if (lY < 0 || v[x][lY] != let) {
                            if (flagLeft == 0){
                                sides++;
                                flagLeft = 1;
                            }
                        }
                        else {
                            flagLeft = 0;
                        }
                        if (rY >= m || v[x][rY] != let) {
                            if (flagRight == 0){
                                sides++;
                                flagRight = 1;
                            }
                        }
                        else {
                            flagRight = 0;
                        }
                        prevX = x;
                    }
                }
                ans += area * sides;
            }
        }
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