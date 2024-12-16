//
// Created by Prakul Agrawal on 12/13/24.
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

int increase_cnt_X(vector<string> &grid, int i, int j, int n, int m) {
    string word = "MAS";
    int cnt = 0;
    vpii dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (auto [dx, dy]: dir) {
        rep(mov,1,4){
            int x = i + mov * dx, y = j + mov * dy;
            if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != word[mov-1]) {
                break;
            }
            if (mov == 3) {
                cnt++;
            }
        }
    }
    return cnt;
}

int increase_cnt_A(vector<string> &grid, int i, int j, int n, int m) {
    vpii dir = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    string word = "";
    for (auto [dx, dy]: dir) {
        int x = i + dx, y = j + dy;
        if (x < 0 || x >= n || y < 0 || y >= m) {
            break;
        }
        else {
            word += grid[x][y];
        }
    }
    vector<string> words = {"MMSS", "SMSM", "SSMM", "MSMS"};
    int flag = 0;
    for (auto w: words) {
        if (w == word) {
            flag = 1;
            break;
        }
    }
    return flag;
}

void solve1() {
    string s = readFile("input.txt");
    istringstream iss(s);
    vector<string> grid;
    string line;
    while (getline(iss, line)) {
        grid.push_back(line);
    }
    int n = grid.size(), m = grid[0].size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                cnt += increase_cnt_X(grid, i, j, n, m);
            }
        }
    }
    cout << cnt << endl;
}

void solve2() {
    string s = readFile("input.txt");
    istringstream iss(s);
    vector<string> grid;
    string line;
    while (getline(iss, line)) {
        grid.push_back(line);
    }
    int n = grid.size(), m = grid[0].size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                cnt += increase_cnt_A(grid, i, j, n, m);
            }
        }
    }
    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(0); // To increase input-output speed
    cin.tie(0);
    solve1();
    solve2();
}