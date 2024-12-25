//
// Created by Prakul Agrawal on 12/25/24.
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
    vector<string> grid;
    while (getline(iss, line)) {
        if (line == "") break;
        grid.pb(line);
    }
    string moves = "";
    while(getline(iss, line)) {
        moves += line;
    }
    int n = sz(grid), m = sz(grid[0]);
    int x, y;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == '@') {
                x = i;
                y = j;
            }
        }
    }
    map<char, pii> dir = {{'<', {0, -1}}, {'>', {0, 1}}, {'^', {-1, 0}}, {'v', {1, 0}}};
    for(auto move : moves){
        auto [dx, dy] = dir[move];
        int nx = x + dx, ny = y + dy;
        while(grid[nx][ny] != '#' && grid[nx][ny] != '.'){
            nx += dx;
            ny += dy;
        }
        if(grid[nx][ny] == '#'){
            continue;
        }
        grid[x][y] = '.';
        grid[x + dx][y + dy] = '@';
        while(grid[nx][ny] != '@'){
            grid[nx][ny] = 'O';
            nx -= dx;
            ny -= dy;
        }
        x += dx;
        y += dy;
    }
    ll ans = 0;
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] == 'O'){
                ans += 100 * i + j;
            }
        }
    }
    cout << ans << endl;
}

void solve2(string &filename) {
    string s = readFile(filename);
    istringstream iss(s);
    string line;
    vector<string> grid;
    while (getline(iss, line)) {
        if (line == "") break;
        grid.pb(line);
    }
    rep(i, 0, sz(grid)){
        string temp = "";
        for (auto c : grid[i]){
            if (c == '@'){
                temp += "@.";
            } else if (c == 'O'){
                temp += "[]";
            } else {
                temp += c;
                temp += c;
            }
        }
        grid[i] = temp;
    }
    string moves = "";
    while(getline(iss, line)) {
        moves += line;
    }
    int n = sz(grid), m = sz(grid[0]);
    int x, y;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == '@') {
                x = i;
                y = j;
            }
        }
    }
    map<char, pii> dir = {{'<', {0, -1}}, {'>', {0, 1}}, {'^', {-1, 0}}, {'v', {1, 0}}};
    for(auto move : moves){
        auto [dx, dy] = dir[move];
        if (move == '<' || move == '>') {
            int nx = x + dx, ny = y + dy;
            while(grid[nx][ny] != '#' && grid[nx][ny] != '.'){
                nx += 2 * dx;
                ny += 2 * dy;
            }
            if(grid[nx][ny] == '#'){
                continue;
            }
            grid[x][y] = '.';
            grid[x + dx][y + dy] = '@';
            x += dx;
            y += dy;
            int tx = x + dx, ty = y + dy;
            string brackets = move == '<' ? "][" : "[]";
            int index = 0;
            int loopCount = move == '<' ? ty - ny + 1 : ny - ty + 1;
            rep(i, 0, loopCount){
                grid[tx][ty] = brackets[index];
                tx += dx;
                ty += dy;
                index = 1 - index;
            }
        }
        else {
            vvpii memo;
            memo.pb({{x, y}});
            bool foundHash = false;
            while(!foundHash){
                vpii next;
                for (auto [i, j] : memo.back()) {
                    int nx = i + dx, ny = j + dy;
                    if (grid[nx][ny] == '#') {
                        foundHash = true;
                        break;
                    }
                    if (grid[nx][ny] != '.') {
                        next.pb({nx, ny});
                        if (grid[nx][ny] == '[') {
                            next.pb({nx, ny + 1});
                        }
                        else {
                            next.pb({nx, ny - 1});
                        }
                    }
                }
                if (next.empty()){
                    break;
                }
                memo.pb(next);
            }
            if (!foundHash){
                while(!memo.empty()){
                    for (auto [i, j] : memo.back()){
                        grid[i + dx][j + dy] = grid[i][j];
                    }
                    for (auto [i, j] : memo.back()){
                        grid[i][j] = '.';
                    }
                    memo.pop_back();
                }
                x += dx;
                y += dy;
            }
        }
    }
    ll ans = 0;
    rep(i, 0, n){
        rep(j, 0, m){
            if(grid[i][j] == '['){
                ans += 100 * i + j;
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