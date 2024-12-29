//
// Created by Prakul Agrawal on 12/28/24.
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

void solve(string &filename, int minTime, int cheats) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    int startX, startY;
    int endX, endY;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] == 'S') {
                startX = i;
                startY = j;
            }
            if (v[i][j] == 'E') {
                endX = i;
                endY = j;
            }
        }
    }
    v[startX][startY] = '.';
    vvi dist(n, vi(m, INT_MAX));
    int currDist = 0;
    int x = endX, y = endY;
    vpii dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while(true) {
        dist[x][y] = currDist++;
        rep(i, 0, 4) {
            int nx = x + dir[i].ff, ny = y + dir[i].ss;
            if (v[nx][ny] == '.' && dist[nx][ny] == INT_MAX) {
                x = nx;
                y = ny;
                break;
            }
        }
        if (x == startX && y == startY) {
            break;
        }
    }
    dist[x][y] = currDist;
    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] == '.') {
                rep(a, -cheats, cheats + 1) {
                    rep(b, abs(a) - cheats, cheats - abs(a) + 1) {
                        int nx = i + a, ny = j + b;
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                            v[nx][ny] != '#' && (dist[i][j] - dist[nx][ny] - abs(a) - abs(b)) >= minTime) {
                            ans++;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve(filename, 100, 2);
    solve(filename, 100, 20);
}