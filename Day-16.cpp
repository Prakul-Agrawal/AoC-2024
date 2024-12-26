//
// Created by Prakul Agrawal on 12/26/24.
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
typedef tuple<ll, int, int, int> tliii;
typedef tuple<int, int, int> tiii;

string readFile(string filename) {
    ifstream file(filename);
    string s;
    string line;
    while (getline(file, line)) {
        s += line + "\n";
    }
    return s;
}

void solve(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int n = sz(v), m = sz(v[0]);
    int startX = -1, startY = -1;
    int endX = -1, endY = -1;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (v[i][j] == 'S') {
                startX = i;
                startY = j;
            }
            else if (v[i][j] == 'E') {
                endX = i;
                endY = j;
            }
        }
    }
    map<int, pii> dirMap = {{0, {0, 1}}, {1, {1, 0}}, {2, {0, -1}}, {3, {-1, 0}}};
    vector<vvl> dist(n, vvl(m, vl(4, INF)));
    vector<vector<vector<vector<tiii>>>> parents(n, vector<vector<vector<tiii>>>(m, vector<vector<tiii>>(4)));
    dist[startX][startY][0] = 0;
    min_heap(tliii) pq;
    pq.push({0, 0, startX, startY});
    while (!pq.empty()) {
        auto [d, dir, x, y] = pq.top();
        pq.pop();
        if (d > dist[x][y][dir]) {
            continue;
        }
        int nx = x + dirMap[dir].ff;
        int ny = y + dirMap[dir].ss;
        if (v[nx][ny] != '#' && dist[nx][ny][dir] >= d + 1) {
            if (dist[nx][ny][dir] > d + 1) {
                dist[nx][ny][dir] = d + 1;
                pq.push({d + 1, dir, nx, ny});
                parents[nx][ny][dir] = {{x, y, dir}};
            }
            else {
                parents[nx][ny][dir].pb({x, y, dir});
            }
        }
        for(auto newDir : {-1, 1}) {
            newDir = (dir + newDir + 4) % 4;
            if (dist[x][y][newDir] >= d + 1000) {
                if (dist[x][y][newDir] > d + 1000) {
                    dist[x][y][newDir] = d + 1000;
                    pq.push({d + 1000, newDir, x, y});
                    parents[x][y][newDir] = {{x, y, dir}};
                }
                else {
                    parents[x][y][newDir].pb({x, y, dir});
                }
            }
        }
    }
    ll ans1 = INF;
    rep(i, 0, 4) {
        ans1 = min(ans1, dist[endX][endY][i]);
    }
    cout << ans1 << endl;
    vvi inPath(n, vi(m, 0));
    inPath[endX][endY] = 1;
    queue<tiii> q;
    rep(i, 0, 4) {
        if (dist[endX][endY][i] == ans1) {
            q.push({endX, endY, i});
        }
    }
    while (!q.empty()) {
        auto [x, y, dir] = q.front();
        q.pop();
        for (auto [px, py, pdir] : parents[x][y][dir]) {
            inPath[px][py] = 1;
            q.push({px, py, pdir});
        }
    }
    int ans2 = accumulate(all(inPath), 0, [](int a, vi b) {
        return a + accumulate(all(b), 0);
    });
    cout << ans2 << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve(filename);
}