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

vi parent, sizeArray;

string readFile(string filename) {
    ifstream file(filename);
    string s;
    string line;
    while (getline(file, line)) {
        s += line + "\n";
    }
    return s;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
void make_set(int v) {
    parent[v] = v;
    sizeArray[v] = 1;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sizeArray[a] < sizeArray[b])
            swap(a, b);
        parent[b] = a;
        sizeArray[a] += sizeArray[b];
    }
}

void solve1(string &filename, int n, int bytes) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    vvi grid(n, vi(n, 0));
    rep(i, 0, bytes){
        int pos = v[i].find(",");
        int x = stoi(v[i].substr(0, pos));
        int y = stoi(v[i].substr(pos + 1));
        grid[x][y] = 1;
    }
    queue<pair<pii, int>> q;
    vvi vis(n, vi(n, 0));
    q.push({{0, 0}, 0});
    vis[0][0] = 1;
    int ans = 0;
    vpii dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!q.empty()) {
        auto [curr, dist] = q.front();
        q.pop();
        if (curr.ff == n - 1 && curr.ss == n - 1) {
            ans = dist;
            break;
        }
        for (auto [dx, dy] : dir) {
            int nx = curr.ff + dx, ny = curr.ss + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && !vis[nx][ny] && grid[nx][ny] == 0) {
                vis[nx][ny] = 1;
                q.push({{nx, ny}, dist + 1});
            }
        }
    }
    cout << ans << endl;
}

void solve2(string &filename, int n) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> v;
    while (getline(iss, line)) {
        v.pb(line);
    }
    int newN = n + 2;
    vvi grid(newN, vi(n+2, 0));
    parent.assign(newN * newN, 0);
    sizeArray.assign(newN * newN, 0);
    rep(i, 0, sz(parent)){
        make_set(i);
    }
    rep(i, 1, newN - 1){
        union_sets(newN * i, newN * (i + 1));
        grid[i][0] = 1;
    }
    rep(j, 0, newN - 2){
        union_sets(newN * (newN - 1) + j, newN * (newN - 1) + j + 1);
        grid[newN - 1][j] = 1;
    }
    rep(j, 1, newN - 1){
        union_sets(j, j + 1);
        grid[0][j] = 1;
    }
    rep(i, 0, newN - 2){
        union_sets(newN * i + newN - 1, newN * (i + 1) + newN - 1);
        grid[i][newN - 1] = 1;
    }
    vpii surround = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    rep(i, 0, sz(v)){
        int pos = v[i].find(",");
        int x = stoi(v[i].substr(0, pos)) + 1;
        int y = stoi(v[i].substr(pos + 1)) + 1;
        grid[x][y] = 1;
        for (auto [dx, dy] : surround){
            int nx = x + dx, ny = y + dy;
            if (grid[nx][ny] == 1){
                union_sets(newN * x + y, newN * nx + ny);
            }
        }
        if (find_set(newN) == find_set(1)){
            cout << v[i] << endl;
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string filename = argc > 1 ? argv[1] : "large-input.txt";
    solve1(filename, 71, 1024);
    solve2(filename, 71);
}